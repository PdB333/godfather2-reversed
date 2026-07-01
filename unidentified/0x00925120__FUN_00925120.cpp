// FUNC_NAME: SomeClass::releaseResourceBlock
void __fastcall SomeClass::releaseResourceBlock(void* thisPtr)
{
    // this +0x80 holds pointer to a resource block
    int* resourceBlock = *(int**)((char*)thisPtr + 0x80);
    if (resourceBlock != nullptr) {
        // Free field at offset 0x3C (slot 15)
        if (resourceBlock[0xf] != 0) {
            earMemoryFree(resourceBlock[0xf]);
        }
        // Perform some memory management step (e.g., return block to heap)
        earMemoryManageStep();
        // Free field at offset 0x14 (slot 5)
        earMemoryFree(resourceBlock[5]);
        // Dereference first field of resourceBlock (likely a sub-allocation)
        int* firstField = resourceBlock[0]; // *resourceBlock
        if (firstField != 0) {
            // Free sub-allocation's child at offset 0x30
            earMemoryFree(*(undefined4*)(firstField + 0x30));
            // Free the sub-allocation itself
            earMemoryFreeNode(firstField);
        }
        // Free the resourceBlock itself
        earMemoryFreeNode(resourceBlock);
    }
    // Clear the pointer
    *(undefined4*)((char*)thisPtr + 0x80) = 0;
    // Notify global memory manager about deallocation
    earMemoryDeallocationNotify();
}