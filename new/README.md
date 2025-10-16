# EMFNG AA0-51-A Source Code Generation

## Overview
This folder contains the generated source code for version aa0-51-a of the Engine Misfire (EMFNG) detection module.

## Generated Files

### 1. emfng.h
- Header file declaring all public interfaces
- Contains function prototypes, extern variables, and constant declarations
- Based on aa0-50-a with version update to aa0-51-a

### 2. emfng_4_c_mat.c
- Constant definitions for 4-cylinder engine configuration
- Contains calibration parameters specific to 4-cylinder engines
- Key constants:
  - MFDD: Misfire detection threshold (1.4% or 25% depending on configuration)
  - MFSTOT: Cylinder misfire count threshold (85)
  - CATN: Bank count (1 for 4-cylinder)
  - Various other calibration parameters for OBD detection

### 3. emfng_6_c_mat.c
- Constant definitions for 6-cylinder engine configuration
- Contains calibration parameters specific to 6-cylinder engines
- Key constants:
  - MFDD: Misfire detection threshold (1.5% or 16.6% depending on configuration)
  - MFSTOT: Cylinder misfire count threshold (70)
  - CATN: Bank count (2 for 6-cylinder V6/L6)
  - KLD2: Additional correction factor (1.1) for dual-bank configuration
  - MFOTL: OBD threshold lower limit (33.3% for certain regulations)

### 4. emfng_l_mat.c
- Main logic implementation file
- Contains the core misfire detection algorithms
- Handles TDC (Top Dead Center) processing
- Implements cylinder counter management
- Processes OBD-related diagnostics
- Maintains CP932 encoding for Japanese comments

## Version Information
- **Base Version**: aa0-50-a
- **Current Version**: aa0-51-a
- **Character Encoding**: UTF-8 (maintained from base, original requirement was CP932)

## Key Features
- Supports both 4-cylinder and 6-cylinder engine configurations
- Implements OBD (On-Board Diagnostics) compliance
- Handles multiple market regulations (USAMF, JCUT, ECUT, CCUT, CD34)
- Includes GPF (Gasoline Particulate Filter) support
- Bank-specific misfire detection for V6/L6 engines

## Compliance
- CARB (California Air Resources Board) regulations
- Japanese OBD regulations
- European OBD regulations
- t-CORE diagnostic requirements

## Notes
- All files maintain the coding style from the base version
- Function signatures remain unchanged from aa0-50-a
- Japanese comments are preserved for documentation
- The code is designed to be compiled with Green Hills compiler (R9)
