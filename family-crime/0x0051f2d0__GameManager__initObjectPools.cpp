// FUNC_NAME: GameManager::initObjectPools
// Address: 0x0051f2d0
// Role: Initializes a manager's object pools, setting up linked lists and vtables.

void GameManager::initObjectPools(void)
{
    // Set vtable for this object (first phase)
    *this = &PTR_LAB_00e38370;

    // Call a virtual function on a sub-object at offset 0x37C04 (0xdf01 * 4)
    // This likely invokes an initialization function from the base class or component.
    (**(code **)(*(int *)this[0xdf01] + 0xc))();

    // Call external initialization (e.g., memory manager setup)
    sub_66E1D0();

    uint32_t* poolArrayEnd = this + 0x10c04; // pointer to end of pool array
    uint32_t* currentPool = this + 0x10c4d; // pointer to start of pool area? Actually used as base for iteration
    int arrayCount = 143; // 0x8f

    do {
        uint32_t* objectBase = currentPool[-0x50]; // dereference to get head node of a linked list
        uint32_t* nextBase = currentPool - 0x50;   // base of this pool slot
        poolArrayEnd -= 0x50; // move to previous pool slot (descending)

        if (objectBase != 0) {
            uint32_t** linkPtr = *(uint32_t***)(objectBase + 1); // +4: next pointer in node
            if (linkPtr == nextBase) {
                // Node is the first and only element; set next to the second element's address
                *(uint32_t**)(objectBase + 4) = *(uint32_t***)(currentPool[-0x4f]);
            }
            else {
                // Traverse the linked list to find the node that points to 'nextBase'
                uint32_t** searchPtr = (uint32_t**)linkPtr[1];
                while (searchPtr != nextBase) {
                    linkPtr = (uint32_t**)linkPtr[1];
                    searchPtr = (uint32_t**)linkPtr[1];
                }
                // Remove 'nextBase' from the list by bypassing it
                linkPtr[1] = *(uint32_t***)(currentPool[-0x4f]);
            }
        }

        arrayCount--;
        // Set vtable for this pool element (second phase)
        *poolArrayEnd = &PTR_LAB_00e38340;
        currentPool = (uint32_t*)(currentPool - 0x50);
    } while (arrayCount >= 0);

    // Initialize 199 sub-objects (e.g., entity slots or reorderable arrays)
    int subObjectCount = 199;
    do {
        sub_5231B0();
        subObjectCount--;
    } while (subObjectCount >= 0);

    // Set final vtable for the manager object
    *this = &PTR_LAB_00e38374;

    // Clear a global flag indicating initialization complete
    DAT_012234d0 = 0;
}