#include "common.hpp"
#include <fstream>
#include <sstream>

const char* clGetErrorString(cl_int errorCode) {
    switch (errorCode) {
        case 0: return "CL_SUCCESS";
        case -1: return "CL_DEVICE_NOT_FOUND";
        case -2: return "CL_DEVICE_NOT_AVAILABLE";
        case -3: return "CL_COMPILER_NOT_AVAILABLE";
        case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case -5: return "CL_OUT_OF_RESOURCES";
        case -6: return "CL_OUT_OF_HOST_MEMORY";
        case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
        case -8: return "CL_MEM_COPY_OVERLAP";
        case -9: return "CL_IMAGE_FORMAT_MISMATCH";
        case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case -12: return "CL_MAP_FAILURE";
        case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
        case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
        case -15: return "CL_COMPILE_PROGRAM_FAILURE";
        case -16: return "CL_LINKER_NOT_AVAILABLE";
        case -17: return "CL_LINK_PROGRAM_FAILURE";
        case -18: return "CL_DEVICE_PARTITION_FAILED";
        case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
        case -30: return "CL_INVALID_VALUE";
        case -31: return "CL_INVALID_DEVICE_TYPE";
        case -32: return "CL_INVALID_PLATFORM";
        case -33: return "CL_INVALID_DEVICE";
        case -34: return "CL_INVALID_CONTEXT";
        case -35: return "CL_INVALID_QUEUE_PROPERTIES";
        case -36: return "CL_INVALID_COMMAND_QUEUE";
        case -37: return "CL_INVALID_HOST_PTR";
        case -38: return "CL_INVALID_MEM_OBJECT";
        case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case -40: return "CL_INVALID_IMAGE_SIZE";
        case -41: return "CL_INVALID_SAMPLER";
        case -42: return "CL_INVALID_BINARY";
        case -43: return "CL_INVALID_BUILD_OPTIONS";
        case -44: return "CL_INVALID_PROGRAM";
        case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
        case -46: return "CL_INVALID_KERNEL_NAME";
        case -47: return "CL_INVALID_KERNEL_DEFINITION";
        case -48: return "CL_INVALID_KERNEL";
        case -49: return "CL_INVALID_ARG_INDEX";
        case -50: return "CL_INVALID_ARG_VALUE";
        case -51: return "CL_INVALID_ARG_SIZE";
        case -52: return "CL_INVALID_KERNEL_ARGS";
        case -53: return "CL_INVALID_WORK_DIMENSION";
        case -54: return "CL_INVALID_WORK_GROUP_SIZE";
        case -55: return "CL_INVALID_WORK_ITEM_SIZE";
        case -56: return "CL_INVALID_GLOBAL_OFFSET";
        case -57: return "CL_INVALID_EVENT_WAIT_LIST";
        case -58: return "CL_INVALID_EVENT";
        case -59: return "CL_INVALID_OPERATION";
        case -60: return "CL_INVALID_GL_OBJECT";
        case -61: return "CL_INVALID_BUFFER_SIZE";
        case -62: return "CL_INVALID_MIP_LEVEL";
        case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
        case -64: return "CL_INVALID_PROPERTY";
        case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
        case -66: return "CL_INVALID_COMPILER_OPTIONS";
        case -67: return "CL_INVALID_LINKER_OPTIONS";
        case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";
        case -69: return "CL_INVALID_PIPE_SIZE";
        case -70: return "CL_INVALID_DEVICE_QUEUE";
        case -71: return "CL_INVALID_SPEC_ID";
        case -72: return "CL_MAX_SIZE_RESTRICTION_EXCEEDED";
        case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
        case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
        case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
        case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
        case -1006: return "CL_INVALID_D3D11_DEVICE_KHR";
        case -1007: return "CL_INVALID_D3D11_RESOURCE_KHR";
        case -1008: return "CL_D3D11_RESOURCE_ALREADY_ACQUIRED_KHR";
        case -1009: return "CL_D3D11_RESOURCE_NOT_ACQUIRED_KHR";
        case -1010: return "CL_INVALID_DX9_MEDIA_ADAPTER_KHR";
        case -1011: return "CL_INVALID_DX9_MEDIA_SURFACE_KHR";
        case -1012: return "CL_DX9_MEDIA_SURFACE_ALREADY_ACQUIRED_KHR";
        case -1013: return "CL_DX9_MEDIA_SURFACE_NOT_ACQUIRED_KHR";
        case -1093: return "CL_INVALID_EGL_OBJECT_KHR";
        case -1092: return "CL_EGL_RESOURCE_NOT_ACQUIRED_KHR";
        case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
        case -1057: return "CL_DEVICE_PARTITION_FAILED_EXT";
        case -1058: return "CL_INVALID_PARTITION_COUNT_EXT";
        case -1059: return "CL_INVALID_PARTITION_NAME_EXT";
        case -1094: return "CL_INVALID_ACCELERATOR_INTEL";
        case -1095: return "CL_INVALID_ACCELERATOR_TYPE_INTEL";
        case -1096: return "CL_INVALID_ACCELERATOR_DESCRIPTOR_INTEL";
        case -1097: return "CL_ACCELERATOR_TYPE_NOT_SUPPORTED_INTEL";
        case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
        case -1098: return "CL_INVALID_VA_API_MEDIA_ADAPTER_INTEL";
        case -1099: return "CL_INVALID_VA_API_MEDIA_SURFACE_INTEL";
        case -1100: return "CL_VA_API_MEDIA_SURFACE_ALREADY_ACQUIRED_INTEL";
        case -1101: return "CL_VA_API_MEDIA_SURFACE_NOT_ACQUIRED_INTEL";
        default: return "CL_UNKNOWN_ERROR";
    }
}

