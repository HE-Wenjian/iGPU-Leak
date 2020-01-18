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

GPU_NUM_SUBSLICE=3

try make -C ../util/ release

while true ; do
    echo "Press Ctrl+C to stop."
    try ../util/ocl_run --cl slm_victim.cl -n write_slm -g "${GPU_NUM_SUBSLICE}" --enqueue 32 --batch 32 -E0
done
