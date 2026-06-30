// FUNC_NAME: calculateAerodynamicDrag
// Function address: 0x006cc570
// Role: Computes aerodynamic drag/force for a physics simulation (likely from EARS engine)
// Uses x87 extended precision and global constants for approximation.
// Parameters: 
//   param_1 - velocity magnitude (or factor)
//   param_2 - angle (degrees? converted to radians internally)
//   param_3 - another angle (degrees? converted to radians)
//   param_4 - additional factor (e.g., surface area or mass)

// External constants (inferred from DAT_* references)
extern const float kDegToRad = 0.0174532925f;           // DAT_00e445c8 - degrees to radians
extern const uint32 kFloatSignMask = 0x7FFFFFFF;        // DAT_00e44680 - mask to get absolute float value
extern const float kDeadbandThreshold = 1.0e-10f;       // DAT_00d5ef84 - small threshold for deadband
extern const float kAeroConstant1 = 2.0f;               // _DAT_00d5c458 - constant in tangent computation
extern const float kAeroConstant2 = 0.5f;               // DAT_00d5eee4 - divisor factor
extern const float kAeroConstant3 = 1.0f;               // _DAT_00d5780c - subtractor
extern const float kAeroConstant4 = 0.1f;               // DAT_00d5ef70 - final multiplier

// External helper functions (likely fast math approximations, side-effects unknown)
extern void sinApprox();    // FUN_00b99e20
extern void cosApprox();    // FUN_00b99fcb
extern void tanApprox();    // FUN_00b9c041

// Internal helper: compute tangent using x87 fptan (returns two values on stack, we use the tan)
inline float fptan(float angle) {
    // x87 fptan: pushes 1.0 and tan(angle)
    // We assume the function is implemented via inline assembly in the original code.
    // This is a placeholder; the actual usage suggests angle in radians.
    __asm {
        fld [angle]
        fptan
        fstp st(0) // pop 1.0
    }
    // Return tan(angle) as float
    __asm {
        fstp [angle]
    }
    return angle;
}

float calculateAerodynamicDrag(float param_1, float param_2, float param_3, float param_4) {
    // Convert angles from degrees to radians
    float angle1Rad = param_2 * kDegToRad;
    float angle2Rad = param_3 * kDegToRad;

    // Step 1: Compute 'velocity' term with deadband
    double dVar4 = (double)angle1Rad;
    sinApprox();  // Possibly sets FPU precision? (side effect)
    
    // Mask sign bit and do integer truncation trick
    uint32 uintVal = (uint32)((float)dVar4 * param_1);
    float fVar3 = (float)(uintVal & kFloatSignMask);   // Keep absolute value

    // Compare masked value (redundant but done in original)
    if ((float)((uint32)fVar3 & kFloatSignMask) <= kDeadbandThreshold) {
        fVar3 = 0.0f;   // Deadband: set to zero if below threshold
    } else {
        double dVar5 = (double)angle1Rad;
        cosApprox();    // side effect
        double dVar6 = (double)(angle2Rad * kAeroConstant1);
        tanApprox();    // side effect

        // Compute rational term for drag coefficient
        float divisor = ((float)dVar5 * param_1 * param_4) / ((float)dVar6 * kAeroConstant2)
                        + fVar3 * kAeroConstant1 + fVar3;
        fVar3 = fVar3 / divisor;
    }

    // Step 2: Compute final force
    double dVar5 = (double)angle1Rad;
    cosApprox();    // side effect (again)
    
    // fVar1 = (kAeroConstant3 - fVar3 * kAeroConstant1) * dVar5 * param_1
    float fVar1 = (kAeroConstant3 - fVar3 * kAeroConstant1) * (float)dVar5 * param_1;

    // Compute tangent of angle2Rad * kAeroConstant1
    float fVar2 = fptan((float)((float)angle2Rad * kAeroConstant1));

    // Final result: |dVar4 * fVar1| * kAeroConstant4 + (dVar5 * fVar1 * param_4) / (2 * tan(angle))
    return fabsf((float)dVar4 * fVar1) * kAeroConstant4
           + ((float)dVar5 * fVar1 * param_4) / (fVar2 + fVar2);
}