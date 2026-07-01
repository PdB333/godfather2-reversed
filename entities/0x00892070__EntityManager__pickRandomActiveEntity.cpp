// FUNC_NAME: EntityManager::pickRandomActiveEntity

// Function at 0x00892070: Selects a random entity from an internal list that has flag bit 2 set and bit 3 clear.
// Presumed class: EntityManager (or similar collection manager).
// This pointer at param_1.
// Offsets: +0x08 = pointer to array of entity pointers
//          +0x0c = count of entities in array
//          +0x170 (on each entity) = flag bitfield

undefined4 __thiscall EntityManager::pickRandomActiveEntity(void *this_ptr)
{
    int entityCount;
    uint index;
    uint selectedCount;
    uint randVal;
    undefined4 result;

    selectedCount = 0;
    index = 0;
    result = 0;

    if (*(int *)((int)this_ptr + 0xc) != 0) {
        // Iterate over the entity pointer array
        do {
            int entity = *(int *)(*(int *)((int)this_ptr + 8) + index * 4);
            uint flags = *(uint *)(entity + 0x170);

            // Check if bit 2 is set and bit 3 is clear
            if (((flags >> 2) & 1) != 0 && ((flags >> 3) & 1) == 0) {
                uint currentSelection = selectedCount;
                if (selectedCount == 0) {
                    // First selected entity: initialize temporary storage
                    EntityManager::initTempSelectionBuffer(1);  // 0x00891ce0
                    currentSelection = (uint)selectedCount; // selectedCount was 0
                }
                selectedCount = currentSelection + 1;
                // Store entity in temporary array (global/static buffer)
                (g_tempSelectionArray)[currentSelection] = (void *)entity;
            }
            index = index + 1;
        } while (index < *(uint *)((int)this_ptr + 0xc));

        if (selectedCount != 0) {
            randVal = _rand();
            result = (undefined4)(g_tempSelectionArray)[randVal % selectedCount];
        }
    }
    return result;
}