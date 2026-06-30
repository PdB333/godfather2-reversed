// FUNC_NAME: Allocator::allocateObject
undefined4 Allocator::allocateObject(undefined4 param_1)
{
    int iVar1;
    undefined4 *puVar2;
    undefined4 uVar3;
    undefined4 unaff_retaddr;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    iVar1 = FUN_004168f0(); // getGlobalManager()
    if ((iVar1 != 0) && (*(int *)(iVar1 + 0x14) != 0)) { // +0x14: isInitialized
        puVar2 = (undefined4 *)FUN_009c8f80(); // getAllocator()
        local_c = 2; // Allocation type: maybe kAllocationHeap or kAllocationType
        local_8 = 0x10; // Allocation flags: e.g., kAllocFlagAligned16
        local_4 = 0; // Possibly alignment or memtag
        iVar1 = (**(code **)*puVar2)(0x70, &local_c); // vtable[0] (Allocate) with size 0x70 (112 bytes) and param struct
        if (iVar1 != 0) {
            uVar3 = FUN_00416a70(param_1, unaff_retaddr); // constructObject(this, returnAddress)
            return uVar3;
        }
        return 0;
    }
    return 0;
}