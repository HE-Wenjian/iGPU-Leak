CVE-2019-14615: The iGPU-Leak Vulnerability
========

> Wenjian He, Wei Zhang, Sharad Sinha and Sanjeev Das. iGPU Leak: An Information Leakage Vulnerability on Intel Integrated GPU. In Proceedings of the 25th Asia and South Pacific Design Automation Conference (ASP-DAC'20).
> 
> [View PDF](https://ieeexplore.ieee.org/document/9045745)
>
> [View Slides](https://github.com/HE-Wenjian/iGPU-Leak/blob/master/iGPU-Leak_Slides.pdf)


# What happened?

A security issue was found on Intel integrated GPUs (iGPUs).
It allows attackers to leak private data from an iGPU.
Besides games, nowadays a large variety of software leverage GPU acceleration, e.g. web browsers and blockchains.
These applications are all at risk.
The problem is caused by defective GPU management of the graphics driver.
When an application uses the GPU, some private data inevitably get stored in GPU.
We find the graphics driver fails to wipe them after the application finishes, so the data preserve in the GPU.
Therefore, an attacker can run a GPU spyware to steal these private data.

For details, see [Technical explanation](#Technical-Explanation).


# Affected Products

**Affected Hardware**: Most Intel 3rd to 10th Generation Core processors and many other Intel processor families are all affected.

| Affected OSes | Patch  |
| ------ |  ------------ |
| Win    | Intel Graphics DCH driver >= 26.20.100.7209
| Linux  | Consult your OS vendor. [Learn More](#Linux-Patch-Status)
| Mac    | macOS Catalina 10.15.4. [Learn More](https://support.apple.com/en-ca/HT211100)

We recommend you to update the Intel Graphics driver as soon as it becomes available.
Please refer to the Intel Security Advisory [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html) for the complete list of affected products and operating systems.


# Known Exploits

We are not aware of any exploitations in the wild.
However, we expect it is easy to develop attacks with the vulnerability.
According to our experiments, the following 2 attacks are possible. 


#### 1. Browser activity eavesdropping

By monitoring the Intel iGPU, an attacker may know which website the user is visiting.

![Browser eavesdropping](https://github.com/HE-Wenjian/iGPU-Leak/raw/pic/browser_attack.png) 


#### 2. Key recovery attack against iGPU-accelerated ciphers

If you are using an iGPU for cryptographic tasks, the plaintext or even the key may be leaked due to the iGPU-Leak vulnerability.


# Technical Explanation

This is an uninitialized data vulnerability due to the Intel Graphics driver, and it results in information leakage through GPU hardware.
In essence, the GPU state is not reset during a GPU context switch. 
We identify two components in Intel iGPUs that leak information due to this vulnerability:
1) shared local memory, and
2) the general register file in every execution unit (EU).

![SLM and GRF in Intel iGPU Arch](https://github.com/HE-Wenjian/iGPU-Leak/raw/pic/gpu_arch.png)


## Demo Videos

* Demo video of Shared Local Memory (SLM) leakage: https://youtu.be/xHihb2SwXyo
* Demo video of General Register File (GRF) leakage: https://youtu.be/AouEeCF4cj0


## PoC Code

* `./demo` contains the source code of the proof-of-concept attack. Please refer to the `./demo/README.md` for the instructions to run the demo.


## Linux Patch Status

| Intel Graphics |  CPU uArch  | Patch  | Status |
| ------ | ------------------- | ------ | ------ |
| Gen 9  | Skylake, Kaba Lake, Coffee Lake | [Link](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit?id=bc8a76a152c5f9ef3b48104154a65a68a8b76946) | Merged into mainline at [Linux 5.5-rc7](https://lwn.net/Articles/809255/), and backported.
| Gen 8  | Broadwell           | Immune |
| Gen 7  | Haswell, Ivy Bridge | [Link](https://patchwork.freedesktop.org/series/72028/) | Under development.


## Coordinated Disclosure

We appreciate Intel's professional handling of our report.

* September 2019: We reported our findings to Intel.
* October 14, 2019: Intel confirmed the vulnerability.
* January 14, 2020: Intel released [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html).


### Credit
* Wenjian He, wheac@connect.ust.hk, _Hong Kong Univ. of Science and Technology_
* Wei Zhang, wei.zhang [at] ust.hk, _Hong Kong Univ. of Science and Technology_
* Sharad Sinha, sharad [at] iitgoa.ac.in, _Indian Institute of Technology, Goa_
* Sanjeev Das, sdas [at] cs.unc.edu, _Univ. of North Carolina at Chapel Hill, USA_

