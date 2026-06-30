// FUNC_NAME: Entity::updateWorldTransform
void __thiscall Entity::updateWorldTransform(int* thisPtr, Matrix4x4* parentMatrix, void* param_3)
{
    float fVar1;
    char cVar2;
    int iVar3;
    int* piVar4;
    int* piVar5;
    // Stack arrays: 16 bytes, 48 bytes, then local matrix (64 bytes = 16 ints)
    // Ghidra may have mis-sized local_50 as 12 ints, but loop copies 16 ints.
    undefined1 auStack_90[16];
    undefined1 auStack_80[48];
    int local_50[16]; // 64 bytes, copy of local matrix
    float local_20 = 0.0f;
    float local_1c = 0.0f;
    float local_18 = 0.0f;

    // Combine parent matrix with something (param_3 likely another matrix or extra data)
    FUN_0046fbc0(parentMatrix, param_3);

    // Fetch euler angles: pitch, yaw, roll at offsets +0x4d, +0x4e, +0x4f (0x134, 0x138, 0x13c bytes)
    fVar1 = *(float*)(thisPtr + 0x4d); // pitch
    // Copy local matrix from this+0x34 (16 floats = 64 bytes) to stack
    piVar4 = (int*)(thisPtr + 0x34);
    piVar5 = local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3--) {
        *piVar5 = *piVar4;
        piVar4++;
        piVar5++;
    }
    local_20 = 0.0f;
    local_1c = 0.0f;
    local_18 = 0.0f;

    // Check if any euler angle difference exceeds a threshold (wrap-around detection)
    // DAT_00e2b1a4: likely half-rotation (PI) or zero offset
    // DAT_00e44680: bitmask for sign/angle modulo (interpreted as uint)
    // DAT_00e44598: threshold for allowable angle change
    uint pitchDiff = (uint)(fVar1 - DAT_00e2b1a4) & (uint)DAT_00e44680;
    uint yawDiff   = (uint)(*(float*)(thisPtr + 0x4e) - DAT_00e2b1a4) & (uint)DAT_00e44680;
    uint rollDiff  = (uint)(*(float*)(thisPtr + 0x4f) - DAT_00e2b1a4) & (uint)DAT_00e44680;
    if (DAT_00e44598 < (float)pitchDiff ||
        DAT_00e44598 < (float)yawDiff   ||
        DAT_00e44598 < (float)rollDiff) {
        // Recompute matrix from euler angles
        FUN_0043a2a0(local_50, local_50);
    }

    // Fetch pointer to child/derived object at offset +0xba (0x2e8 bytes)
    iVar3 = *(int*)(thisPtr + 0xba);

    // Virtual call at vtable+0x19c: returns a flag (probably "visible" or "active")
    cVar2 = (*(char (__thiscall **)(int*))(*(int*)thisPtr + 0x19c))(thisPtr);
    if (cVar2 == '\0') {
        if (iVar3 != 0) {
            // Propagate transformation to child object
            FUN_004b59d0(local_50, auStack_80); // matrix multiplication (local * child?)
            FUN_00aa3930(auStack_80);           // convert to quaternion or decompose
            FUN_009f4c70(auStack_90);           // apply to child transform
        }
    }
    else {
        // Alternative path: static update function
        FUN_0055db80();
    }

    // Final virtual call at vtable offset 600 (0x258) – likely post-update or render setup
    (*(void (__thiscall **)(int*))(*(int*)thisPtr + 600))();
    return;
}