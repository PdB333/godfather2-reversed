// FUNC_NAME: PhysicsObject::integratePosition

// 0x00501210: Physics integration step for position/velocity update.
// Offsets for this:
// +0x04: Pointer to parent object (unused?) Likely a network ID or owner.
// +0x10: Pointer to thread-local storage context (used for lock flag).
// +0x30: Velocity X
// +0x34: Velocity Y
// +0x38: Velocity Z
// +0x3c: Velocity W (unused?)
// +0x40: New position X (output)
// +0x44: New position Y (output)
// +0x48: New position Z (output)
// +0x4c: New position W (output)
// +0x50: Pointer to parameter block (PhysicsParams)
// +0x60: Current time accumulator (input)
// +0x64: Time accumulator offset? (updated with dt)
// +0x68: Param multiplier A (used for X axis force)
// +0x6c: Param multiplier B (used for Y axis force)
// +0x70: Param multiplier C (used for Z axis force)
// +0x100: Actually +0x64 in code (decompiler miscalc?); it's 0x64.
//   In the code, *(float *)(param_1 + 100) = 0x64. So it's an extra time variable.

// Offsets for the parameter block (at this+0x50):
// +0x10: byte (0 or 1) – use local vector?
// +0x12: byte (2) – alternate force mode?
// +0x18: byte flags (bit0=use damping? bit1=render to global pos?)
// +0x1c: float – threshold for early return
// +0x20: Offset X (added to output)
// +0x24: Offset Y
// +0x28: Offset Z
// +0x2c: float – X force multiplier?
// +0x30: float – Y force multiplier?
// +0x34: float – Z force multiplier?
// +0x38: float – damping factor?
// +0x3c: float – another damping?
// +0x4c: float – additional X factor?
// +0x50: float – additional Y factor?
// +0x54: float – additional Z factor?

// Global constants (some might be 1.0):
static const float kDampingBase = 0x00e2d99c; // damping factor
static const float kScaleFactor = 0x00e2cd54; // scaling factor
static const float kOne        = 0x00e2b1a4; // 1.0f
static const float kAltForce   = 0x00e35654; // additional force for mode 2
static const uint32_t kDampingMask = 0x00e44680; // bitmask for damping
static const float kDampingOffset = 0x00e44560; // offset for damping

