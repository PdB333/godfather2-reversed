// FUNC_NAME: ObjectPool::resetPool
void __fastcall ObjectPool::resetPool(int this)
{
    int count;
    void** itemPtr;
    int i;

    count = *(int *)(this + 0x100);
    if (count != 0) {
        i = 0;
        do {
            // Get pointer from array at offset 4, each entry is 8 bytes, first 4 bytes are pointer
            itemPtr = *(void***)(*(int *)(this + 0x60) + 4 + i * 8);
            releaseItem(itemPtr); // FUN_00949f30 - likely destroys each item
            // Move item to free list: set item's first pointer to current free list head
            *itemPtr = *(void**)(this + 0x5c);
            // Update counters
            *(int *)(this + 0x38) = *(int *)(this + 0x38) - 1; // free count down
            *(int *)(this + 0x34) = *(int *)(this + 0x34) + 1; // allocated count up?  (or other)
            // Update free list head
            *(void**)(this + 0x5c) = itemPtr;
            i++;
        } while (i < count);
    }
    // Reset item count
    *(int *)(this + 0x100) = 0;
    // Free the item array
    freeMemory(*(void**)(this + 0x60)); // FUN_009c8f10
    *(int *)(this + 0x60) = 0;
    *(int *)(this + 0x68) = 0;
    // Call virtual function at vtable+4 (likely a cleanup/destructor step)
    (**(void (__thiscall **)(int))(*(int *)(this + 0x28) + 4))(this);
    // Reset additional fields
    *(int *)(this + 0x10) = 0;
    *(int *)(this + 0x14) = 0;
    // Final cleanup
    finalizeCleanup(); // FUN_005c08f0
}