// FUNC_NAME: initializeHandle
void initializeHandle(uint *outHandle, undefined param2, undefined4 param3, undefined4 param4) {
    uint handle;
    undefined4 local_24 = 0, local_20 = 0, local_1c = 0, local_18 = 0;
    byte *local_14 = &LABEL_ADDRESS; // Address of a label in original code (likely unused)
    uint *local_10 = outHandle;
    uint local_8 = 0, local_c = 0;

    handle = FUN_005e4950(DAT_012234bc, &local_24);
    *outHandle = handle;
    if (handle != 0) {
        FUN_005e6580(handle, param3);
        uint index = *outHandle & 0xffff;
        if (index < 0x200) {
            int entryPtr = index * 0x30 + 0x10 + DAT_012234bc;
            if (entryPtr != 0 && *(uint *)(entryPtr + 0x2c) == *outHandle) {
                if (entryPtr != 0 && *(int *)(entryPtr + 0x10) != 0) {
                    *(undefined4 *)(*(int *)(entryPtr + 0x10) + 0x5c) = param4;
                }
            }
        }
        param2 = 0;
        param3 = 0;
        undefined4 *resultPtr = (undefined4 *)FUN_005f0600(DAT_01223514, &param2);
        undefined4 value = (resultPtr != 0) ? *resultPtr : 0;
        byte flag = 0;
        int result2 = FUN_005f0560(value, &param2, &param3);
        if (result2 != 0 && result2 != -0x20) {
            flag = (byte)((*(uint *)(result2 + 0x28) >> 6) & 1);
        }
        *(byte *)(outHandle + 1) = flag; // OutHandle[1] low byte - flag at offset 4
        *(byte *)((int)outHandle + 5) = 0; // Offset 5 set to zero
    }
}