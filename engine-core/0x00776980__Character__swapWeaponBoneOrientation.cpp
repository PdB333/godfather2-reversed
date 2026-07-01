// FUNC_NAME: Character::swapWeaponBoneOrientation
void __fastcall Character::swapWeaponBoneOrientation(int thisPtr)
{
    int* pTargetObj = *(int**)(thisPtr + 0x5c); // pointer to target object (e.g., SimNpc)
    uint flags = *(uint*)(thisPtr + 0xac);
    // Toggle bit 1 (0x2) at offset 0xac – possible "swap enabled" flag
    if ((flags >> 1 & 1) == 0) {
        *(uint*)(thisPtr + 0xac) = flags | 2;
    } else {
        *(uint*)(thisPtr + 0xac) = flags & 0xfffffffd;
    }

    // Swap two float pairs: (0x80,0x84) <-> (0x88,0x8c)
    // Likely current and previous orientation (quaternion parts or two 2D vectors)
    float valA = *(float*)(thisPtr + 0x80);
    float valB = *(float*)(thisPtr + 0x84);
    float* pSwap = (float*)(thisPtr + 0x80);
    *pSwap = *(float*)(thisPtr + 0x88);
    *(float*)(thisPtr + 0x84) = *(float*)(thisPtr + 0x8c);
    *(float*)(thisPtr + 0x88) = valA;
    *(float*)(thisPtr + 0x8c) = valB;

    // If target object exists, copy the first swapped pair to target's offsets 0x860/0x864
    // These might be weapon bone pivot/offset slots
    if (pTargetObj != 0) {
        *(float*)(pTargetObj + 0x860) = *pSwap;
        *(float*)(pTargetObj + 0x864) = *(float*)(thisPtr + 0x84);
    }

    // Check state at offset 0x70: if not zero and not 0x48, call helper
    // 0x48 likely corresponds to "idle" or "no weapon" state
    if (*(int*)(thisPtr + 0x70) != 0 && *(int*)(thisPtr + 0x70) != 0x48) {
        FUN_005430c0(pTargetObj, pSwap); // update something with the swapped orientation
    }

    // Compute time-based value at offset 0xa0 (e.g., animation progress)
    float base = (float)DAT_01205224; // global frame count or delta
    if (DAT_01205224 < 0) {
        base = base + DAT_00e44578; // adjust negative values
    }
    *(float*)(thisPtr + 0xa0) = base + _DAT_00d5c458;

    // Retrieve manager (e.g., RenderManager) and set weapon bone transform
    int* mgr = (int*)FUN_00800a90();
    if (mgr != 0) {
        (**(void (__thiscall**)(int*))(*mgr + 0x7c))(); // begin bone update
        (**(void (__thiscall**)(int*, int, const char*, int))(*mgr + 0x154))(
            pTargetObj, "r_weapon", 0); // set weapon bone from target object
    }
}