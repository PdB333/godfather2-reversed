// FUNC_NAME: Entity::cleanup

void __thiscall Entity::cleanup(int thisPtr)
{
    int childBase;
    int *pPtr;
    int localResult;

    // Clean up child objects at offsets +0xcc, +0x128, +0x184
    // Each child object has a backreference at +0x158 that needs clearing
    if ((*(int *)(thisPtr + 0xcc) != 0) && (*(int *)(thisPtr + 0xcc) != 0x48)) {
        childBase = (*(int *)(thisPtr + 0xcc) == 0) ? 0 : (*(int *)(thisPtr + 0xcc) - 0x48);
        if (*(int *)(childBase + 0x158) != 0) {
            if (*(int *)(thisPtr + 0xcc) == 0)
                childBase = 0;
            else
                childBase = *(int *)(thisPtr + 0xcc) - 0x48;
            *(int *)(childBase + 0x158) = 0;
        }
    }
    if ((*(int *)(thisPtr + 0x128) != 0) && (*(int *)(thisPtr + 0x128) != 0x48)) {
        childBase = (*(int *)(thisPtr + 0x128) == 0) ? 0 : (*(int *)(thisPtr + 0x128) - 0x48);
        if (*(int *)(childBase + 0x158) != 0) {
            if (*(int *)(thisPtr + 0x128) == 0)
                childBase = 0;
            else
                childBase = *(int *)(thisPtr + 0x128) - 0x48;
            *(int *)(childBase + 0x158) = 0;
        }
    }
    if ((*(int *)(thisPtr + 0x184) != 0) && (*(int *)(thisPtr + 0x184) != 0x48)) {
        childBase = (*(int *)(thisPtr + 0x184) == 0) ? 0 : (*(int *)(thisPtr + 0x184) - 0x48);
        if (*(int *)(childBase + 0x158) != 0) {
            if (*(int *)(thisPtr + 0x184) == 0)
                childBase = 0;
            else
                childBase = *(int *)(thisPtr + 0x184) - 0x48;
            *(int *)(childBase + 0x158) = 0;
        }
    }

    // Reset local state
    FUN_008e35f0(); // some sub-cleanup
    pPtr = (int *)(thisPtr + 0x1c4);
    *(int *)(thisPtr + 0x1dc) = -1; // +0x1dc: maybe a timer or state
    *(char *)(thisPtr + 0x1a5) = 0; // +0x1a5: flag
    *(int *)(thisPtr + 0x1a8) = 0;  // +0x1a8: counter
    *(char *)(thisPtr + 0x1a4) = 0; // +0x1a4: flag
    if (*pPtr != 0) {
        FUN_004daf90(pPtr); // release something (maybe a string or memory)
        *pPtr = 0;
    }
    // Clear a 4-word region (possibly bounding box or some data)
    *(int *)(thisPtr + 0x1d8) = 0;
    *(int *)(thisPtr + 0x1d4) = 0;
    *(int *)(thisPtr + 0x1d0) = 0;
    *(int *)(thisPtr + 0x1cc) = 0;
    // Clear a bit in flags at +0x84 (bit 19-31 cleared)
    *(unsigned int *)(thisPtr + 0x84) &= 0xfff8ffff;

    // Check if the resource identifier (4 ints at +0x74) is a known null/sentinel
    if ((((*(int *)(thisPtr + 0x74) != -0x45245246) ||
          (*(int *)(thisPtr + 0x78) != -0x41104111) ||
          (*(int *)(thisPtr + 0x7c) != -0x153ea5ab) ||
          (*(int *)(thisPtr + 0x80) != -0x6eeff6ef)) &&
         ((*(int *)(thisPtr + 0x74) != 0) ||
          (*(int *)(thisPtr + 0x78) != 0) ||
          (*(int *)(thisPtr + 0x7c) != 0) ||
          (*(int *)(thisPtr + 0x80) != 0)))) {
        pPtr = (int *)FUN_00446100((int *)(thisPtr + 0x74), 0); // lookup resource
        if (pPtr != 0) {
            localResult = 0;
            char callResult = (*(code **)(*pPtr + 0x10))(0xf4636937, &localResult); // virtual release
            int result = localResult;
            if ((callResult != 0) && (localResult != 0)) {
                FUN_009509a0(0, 0);
                FUN_00950550(0, 0);
                FUN_009506a0(0);
                FUN_009504e0(0, 0);
                FUN_00950540(0);
                FUN_009504d0(0);
                FUN_009211b0(result);
                FUN_0094b190(result);
            }
        }
    }
    FUN_008e6270(thisPtr); // base cleanup
    return;
}