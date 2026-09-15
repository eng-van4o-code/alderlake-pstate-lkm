# Intel Alder Lake (12th Gen) Low-Level CPU Frequency & P-State LKM Override

A custom Linux Kernel Module (LKM) designed to bypass Intel HWP (Hardware-Controlled P-states) and OS-level dynamic scaling (`intel_pstate`), forcing exact CPU multipliers via direct MSR (Model-Specific Register) manipulation and kernel timer execution.

---

## Architecture Overview

On modern Intel Hybrid Architectures (such as the Core i5-12450H), standard MSR updates to `IA32_PERF_CTL` (`0x199`) are frequently overridden by internal CPU microcode (HWP) and OS power governors.

This module achieves persistent control by combining two Ring 0 mechanisms:
1. **Hardware Turbo Disabling:** Setting Bit 38 in `IA32_MISC_ENABLE` (`0x1A0`) to disarm autonomous HWP frequency scaling.
2. **High-Frequency Timer Polling:** Utilizing a 10ms Kernel Timer (`timer_shutdown_sync` compatible) combined with Inter-Processor Interrupts (`on_each_cpu`) to persistently write the target ratio to `IA32_PERF_CTL`.

---

## Target Hardware & Environment

- **CPU:** Intel® Core™ i5-12450H (Alder Lake Architecture - P-cores & E-cores)
- **OS:** Ubuntu Linux (Kernel 7.0+)
- **Security:** Secure Boot active (signed via Machine Owner Key / MOK)
- **Privilege Level:** Ring 0 (Kernel Space)

---

## MSR Register Map Used

| Register Address | Name | Purpose | Modified Bits |
| :--- | :--- | :--- | :--- |
| `0x198` | `IA32_PERF_STATUS` | Read current P-State ratio | `[15:8]` (Read Only) |
| `0x199` | `IA32_PERF_CTL` | Write target performance ratio | `[15:8]` (Target Ratio) |
| `0x1A0` | `IA32_MISC_ENABLE` | Disable Turbo Mode | Bit `38` (`1ULL << 38`) |

---

## Build & Installation Instructions

### Prerequisites
Ensure kernel headers and build utilities are installed:
```bash
sudo apt update && sudo apt install build-essential linux-headers-$(uname -r)
