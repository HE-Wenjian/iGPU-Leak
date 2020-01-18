
#include "common.hpp"
#include "args.hpp"
#include <chrono>

static cl_device_id device = NULL;
static cl_context context = NULL;
static cl_command_queue queue = NULL;
static cl_program program = NULL;

template <class T> inline
void PrintOneLine(const size_t addr, T* data, const T* end){
    printf("%7lu: ", addr);
    for(; data != end; data++){
        printf("%8x ", (unsigned)(*data) );
    }
    printf("\n");
}

template <class List>
void PrintSurfs(const std::vector<int*>& SVM_ptrs, const List& surf_sizes){
    const int NumElemPerLine=ArgsGet(NumElemPerLine);
    if(NumElemPerLine==0) return;

    for(int idx=0; idx<surf_sizes.size(); ++idx){
        printf("surf[%i]:\n", idx );
        for(int addr=0; addr<surf_sizes[idx]; addr+=NumElemPerLine){
            PrintOneLine(addr, & SVM_ptrs[idx][addr],
                & SVM_ptrs[idx][std::min(addr+NumElemPerLine,surf_sizes[idx])]);
        }
        printf("\n");
    }
}

static void RunOneBatch(cl_kernel kernel,const int dim, const size_t* global, const size_t* local){
    cl_event WaitPrevious;
    cl_event NextEvent;
    auto start = std::chrono::high_resolution_clock::now();

    CL_assert(clEnqueueNDRangeKernel(queue, kernel, dim, NULL,
            global, local, 0, NULL, &WaitPrevious));
    for(int i=1; i<(ArgsGet(NumEnqueue)); ++i){
        CL_assert(clEnqueueNDRangeKernel(queue, kernel, dim, NULL,
            global, local, 1, &WaitPrevious, &NextEvent));
        WaitPrevious=NextEvent;
    }

    CL_assert(clFinish(queue));
    printf("[INFO] Kernel Finish. Elapsed= %f s\n",
        (std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-start)).count());
}

template <class List>
static void RunOpenCL(
    cl_kernel kernel,
    const List& g_sizes,
    const List& l_sizes,
    const List& surf_sizes
){
    std::vector<int*> SVM_ptrs;
    for(int idx=0; idx<surf_sizes.size(); ++idx){
        int * ptr=(int *)clSVMAlloc(context, CL_MEM_READ_WRITE, surf_sizes[idx]*sizeof(int),0);
        assert(ptr);
        CL_assert(clEnqueueSVMMap(queue,CL_FALSE,CL_MAP_WRITE,ptr,surf_sizes[idx]*sizeof(int),0,NULL,NULL));
        SVM_ptrs.push_back(ptr);
    }
    CL_assert(clFinish(queue));

    for(int idx=0; idx<surf_sizes.size(); ++idx)
        CL_assert(clSetKernelArgSVMPointer(kernel,idx,SVM_ptrs[idx]));

    size_t global[3]={0,0,0};
    size_t local[3]={0,0,0};
    for(int i=0; i<g_sizes.size(); ++i){
        global[i]=g_sizes[i];
        local[i]=l_sizes[i];
    }

    for(size_t batch=0; batch<ArgsGet(NumBatch); ++batch)
    {
        for(size_t idx=0; idx<surf_sizes.size(); ++idx)
            for(size_t i=0; i<surf_sizes[idx]; ++i)
                SVM_ptrs[idx][i]=0;
    
        if(ArgsGet(verbose)) 
            printf("[INFO] Enqueue <%lu,%lu,%lu> (as <%lu,%lu,%lu> groups) = %lu work items for %i times.\n"
                ,global[0],global[1],global[2]
                , local[0], local[1], local[2]
                ,global[0] * std::max(global[1],1UL) * std::max(global[2],1UL)
                ,ArgsGet(NumEnqueue)
            );
        
        RunOneBatch(kernel,g_sizes.size(),(const size_t*) global, (const size_t*) local);
        PrintSurfs(SVM_ptrs, surf_sizes);
    }

    for(int* ptr: SVM_ptrs){
        CL_assert(clEnqueueSVMUnmap(queue,ptr,0,NULL,NULL));
    }
    CL_assert(clEnqueueSVMFree(queue,SVM_ptrs.size(),(void**)SVM_ptrs.data(),NULL,NULL,0,NULL,NULL));
    CL_assert(clFinish(queue));
}



int main(int argc, char **argv){

    CommandLineParser::getInstance().parse(argc,argv);

    cl_int err;
    device = getDevice(CL_DEVICE_TYPE_GPU);
    if(ArgsGet(verbose)) report_device(device);
    context = clCreateContext(0, 1, &device, NULL, NULL, &err);
    CL_assertMsg(err,"Error: clCreateContext()");
    queue = getCmdQueue(device,context);

    if( ArgsMention(ocl_c) ){
        program = getProgramFromSource(device,context,ArgsGet(ocl_c).c_str());
        printf("[NOTE] Run <%s> kernel from <%s>.\n",
            ArgsGet(kernel_name).c_str(),ArgsGet(ocl_c).c_str());
    }else if( ArgsMention(ocl_bin) ){
        program = getProgramFromBinary(device,context,ArgsGet(ocl_bin).c_str());
        printf("[NOTE] Run <%s> kernel from <%s>.\n",
            ArgsGet(kernel_name).c_str(),ArgsGet(ocl_bin).c_str());
    }
    
    cl_kernel kernel = clCreateKernel(program, ArgsGet(kernel_name).c_str(), &err);
    CL_assertMsg(err,"Error: clCreateKernel()!");

    RunOpenCL(kernel, ArgsGet(g_wsize), ArgsGet(l_wsize), ArgsGet(surf_sizes));

    CL_assert(clReleaseProgram(program));
    cleanupCL(device,context,queue);
    return 0;
}
