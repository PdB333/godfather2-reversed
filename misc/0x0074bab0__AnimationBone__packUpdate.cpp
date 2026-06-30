// FUNC_NAME: AnimationBone::packUpdate
void __thiscall AnimationBone::packUpdate(int thisPtr, undefined4* outputObj)
{
    // Retrieve type identifier from output object's vtable (first method)
    int typeId = (*(int (__thiscall **)())(**(int**)outputObj))();
    
    if (typeId == 0x414678c) {
        // Reset interpolation state (e.g., blend weights, bone snapshot)
        FUN_0080eb00(thisPtr + 0x70);
    }
    else if (typeId == 0x17a70916) {
        float* posVec = nullptr;
        int state = *(int*)(thisPtr + 0xc);
        
        if (state == 1) { // Interpolation mode (blending)
            float delta = FUN_007fd800(); // Returns a time delta or random factor
            // Linear interpolation: start + speed * delta
            float x = (float)(*(float*)(thisPtr + 0x80) * delta + *(float*)(thisPtr + 0x74));
            float y = (float)(*(float*)(thisPtr + 0x84) * delta + *(float*)(thisPtr + 0x78));
            float z = (float)(*(float*)(thisPtr + 0x88) * delta + *(float*)(thisPtr + 0x7c));
            float localPos[3] = { x, y, z };
            posVec = localPos;
        }
        else if (state == 6) { // Fixed/absolute position mode
            posVec = (float*)(thisPtr + 0x9c);
        }
        
        // Set visibility/active flag in output object
        if (*(char*)(thisPtr + 0xe4) == '\0') {
            outputObj[0x2a] &= 0xfffffffe; // Clear bit 0 (invisible/inactive)
        } else {
            outputObj[0x2a] |= 1; // Set bit 0 (visible/active)
        }
        
        // Process the position vector (e.g., transform, normalize)
        FUN_0075cd50(posVec);
        
        // Clear bit 2 in output flags (some other state)
        outputObj[0x2a] &= 0xfffffffb;
        
        // Copy bone transform matrix (12 floats = 48 bytes) from this to output at offset 0x78
        // Offsets: +0xb4 to +0xdc (3x4 affine matrix)
        *(undefined8*)(outputObj + 0x1e) = *(undefined8*)(thisPtr + 0xb4);
        *(undefined8*)(outputObj + 0x20) = *(undefined8*)(thisPtr + 0xbc);
        *(undefined8*)(outputObj + 0x22) = *(undefined8*)(thisPtr + 0xc4);
        *(undefined8*)(outputObj + 0x24) = *(undefined8*)(thisPtr + 0xcc);
        *(undefined8*)(outputObj + 0x26) = *(undefined8*)(thisPtr + 0xd4);
        *(undefined8*)(outputObj + 0x28) = *(undefined8*)(thisPtr + 0xdc);
    }
}