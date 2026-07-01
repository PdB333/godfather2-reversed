// FUNC_NAME: applyRotationWithFlags

void __fastcall applyRotationWithFlags(int thisPtr)
{
    uint flags = *(uint*)(thisPtr + 0x10); // bitfield at this+0x10
    // Read rotation components (x,y,z) from offset 0x108 (typical: 3 floats)
    float rotX = *(float*)(thisPtr + 0x108);
    float rotY = *(float*)(thisPtr + 0x10C);
    float rotZ = *(float*)(thisPtr + 0x110);
    // Global constant for the w component (likely identity quaternion w = 1.0f)
    extern float _DAT_00d5780c; // global float constant
    float rotW = _DAT_00d5780c;

    // Form a quaternion from the loaded data
    struct Quaternion { float x, y, z, w; };
    Quaternion rotation = { rotX, rotY, rotZ, rotW };

    // Priority: bit1 (value 2) > bit0 (value 1) > bit2 (value 4)
    if ((flags >> 1) & 1)          // bit1 set
    {
        applyRotationBlend(&rotation);   // apply blend once
        return;
    }
    if (flags & 1)                 // bit0 set
    {
        applyRotationBlend(&rotation);   // apply blend twice
        applyRotationBlend(&rotation);
        return;
    }
    if ((flags >> 2) & 1)          // bit2 set
    {
        applyRotationBlend(&rotation);   // apply blend twice
        applyRotationBlend(&rotation);
    }
    // No action if no flags set
}