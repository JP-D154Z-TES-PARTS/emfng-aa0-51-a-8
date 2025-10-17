# emfng-aa0-51-a Changes Summary

## Overview
This document summarizes the changes made to generate emfng-aa0-51-a from emfng-aa0-50-a based on the logic difference specification.

## Specification Reference
- Base version: emfng-aa0-50-a
- New version: emfng-aa0-51-a
- Specification document: ロジック変更シート_ver9.09_emfng-aa0.xlsx (S51a sheet)

## Main Changes

### 1. DI/PFI Abnormality Detection Timing Improvement (t-CORE対応)

**File:** emfng_l_mat.c
**Location:** Lines 2758-2763
**Purpose:** Improve DI/PFI abnormality detection timing to match North American OBD requirements

**Change Description:**
Modified the condition for setting `u1t_emcnd` to `u1g_WMF_FDI_WITHIN_FIRST1000RPM` (1 notification) instead of `u1g_WMF_FDI_AFTER_FIRST1000RPM` (4 notifications).

**Before (aa0-50-a):**
```c
u1t_emcnd = u1g_WMF_FDI_AFTER_FIRST1000RPM;
if ( bis_emfng_exemfst == (u1)ON )
{
    u1t_emcnd = u1g_WMF_FDI_WITHIN_FIRST1000RPM;
}
```

**After (aa0-51-a):**
```c
u1t_emcnd = u1g_WMF_FDI_AFTER_FIRST1000RPM;
if ( ( bis_emfng_exemfst == (u1)ON )
#if ( JEEFI == u1g_EJCC_DUAL ) && ( JEHIPFI_E == u1g_EJCC_USE )
  || ( big_emfng_exmfddi == (u1)ON )
  || ( big_emfng_exmfdpfi == (u1)ON )
#endif
   )
{
    u1t_emcnd = u1g_WMF_FDI_WITHIN_FIRST1000RPM;
}
```

**Impact:**
- DI/PFI abnormality detection now occurs after 200 rev × 1 time (instead of 200 rev × 4 times)
- Faster abnormality detection for North American OBD compliance
- Only applies when dual injection (DI/PFI) is used

### 2. Minor Documentation Update

**File:** Line 2197
**Change:** Minor character correction in Japanese comment (not related to main logic change)

### 3. Version History Update

**File:** emfng.h
**Location:** Lines 80-87
**Purpose:** Document the aa0-51-a changes in the header file

Added aa0-51 version history entry describing:
- DI/PFI abnormality detection timing improvement
- Addition of conditions for WMF_FDI_WITHIN_FIRST1000RPM notification
- Documentation correction reference (DENG-STD-24050 No1)

## File Encoding
- All files are generated with CP932 (Shift-JIS) encoding to support Japanese comments
- File sizes are identical to base version, preserving original encoding

## Compilation Status
- The generated files maintain the same structure as the base version
- All preprocessor directives and compile switches are preserved
- Changes are conditionally compiled based on existing switches (JETCORE_D, JEEFI, JEHIPFI_E)

## Related Files
- new/emfng_l_mat.c: Main source file with logic changes
- new/emfng.h: Header file with version history update
- Specification: new/D0emfng-aa0-51-a/document/ロジック変更シート_ver9.09_emfng-aa0.xlsx
