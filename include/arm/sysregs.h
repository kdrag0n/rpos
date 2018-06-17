#pragma once

// sctlr_el1: System Control Register
// reserved bits
#define SCTLR_RESERVED              (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
// use little endian in el1
#define SCTLR_EE_LITTLE_ENDIAN      (0 << 25)
// use little endian in el0
#define SCTLR_E0E_LITTLE_ENDIAN     (0 << 24)
// disable instruction cache
#define SCTLR_I_CACHE_DISABLED      (0 << 12)
// disable data cache
#define SCTLR_D_CACHE_DISABLED      (0 << 2)
// disable memory mapping unit
#define SCTLR_MMU_DISABLED          (0 << 0)
// enable memory mapping unit
#define SCTLR_MMU_ENABLED           (1 << 0)
// target flags
#define SCTLR_VALUE                 (SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED)

// hcr_el2: Hypervisor Configuration Register
// execute aarch64 in el1
#define HCR_RW                      (1 << 31)
// target flags
#define HCR_VALUE                   HCR_RW

// scr_el3: Secure Configuration Register
// reserved bits
#define SCR_RESERVED                (3 << 4)
// execute aarch64 in el2
#define SCR_RW                      (1 << 10)
// el < 2 is non secure
#define SCR_NS                      (1 << 0)
// target flags
#define SCR_VALUE                   (SCR_RESERVED | SCR_RW | SCR_NS)

// spsr_el3: Saved Program Status Register
// disable interrupts in el <= 1
#define SPSR_MASK_ALL               (7 << 6)
// dedicated el1 stack pointer
#define SPSR_EL1H                   (5 << 0)
// target flags
#define SPSR_VALUE                  (SPSR_MASK_ALL | SPSR_EL1H)
