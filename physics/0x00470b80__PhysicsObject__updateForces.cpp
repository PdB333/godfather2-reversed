// FUNC_NAME: PhysicsObject::updateForces

void __thiscall PhysicsObject::updateForces(int param_2, float param_3)
{
    // Local vector structs: three 3D vectors each followed by an int (padding)
    // Uses a helper to generate force vectors based on input index and scaled time
    float fLocal_50; // Vector1 X
    float fStack_4c; // Vector1 Y
    float fStack_48; // Vector1 Z
    int iDummy1;
    float fLocal_40; // Vector2 X
    float fStack_3c; // Vector2 Y
    float fStack_38; // Vector2 Z
    int iDummy2;
    float fLocal_30; // Vector3 X
    float fStack_2c; // Vector3 Y
    float fStack_28; // Vector3 Z
    int iDummy3;

    // Global scale factor
    float globalTimeScale = *(float*)0x00e44748;

    // Generate force vectors (likely from input or control)
    GetForceVector(&fLocal_50, param_2, param_3 * globalTimeScale, 0);

    // Scale vectors by per-component factors stored at offset 0x134, 0x138, 0x13C
    // (these are at param_1[0x4d], param_1[0x4e], param_1[0x4f])
    float scale1 = *(float*)(this + 0x134);
    fLocal_50 *= scale1;
    fStack_4c *= scale1;
    fStack_48 *= scale1;

    float scale2 = *(float*)(this + 0x138);
    fLocal_40 *= scale2;
    fStack_3c *= scale2;
    fStack_38 *= scale2;

    float scale3 = *(float*)(this + 0x13C);
    fLocal_30 *= scale3;
    fStack_2c *= scale3;
    fStack_28 *= scale3;

    // Store vectors into object state (offset 0xD0 = 0x34 * 4)
    *(int*)(this + 0xD0) = (int)fLocal_50;   // +0xD0: mForce1X
    *(int*)(this + 0xD4) = (int)fStack_4c;   // +0xD4: mForce1Y
    *(int*)(this + 0xD8) = (int)fStack_48;   // +0xD8: mForce1Z
    *(int*)(this + 0xDC) = 0;                 // +0xDC: padding (zeroed)

    *(int*)(this + 0xE0) = (int)fLocal_40;   // +0xE0: mForce2X
    *(int*)(this + 0xE4) = (int)fStack_3c;   // +0xE4: mForce2Y
    *(int*)(this + 0xE8) = (int)fStack_38;   // +0xE8: mForce2Z
    *(int*)(this + 0xEC) = 0;                 // +0xEC: padding

    *(int*)(this + 0xF0) = (int)fLocal_30;   // +0xF0: mForce3X
    *(int*)(this + 0xF4) = (int)fStack_2c;   // +0xF4: mForce3Y
    *(int*)(this + 0xF8) = (int)fStack_28;   // +0xF8: mForce3Z
    *(int*)(this + 0xFC) = 0;                 // +0xFC: padding

    // Copy quaternion/rotation from offset 0xC0 to 0x100
    // 64-bit value at +0xC0 (param_1[0x30])
    unsigned long long quat = *(unsigned long long*)(this + 0xC0);
    *(int*)(this + 0x100) = (int)(quat & 0xFFFFFFFF);      // +0x100: mQuaternionLow
    *(int*)(this + 0x104) = (int)(quat >> 32);             // +0x104: mQuaternionHigh

    // Copy extra int from +0xC8 to +0x108
    *(int*)(this + 0x108) = *(int*)(this + 0xC8);          // +0x108: mTimestamp

    // Set final field to global constant
    *(int*)(this + 0x10C) = *(int*)0x00e2b1a4;             // +0x10C: mSomeGlobal

    // Call internal update (vtable + 0x68)
    ((void(__thiscall*)(PhysicsObject*))(*(void***)this)[0x1A])();  // vtable index 0x68/4 = 0x1A
}