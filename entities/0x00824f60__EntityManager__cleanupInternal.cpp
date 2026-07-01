// FUNC_NAME: EntityManager::cleanupInternal
// Address: 0x00824f60
// This function cleans up a dynamic array of entity sub-resources and releases a temporary collection.

void __thiscall EntityManager::cleanupInternal(void* thisPtr, uint32_t param2) {
    int local_88; // Holds pointer to sub-object
    undefined4 local_84; // Next pointer in linked list
    void* local_80[23]; // Stack-allocated collection (23 elements)
    int local_24[8];   // Temporary pointer or small object

    // Initialize a local collection from this+0xC0 using the provided param2
    FUN_00824a50(local_80, param2, (int)thisPtr + 0xC0);
    // Set first slot to a known function pointer (vtable? callback?)
    local_80[0] = (void*)&PTR_FUN_00d7343c;

    // If the temporary pointer is non-null, release it
    if (local_24[0] != 0) {
        FUN_004daf90(local_24); // Destructor / free
    }

    uint32_t count = *(uint32_t*)((int)thisPtr + 0xAC); // Number of entities
    uint32_t idx = 0;
    if (count != 0) {
        do {
            int* entityPtr = *(int**)(*(int*)((int)thisPtr + 0xA8) + idx * 4); // Entity pointer from array
            if (entityPtr != 0) {
                // Retrieve sub-object at offset +0x5C
                local_88 = *(int*)(*entityPtr + 0x5C);
                // Clear sub-object's linked list next pointer (offset +0x20) and set it to self-sentinel
                *(undefined4*)(local_88 + 0x20) = 0;
                local_84 = *(undefined4*)(local_88 + 4); // Save original next
                *(int**)(local_88 + 4) = &local_88;       // Make next point to self (remove from list)
                // Mark sub-object as deleted (offset +0x24, bit 0)
                *(uint32_t*)(local_88 + 0x24) |= 1;
                if (local_88 != 0) {
                    FUN_004daf90(&local_88); // Destroy the sub-object (pass pointer-to-pointer for cleanup)
                }
            }
            idx++;
        } while (idx < count);
    }
}