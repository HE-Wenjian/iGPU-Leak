#!/bin/bash
function try { 
    "$@" 
    local status=$?
    if [ $status -ne 0 ]; then
        local func_caller
        func_caller=$(caller 0)
        echo "[ERROR] Failed (retcode=$status) on cmd: $* at line $func_caller. Abort." >&2
        exit $status
    fi
}

# In case sudo is not availabe
SUDO="" && hash sudo 2>/dev/null && SUDO=sudo

# Install opencl runtime, this PoC is verified on version 19.26.13286.
# According to https://github.com/intel/compute-runtime/releases/tag/19.26.13286
try mkdir neo
try cd neo
try wget -nv https://github.com/intel/compute-runtime/releases/download/19.26.13286/intel-gmmlib_19.2.1_amd64.deb
try wget -nv https://github.com/intel/compute-runtime/releases/download/19.26.13286/intel-igc-core_1.0.9-2211_amd64.deb
try wget -nv https://github.com/intel/compute-runtime/releases/download/19.26.13286/intel-igc-opencl_1.0.9-2211_amd64.deb
try wget -nv https://github.com/intel/compute-runtime/releases/download/19.26.13286/intel-opencl_19.26.13286_amd64.deb
try wget -nv https://github.com/intel/compute-runtime/releases/download/19.26.13286/intel-ocloc_19.26.13286_amd64.deb
try ${SUDO} dpkg -i ./*.deb
cd ..

# Intall opencl-header and Opencl ICD loader
try ${SUDO} apt-get update
try ${SUDO} apt-get install -y opencl-headers ocl-icd-libopencl1

# Help compilers to find OpenCL libray
[[ ! -f /usr/lib/x86_64-linux-gnu/libOpenCL.so ]] && \
    try ${SUDO} ln -s /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0 /usr/lib/x86_64-linux-gnu/libOpenCL.so
