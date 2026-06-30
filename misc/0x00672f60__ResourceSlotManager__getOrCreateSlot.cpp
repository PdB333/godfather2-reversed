// FUNC_NAME: ResourceSlotManager::getOrCreateSlot
// Function at 0x00672f60: Retrieves or allocates a resource for a given slot index (in ESI) with a specified size.
// Called when a resource slot needs to be prepared (e.g., streaming buffer or object).
// If the slot is not yet used (flag at +0x6c == 0), a new resource is immediately allocated and returned.
// If the slot already has a resource but its size (+0x50) is insufficient, the old resource is freed and a new one is allocated.
// Otherwise returns the existing resource pointer.
// __thiscall: this in EAX, slot index in ESI, newSize on stack (param_1).
// Offsets:
// +0x0C : pointer to a lookup table (e.g., vtable/object array)
// +0x04 : count of allocated objects
// +0x6C : per-slot flag (0 = unused, nonzero = used)
// +0x50 : per-slot size (uint)
// +0x34 : per-slot resource pointer (void*)
// DAT_01206694 : global deallocation function pointer

void* __thiscall ResourceSlotManager::getOrCreateSlot(void* this, int slotIndex, uint newSize) {
    int iVar1;
    void* pvVar2;

    // Check if the slot is uninitialized (flag == 0)
    if (*(int*)((int)this + 0x6c + slotIndex * 4) == 0) {
        pvVar2 = allocateResource(); // FUN_00673070 - allocation function
        return pvVar2;
    }

    // Slot is in use: clear the flag
    *(int*)((int)this + 0x6c + slotIndex * 4) = 0;

    // If current size is insufficient, reallocate
    if (*(uint*)((int)this + 0x50 + slotIndex * 4) < newSize) {
        iVar1 = *(int*)((int)this + 0x34 + slotIndex * 4);
        if (iVar1 != 0) {
            // Unlink from the object table: clear entry at index = (header - 8) * 4 / something
            *(int*)(*(int*)((int)this + 0x0c) + *(int*)(iVar1 - 8) * 4) = 0;
            *(int*)((int)this + 4) = *(int*)((int)this + 4) - 1; // decrement object count
            // Call global deallocation on the allocation base (header - 0x10)
            (*(void(__cdecl*)(void*))DAT_01206694)((void*)(iVar1 - 0x10));
        }
        pvVar2 = allocateResource(); // FUN_00673070
        *(int*)((int)this + 0x34 + slotIndex * 4) = (int)pvVar2;
        *(uint*)((int)this + 0x50 + slotIndex * 4) = newSize;
    }

    // Return the resource pointer (existing or newly allocated)
    return *(void**)((int)this + 0x34 + slotIndex * 4);
}