// FUNC_NAME: EARSObject::~EARSObject
void* __thiscall EARSObject::~EARSObject(void* param_1, byte param_2)
{
    int* piVar2;
    int iVar1;

    // Set vtable to base class for proper virtual dispatch during destruction
    *(void***)param_1 = &PTR_FUN_00e37110;

    iVar1 = *(int*)((int)param_1 + 0x10);       // +0x10: pointer to owned object
    if (iVar1 != 0) {
        // Return the owned pointer to a global free list at DAT_01206880 + 0x14
        piVar2 = (int*)(DAT_01206880 + 0x14);   // +0x14: free list head pointer
        *(void***)*piVar2 = &PTR_LAB_01123be8;   // store vtable of freed object type
        *piVar2 = *piVar2 + 4;                   // advance allocation pointer
        *(int*)*piVar2 = iVar1;                 // store the owned pointer
        *piVar2 = *piVar2 + 4;                   // advance again
        *(int*)((int)param_1 + 0x10) = 0;        // clear owned pointer (+0x10)
        *(int*)((int)param_1 + 0x14) = 0;        // clear next field (+0x14)
    }

    if ((param_2 & 1) != 0) {
        // Deallocate the object memory itself
        FUN_009c8eb0(param_1);
    }

    return param_1;
}