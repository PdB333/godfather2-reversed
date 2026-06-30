// FUNC_NAME: EntityHandle::resolvePointer
undefined4 __fastcall EntityHandle::resolvePointer(int thisPtr)
{
    int *vtablePtr;
    int result;
    int typeId;
    char isMatch;
    int *classInfo;

    vtablePtr = (int *)(thisPtr + 0x54); // +0x54: pointer to vtable or class info

    // Check if the four magic fields match a known GUID or are zero
    if ((((*vtablePtr != 0xBADBFBBA) || (*(int *)(thisPtr + 0x58) != 0xBEEFBEEF) ||
          (*(int *)(thisPtr + 0x5C) != 0xEAC15A55) || (*(int *)(thisPtr + 0x60) != 0x91100911)) &&
         ((*vtablePtr != 0) || (*(int *)(thisPtr + 0x58) != 0) ||
          (*(int *)(thisPtr + 0x5C) != 0) || (*(int *)(thisPtr + 0x60) != 0))))
    {
        // Fields are not the magic signature and not zero — try to resolve via class vtable
        classInfo = (int *)FUN_00446100(vtablePtr, 0); // getClassVtableFromPointer
        if (classInfo != (int *)0x0) {
            typeId = 0;
            // Virtual call to isTypeOfHash (vtable offset 0x10)
            isMatch = (**(code (__thiscall **)(int, int *))(classInfo[4]))(0x6f1d0554, &typeId);
            if (isMatch != '\0' && unaff_ESI != 0) {
                return *(undefined4 *)(unaff_ESI + 0x180); // return cached pointer from caller
            }
            result = FUN_006b95e0(classInfo, 0x43c8ec5b); // findObjectByHash
            if (result != 0) {
                return FUN_008e9640(); // getGlobalInstance
            }
        }
        return 0;
    }
    // Fields match magic or are zero — use the simple pointer at +0x50
    if (*(int *)(thisPtr + 0x50) != 0) {
        return FUN_006b0ee0(*(int *)(thisPtr + 0x50)); // getPointerFromHandle
    }
    return 0;
}