#ifndef HOST_COMMON_H
#define HOST_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <CL/cl.h>

#define eprintf(fmt, ...) fprintf(stderr,fmt, ## __VA_ARGS__)

#define CL_assert(status) clCheckError(status,"Assert:") 
#define CL_assertMsg(status, errorMsg) clCheckError(status,errorMsg)

const char* clGetErrorString(cl_int errorCode);
inline void clCheckError(cl_int errorCode,const char * prefix) {
    if (errorCode != CL_SUCCESS) {
        eprintf("%s: %s\n", prefix, clGetErrorString(errorCode));
        exit(errorCode);
    }
}

static const char * EMPTY_CHAR="";

cl_device_id getDevice(int devtype);
void report_device(cl_device_id device);
cl_command_queue getCmdQueue(cl_device_id device, cl_context context);
cl_program getProgramFromSource(cl_device_id dev, cl_context ctx, const char *filename,
                      const char *buildOptions=EMPTY_CHAR);
cl_program getProgramFromBinary(cl_device_id dev, cl_context ctx, const char *filename,
                      const char *buildOptions=EMPTY_CHAR);

cl_int cleanupCL(cl_device_id device, cl_context context, cl_command_queue queue);
#endif //HOST_COMMON_H
