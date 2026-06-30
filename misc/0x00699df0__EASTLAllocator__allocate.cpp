//FUNC_NAME: EASTLAllocator::allocate
void __thiscall EASTLAllocator::allocate(int thisPtr, int *outPtr, int sizeOrPtr, int pairPtr, char flag)
{
    int iVar1;
    int uVar2;

    // Check if flag is false and sizeOrPtr is not equal to this+4 (possibly a stored pointer)
    if ((flag == '\0') && (sizeOrPtr != thisPtr + 4)) {
        // Validate something at sizeOrPtr+0x10
        iVar1 = validate(sizeOrPtr + 0x10);
        if (-1 < iVar1) {
            uVar2 = 1;
            goto LAB_00699e22;
        }
    }
    uVar2 = 0;

LAB_00699e22:
    // Debug allocation check from EASTL allocator.h line 0xe9
    iVar1 = debugAllocationCheck(0x30, "EASTL", 0, 0,
                                 "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    if (iVar1 != -0x10) {
        // Destroy two objects at pairPtr and pairPtr+0x10
        destroy(pairPtr);
        destroy(pairPtr + 0x10);
    }

    // Perform actual allocation/construction
    doAllocate(iVar1, sizeOrPtr, thisPtr + 4, uVar2);

    // Increment allocation count at this+0x14
    *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + 1;

    // Store result
    *outPtr = iVar1;
    return;
}