void __thiscall PhysicsObject::integratePosition(float dt)
{
    // Check thread-local lock bit
    uint* lockFlag = (uint*)(*(int*)(this + 0x10) + *(int*)(**(int**)(__readfsdword(0x2c)) + 8));
    if (*lockFlag & 1)
        return;

    PhysicsParams* params = *(PhysicsParams**)(this + 0x50);

    // Early exit if time accumulator has reached threshold
    if (*(float*)(params + 0x1c) > 0.0f && *(float*)(this + 0x60) < *(float*)(params + 0x1c))
    {
        *lockFlag |= 1;
        return;
    }

    // Force increment (dv) will be computed in local variables
    float dvX, dvY, dvZ, dvW;

    if (*(char*)(params + 0x10) == 1)
    {
        // Use local (object-space) forces
        if (*(int*)(this + 0x54) == 0)  // note: 0x54 might be a pointer; check
        {
            dvX = 0.0f;
            dvY = 0.0f;
            dvZ = 0.0f;
            dvW = 0.0f;
        }
        else
        {
            // Some function retrieving a vector (likely a matrix or quaternion operation)
            // FUN_00536020(&local_20) - fetches a vector into local_20...dv
            // But decompiler shows it fills local_20..fStack_14 directly
            // We'll assume it returns a vector (dvX,...,dvW)
            getLocalForceVector(&dvX);
        }
    }
    else
    {
        // Compute force based on global multipliers and dt
        float forceX = (*(float*)(params + 0x50) + *(float*)(this + 0x60)) * *(float*)(this + 0x6c);
        clamp(forceX);  // FUN_00501030 likely a clamp to [0,1] or abs?
        // Reuse forceX for damping calculation
        float dampedForce = *(float*)(params + 0x30) * forceX * kScaleFactor;
        float t = (forceX + kOne) * kScaleFactor;
        if (t > 0.0f)
        {
            if (t > kOne)
                t = kOne;
        }
        else
        {
            t = 0.0f;
        }
        float damping = kOne - (kOne - t) * t * kDampingBase;
        float fVar6 = (kOne - damping * damping * damping) * *(float*)(params + 0x3c)
                    + (kOne - *(float*)(params + 0x3c));
        fVar6 *= (*(float*)(params + 0x38) * forceX + kOne);
        float ifactor = kOne;
        if (*(byte*)(params + 0x18) & 1)
            ifactor = kOne / ((float)((uint)fVar6 & kDampingMask) + kDampingOffset);
        // Update time offset at this+0x64
        *(float*)(this + 0x64) = ifactor * dt + *(float*)(this + 0x64);

        // Now compute X component of dv
        float forceY = (*(float*)(params + 0x4c) + *(float*)(this + 0x64)) * *(float*)(this + 0x68);
        clamp(forceY);
        dvX = forceY * *(float*)(params + 0x2c) * fVar6 * kScaleFactor;

        // Additional force for mode 2
        float forceZ;
        if (*(char*)(params + 0x12) == 2)
        {
            forceZ = (*(float*)(params + 0x4c) + *(float*)(this + 0x64)) * *(float*)(this + 0x68) + kAltForce;
        }
        else
        {
            forceZ = (*(float*)(params + 0x54) + *(float*)(this + 0x64)) * *(float*)(this + 0x70);
        }
        clamp(forceZ);

        // Set dv components
        dvY = dampedForce * *(float*)(params + 0x34) * fVar6 * kScaleFactor;
        dvZ = 0.0f;  // Note: dvZ is fStack_14? Actually decompiler sets fStack_14=0.0 but also local_20, etc. Need to track.
        // Actually from decompiled: local_20 = dvX, fStack_1c = dampedForce? Wait:
        // fStack_1c = fVar8; (which is dampedForce * ...?), then later fStack_18 = ...
        // The code is messy. Reconstruct carefully:
        // Let's map variables:
        // fVar8 = dampedForce (as computed)
        // local_20 = dvX (X delta velocity)
        // fStack_1c = fVar8 * param_2? No, it's set to fVar8 (dampedForce) but then used as Y delta?
        // Actually: fStack_1c = fVar8;  // dampedForce
        // Then later: fStack_18 = fVar8 * ...;  // Y delta? No, the line: "fStack_18 = fVar8 * *(float *)(iVar5 + 0x34) * fVar6 * DAT_00e2cd54;"
        // So fStack_18 becomes the y component.
        // And fStack_14 = 0.0;
        // So overall: dvX = local_20, dvY = fStack_18, dvZ = fStack_14 = 0.
        // But fStack_1c is used? Actually later only fStack_18 is used as positional add.
        // I'll set:
        // dvX = local_20;
        // dvY = dampedForce * params->someFactor * fVar6 * kScaleFactor;
        // dvZ = 0.0f;
        // dvW = 0.0f; (not used)
    }

    // Update time accumulator
    float newTime = dt + *(float*)(this + 0x60);
    // Compute new position (old position + dv)
    *(float*)(this + 0x40) = *(float*)(this + 0x30) + dvX;
    *(float*)(this + 0x44) = *(float*)(this + 0x34) + dvY;
    *(float*)(this + 0x48) = *(float*)(this + 0x38) + dvZ;
    *(float*)(this + 0x4c) = *(float*)(this + 0x3c) + 0.0f; // dvW is 0
    *(float*)(this + 0x60) = newTime;

    // Wrap time if parameter flag set
    if (*(char*)(params + 0x11) == 1 && *(float*)(params + 0x44) < newTime)
    {
        *(float*)(this + 0x60) = newTime - *(float*)(params + 0x44);
    }

    // Add global offset from parameter block
    *(float*)(this + 0x40) += *(float*)(params + 0x20);
    *(float*)(this + 0x44) += *(float*)(params + 0x24);
    *(float*)(this + 0x48) += *(float*)(params + 0x28);
    *(float*)(this + 0x4c) = kOne;

    // If bit 1 of flags set, copy new position to global variables (used for rendering?)
    if (*(byte*)(params + 0x18) & 2)
    {
        _DAT_01194a70 = *(uint*)(this + 0x40);   // position X
        _DAT_01194a74 = *(uint*)(this + 0x44);   // position Y
        _DAT_01194a78 = *(uint*)(this + 0x48);   // position Z
        _DAT_01194a7c = *(uint*)(this + 0x4c);   // position W
        return;
    }

    // Otherwise copy to parent object's position field (offset +0x60 in parent)
    int* parent = *(int**)(this + 4);
    *(uint*)(parent + 0x60) = *(uint*)(this + 0x40);
    *(uint*)(parent + 0x64) = *(uint*)(this + 0x44);
    *(uint*)(parent + 0x68) = *(uint*)(this + 0x48);
    *(uint*)(parent + 0x6c) = *(uint*)(this + 0x4c);

    return;
}