cl_command_queue getCmdQueue(cl_device_id device, cl_context context){
    cl_int err;
    cl_command_queue queue=NULL;

    queue = clCreateCommandQueueWithProperties(
        context, device, NULL, &err);

    CL_assertMsg(err,"Error: createCmdQueue() Fail!");
    return queue; 
}


cl_device_id getDevice(int devtype)
{
    int rval;
    cl_platform_id platform[2];
    cl_device_id device;

    rval = clGetPlatformIDs(2, platform, NULL);
    if (rval != CL_SUCCESS)
    {
        printf("failed clGetPlatformIDs (%d)\n", rval);
        exit(-1);
    }
    rval = clGetDeviceIDs(platform[0], devtype, 1, &device, NULL);
    if (rval != CL_SUCCESS)
        rval = clGetDeviceIDs(platform[1], devtype, 1, &device, NULL);
    if (rval != CL_SUCCESS)
    {
        printf("# Valid device ids:\n");
        printf("# %d - DEFAULT \n%d - CPU \n%d - GPU \n%d - ACCELERATOR\n",
               CL_DEVICE_TYPE_DEFAULT, CL_DEVICE_TYPE_CPU,
               CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_ACCELERATOR);
        printf("failed GetDeviceIDs (%d)\n", rval);
        exit(-1);
    }

    return device;
}

