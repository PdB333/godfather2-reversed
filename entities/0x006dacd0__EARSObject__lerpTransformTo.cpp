// FUNC_NAME: EARSObject::lerpTransformTo
void __thiscall lerpTransformTo(int this, int target, float t)
{
    float clampT;
    float* pClampT;

    // Clamp t to [0, 1], but also support negative? 
    // The code chooses between local_8=0, local_4=0, or param_3.
    // Actually: if t > globalClampMax (0.0 <= t) then use t; else if t < 0 use 0, else use 0.
    // Reconstructed: if (t > _DAT_00d5780c) use local_8=0; if (t < 0) use local_4=0; else use t.
    pClampT = &local_8; // local_8 is uninitialized in code? Actually local_8 is declared but not set before use.
    local_4 = 0.0f;

    if ((t <= _DAT_00d5780c) && (pClampT = &local_4, 0.0f <= t)) {
        pClampT = &t;
    }

    clampT = *pClampT;

    // Lerp 10 consecutive floats at offsets +0x40 to +0x60 (so 5 Vector3? Or something like 2 quaternions + 2 floats?)
    // The float at +0x40..+0x60 is 9 floats (0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c, 0x60).
    // Wait, that's 9 floats, not 10. The code shows 9 lerp assignments (0x40 to 0x60 inclusive, step 4 => 9 floats).
    // +0x40 to +0x60 is 0x20 bytes = 32 bytes = 8 floats? No: 0x60-0x40=0x20=32 bytes/4=8 floats.
    // Actually offsets: 0x40,0x44,0x48,0x4c,0x50,0x54,0x58,0x5c,0x60 = that's 9 floats (0x40 to 0x60 inclusive step 4 gives 9 values: (0x60-0x40)/4+1=9).
    // So it's 9 floats. Possibly a 3x3 matrix? Or a quaternion (4) + another quaternion (4) + 1 extra? 
    // Or perhaps a 3x3 rotation matrix? 3x3=9 floats. Likely a rotation matrix at +0x40.
    // And param_1 (this) and param_2 (target) both have these fields.
    *(float*)(this + 0x40) = (*(float*)(target + 0x40) - *(float*)(this + 0x40)) * clampT + *(float*)(this + 0x40);
    *(float*)(this + 0x44) = (*(float*)(target + 0x44) - *(float*)(this + 0x44)) * clampT + *(float*)(this + 0x44);
    *(float*)(this + 0x48) = (*(float*)(target + 0x48) - *(float*)(this + 0x48)) * clampT + *(float*)(this + 0x48);
    *(float*)(this + 0x4c) = (*(float*)(target + 0x4c) - *(float*)(this + 0x4c)) * clampT + *(float*)(this + 0x4c);
    *(float*)(this + 0x50) = (*(float*)(target + 0x50) - *(float*)(this + 0x50)) * clampT + *(float*)(this + 0x50);
    *(float*)(this + 0x54) = (*(float*)(target + 0x54) - *(float*)(this + 0x54)) * clampT + *(float*)(this + 0x54);
    *(float*)(this + 0x58) = (*(float*)(target + 0x58) - *(float*)(this + 0x58)) * clampT + *(float*)(this + 0x58);
    *(float*)(this + 0x5c) = (*(float*)(target + 0x5c) - *(float*)(this + 0x5c)) * clampT + *(float*)(this + 0x5c);
    *(float*)(this + 0x60) = (*(float*)(target + 0x60) - *(float*)(this + 0x60)) * clampT + *(float*)(this + 0x60);
}