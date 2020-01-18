# SLM Leakage

## Video
* Demo video of SLM leakage: https://youtu.be/xHihb2SwXyo


## Prerequisites
* Intel CPU with an integrated GPU (Verified on Core i7 6700, Gen 9 iGPU )
* 64-bit Ubuntu 16.04 or Ubuntu 18.04.
* OpenCL dependencies. Run `install_opencl.sh` in the repo.

## Run
1. (Optional) Adjust GPU_NUM_SUBSLICE in `./run_attacker.sh` and `./run_victim.sh` according to your iGPU.
2. Open two terminals.
3. In one terminal, execute `./run_attacker.sh`. At present, you can only see 0.
4. In the other terminal, execute `./run_victim.sh`. The victim writes values to SLM.
5. Now, you can see that the attacker's terminal gets the SLM dump of the victim.
6. Press Ctrl+C to stop.

## Credit
* Wenjian HE
* Wei Zhang
* Sharad Sinha
* Sanjeev Das

