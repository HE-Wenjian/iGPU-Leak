// My machine is i7-6700 (skylake) with Intel HD 530 (Gen 9.5), 
// whose SLM is 64 KB per subslice
#define Subslice_SLM_Size 64*1024

__kernel void read_slm(__global uint *out){
    const size_t N=Subslice_SLM_Size/sizeof(uint);
    __local uint slm[N];
    const size_t base=N*get_group_id(0);
    for(size_t i=0;i<N;i++){
        out[base+i]=slm[i];
    }
}