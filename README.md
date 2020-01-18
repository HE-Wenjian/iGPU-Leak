CVE-2019-14615: The iGPU-Leak Vulnerability
========

> Wenjian He, Wei Zhang, Sharad Sinha and Sanjeev Das. iGPU Leak: An Information Leakage Vulnerability on Intel Integrated GPU. In Proceedings of the 25th Asia and South Pacific Design Automation Conference (ASP-DAC'20).
> 
> [PDF](Please email me to get, wheac@connect.ust.hk.)


# Introduction

An uninitialized data vulnerability was disclosed on Intel integrated GPU drivers. In essence, residual register values and shared local
memory in the iGPU are not cleared during a context switch.


# Demo Videos

* Demo video of Shared Local Memory (SLM) leakage: https://youtu.be/xHihb2SwXyo
* Demo video of General Register File (GRF) leakage: https://youtu.be/AouEeCF4cj0


# PoC Code

* `./demo` contains the source code of the prove-of-concept attack. Please refer to the `./demo/README.md` for the instructions to run the demo.


# Affected Products

3th to 10th Generation Core processors are all affected, we recommend you to install the update of graphic driver as soon as it becomes available. Please referring to the Intel Security Advisory [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html) for the complete list of affected products.


# Coordinated Disclosure

We appreciate Intel’s professional handling of our report.

* September 2019: We reported our findings to Intel.
* October 14, 2019: Intel confirmed the vulnerability.
* January 14, 2020: Intel released the [INTEL-SA-00314](https://www.intel.com/content/www/us/en/security-center/advisory/intel-sa-00314.html).

## Credit
* Wenjian He, wheac@connect.ust.hk
* Wei Zhang, wei.zhang [AT] ust.hk
* Sharad Sinha, sharad [AT] iitgoa.ac.in
* Sanjeev Das, sdas [AT] cs.unc.edu

