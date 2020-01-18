CVE-2019-14615: The iGPU-Leak Vulnerability
========

> Wenjian He, Wei Zhang, Sharad Sinha and Sanjeev Das. iGPU Leak: An Information Leakage Vulnerability on Intel Integrated GPU. In Proceedings of the 25th Asia and South Pacific Design Automation Conference (ASP-DAC'20).
> 
> [PDF](Please email me to get, wheac@connect.ust.hk.) |
> [Slides](https://github.com/HE-Wenjian/iGPU-Leak/blob/master/iGPU-Leak_Slides.pdf)


# Introduction

We disclose an uninitialized data vulnerability on Intel integrated GPUs (iGPUs).
In essence, residual register values and shared local memory in the iGPU are not cleared during a GPU context switch.


# Demo Videos

* Demo video of Shared Local Memory (SLM) leakage: https://youtu.be/xHihb2SwXyo
* Demo video of General Register File (GRF) leakage: https://youtu.be/AouEeCF4cj0


# Affected Products

Intel 3th to 10th Generation Core processors and many other processor families are all affected. 

We recommend you to update the Intel graphic driver as soon as it becomes available. Please refer to the Intel Security Advisory [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html) for the complete list of affected products and operating systems.

# Known Exploits

We are not aware of any exploitations in the wild.
However, we expect it is easy to develop attacks with the vulnerability.
According to our experiments, the following 2 attacks are possible. 

#### 1. Browser activity eavesdropping

By monitoring the Intel iGPU, an attacker may know which website the user is visiting.

#### 2. Key Recovery Attack against iGPU-accelerated cipher

If you are using an iGPU for cryptographic tasks, the plaintext or even the key may be leaked due to the iGPU-Leak vulnerability.


# PoC Code

* `./demo` contains the source code of the proof-of-concept attack. Please refer to the `./demo/README.md` for the instructions to run the demo.


## Coordinated Disclosure

We appreciate Intel’s professional handling of our report.

* September 2019: We reported our findings to Intel.
* October 14, 2019: Intel confirmed the vulnerability.
* January 14, 2020: Intel released the [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html).

## Credit
* Wenjian He, wheac@connect.ust.hk
* Wei Zhang, wei.zhang [AT] ust.hk
* Sharad Sinha, sharad [AT] iitgoa.ac.in
* Sanjeev Das, sdas [AT] cs.unc.edu