void report_device(cl_device_id device){
    int rval;
    cl_ulong maxSLM;
    size_t max_wrk_grp_size;

    /////////////////////////////////////////
    char deviceName[1024];
    size_t size_ret;
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(deviceName), deviceName,
                    &size_ret);
    printf("# device name: %s\n", deviceName);

    clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(maxSLM),
                    &maxSLM, &size_ret);
    printf("# device slm size: %i\n", (int)(maxSLM));

    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE,
                    sizeof(max_wrk_grp_size), &max_wrk_grp_size, &size_ret);
    printf("# device max work group size: %i\n", (int)(max_wrk_grp_size));

    /////////////////////////////////////////
    cl_uint max_compute_units_gpu = 0;
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
                    &max_compute_units_gpu, 0);
    printf("# Max compute units  (GPU): %d\n", max_compute_units_gpu);

    /////////////////////////////////////////
    cl_device_svm_capabilities tSVMCapabilities;

    rval=clGetDeviceInfo(device,
                    CL_DEVICE_SVM_CAPABILITIES,
                    sizeof(cl_device_svm_capabilities),
                    (void *)(&tSVMCapabilities),
                    NULL);
    CL_assertMsg(rval,"# SVM not supported!\n");

    if (tSVMCapabilities & CL_DEVICE_SVM_ATOMICS)
        printf("# SVM atomics supported.\n");
    if (tSVMCapabilities & CL_DEVICE_SVM_FINE_GRAIN_BUFFER)
        printf("# SVM fine grain buffer supported.\n" );
    if (tSVMCapabilities & CL_DEVICE_SVM_FINE_GRAIN_SYSTEM)
        printf("# SVM fine grain system supported.\n" );
    if (tSVMCapabilities & CL_DEVICE_SVM_COARSE_GRAIN_BUFFER)
        printf("# SVM coarse grain buffer supported.\n");

    /////////////////////////////////////////
}


char * get_file(const char *filename,size_t &fsize){
   FILE *fp;
   char *file_content;
   int e;

   fp = fopen(filename, "rb");
   if (!fp)
   {
	   printf("[ERROR] Could not find file %s\n", filename);
	   exit(1);
   }
   
   fseek(fp, 0L, SEEK_END);
   fsize = ftell(fp);
   fseek(fp, 0L, SEEK_SET);  // Note this resets fp to beginning.

   file_content = (char *) malloc(fsize);
   assert(file_content);
   e = fread(file_content, 1, fsize, fp);
   assert(e == fsize);
   assert(fclose(fp)==0);

   return file_content;
}


cl_program getProgramFromSource(cl_device_id dev, cl_context ctx, const char *filename,
                      const char *buildOptions){
   int e;
   size_t fsize=0;
   char * src=get_file(filename,fsize);

   cl_program program =
       clCreateProgramWithSource(ctx, 1, (const char **)&src, &fsize, &e);
   CL_assertMsg(e,"clCreateProgramWithSource() Err");
   
   e = clBuildProgram(program, 1, &dev, buildOptions, NULL, NULL);

    if (e != CL_SUCCESS)
    {
      /* Print out build log */
      char build_log[65536];
      size_t logsize = sizeof(build_log) - 1;
      e = clGetProgramBuildInfo(program, dev,
                                CL_PROGRAM_BUILD_LOG, logsize,
                                build_log, &logsize);
      build_log[logsize] = 0;

      printf("# Build Failed:\n%s\n", build_log);
      exit(-1);
    }

   free(src);
   return program;
}

cl_program getProgramFromBinary(cl_device_id dev, cl_context ctx, const char *filename,
                      const char *buildOptions){
   cl_int e,bin_e;
   size_t fsize=0;
   char * bin=get_file(filename,fsize);

    cl_program program =
       clCreateProgramWithBinary(ctx, 1, &dev, &fsize, (const unsigned char **)&bin, &bin_e, &e);
    CL_assertMsg(bin_e,"clCreateProgramWithBinary() Err");
    CL_assertMsg(e,"clCreateProgramWithBinary() Err");
   
   e = clBuildProgram(program, 1, &dev, buildOptions, NULL, NULL);

    if (e != CL_SUCCESS)
    {
      /* Print out build log */
      char build_log[65536];
      size_t logsize = sizeof(build_log) - 1;
      e = clGetProgramBuildInfo(program, dev,
                                CL_PROGRAM_BUILD_LOG, logsize,
                                build_log, &logsize);
      build_log[logsize] = 0;

      printf("# Build Failed:\n%s\n", build_log);
      exit(-1);
    }

   free(bin);
   return program;
}

cl_int cleanupCL(cl_device_id device, cl_context context, cl_command_queue queue)
{
	cl_int status;

    if(queue){
        CL_assert(clReleaseCommandQueue(queue));
    }

    if(context){
        CL_assert(clReleaseContext(context));
    }

    if(device)
	{
        CL_assert(clReleaseDevice(device));
	}

	return status;
}

