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


try make -C ../util release

GPU_NUM_SUBSLICE=3

## View all memory data in SLM
# DUMP_SURF_SIZE=$(( GPU_NUM_SUBSLICE * 16384 ))

## View only part of data in SLM
DUMP_SURF_SIZE=16384

while true ; do
    echo "Press Ctrl+C to stop."
    try ../util/ocl_run --cl slm_attacker.cl -n read_slm -g "${GPU_NUM_SUBSLICE}" -s "${DUMP_SURF_SIZE}" --enqueue 1 --batch 2 -E16
done
