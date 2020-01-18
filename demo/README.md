# iGPU Leak

We discover two sources of information leakage in CVE-2019-14615, one is *Shared Local Memory (SLM)* and the other is *General Register File (GRF)*.

This folder contains the PoC of SLM leakage.

GRF leakage code will be open-sourced later.

## Demo
* Demo video of SLM leakage: https://youtu.be/xHihb2SwXyo
* Demo video of GRF leakage: https://youtu.be/AouEeCF4cj0


## Structure
* `./SLM_Leak` contains the code of SLM leakage
* `./util` contains a helper program to run OpenCL kernels.


## Prerequisites
* Intel CPU with an integrated GPU (Verified on Core i7 6700 w/ Gen 9 iGPU )
* 64-bit Ubuntu 16.04 or Ubuntu 18.04.
* OpenCL dependencies. Run `install_opencl.sh` to install the dependencies.


## Run

Please refer to the `README.md` in the `./demo/SLM_Leak` folder.


## Credit
* Wenjian HE
* Wei Zhang
* Sharad Sinha
* Sanjeev Das

