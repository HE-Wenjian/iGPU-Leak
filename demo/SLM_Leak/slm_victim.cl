// My machine is i7-6700 (skylake) with Intel HD 530 (Gen 9.5), 
// whose SLM is 64 KB per subslice
#define Subslice_SLM_Size (64*1024)  // 64 KB

__kernel void write_slm(__global uint *init_val){
    const size_t N=Subslice_SLM_Size/sizeof(uint);
    __local uint slm[N];
    uint sublice_header=(get_group_id(0)+1)<<(6*4);
    uint tmp=*init_val;
    for(int i=0;i<N;i++){
        slm[i]=sublice_header | tmp;
        tmp= (tmp>=0xf000)? 0x0 : tmp+1;
    }
}