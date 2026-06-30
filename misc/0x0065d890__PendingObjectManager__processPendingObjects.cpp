// FUNC_NAME: PendingObjectManager::processPendingObjects

struct PendingNode {
    int   id;       // +0x00 Unique identifier for this pending object
    int   pad;      // +0x04 Not used in this function
    PendingNode* next; // +0x08 Pointer to next node in the list
};

struct ListContainer {
    int   unknown1; // +0x00
    int   unknown2; // +0x04
    PendingNode* head; // +0x08 Pointer to the first node of the linked list
};

// Global singleton entry point
extern void* GetRegistryManager(); // FUN_00ad8d40

// Virtual method offsets used:
// (vtable + 0x34) -> obtains a registrar object
// (vtable + 0x24) -> obtains an ID registry from that registrar
// (vtable + 0x3c) -> getCount() on the registry
// (vtable + 0x24) -> getItem(index) on the registry (same offset as above, but different object)
// (vtable + 0x0c) -> getID() on each item

void PendingObjectManager::processPendingObjects()  // Address: 0x0065d890
{
    // Step 1: Retrieve the global ID registry from the singleton
    void* registryMgr = GetRegistryManager();
    void* registrar    = nullptr;
    void* idRegistry   = nullptr;
    int   registrySize = 0;

    if (registryMgr != nullptr) {
        // Call vtable+0x34 to get the registrar
        registrar = (*(void* (__thiscall**)(void*))(*(uintptr_t*)registryMgr + 0x34))(registryMgr);
        if (registrar != nullptr) {
            // Call vtable+0x24 on the registrar to get the ID registry
            idRegistry = (*(void* (__thiscall**)(void*))(*(uintptr_t*)registrar + 0x24))(registrar);
            // Call vtable+0x3c on the ID registry to get the number of registered items
            registrySize = (*(int (__thiscall**)(void*, int))(*(uintptr_t*)idRegistry + 0x3c))(idRegistry, 0);
        }
    }

    // Step 2: Retrieve the head of the internal pending list
    ListContainer* listCntr = *(ListContainer**)(this + 0x3C);
    PendingNode*   currentNode = nullptr;

    if (listCntr == nullptr) {
        currentNode = nullptr;
    } else {
        // The head node pointer is stored at offset +0x08 inside the ListContainer
        currentNode = *(PendingNode**)((char*)listCntr + 0x08);
    }

    // Step 3: Iterate over the pending list
    while (currentNode != nullptr) {
        bool foundMatch = false;

        // Search for an item in the global registry with the same ID
        if (registrySize > 0) {
            for (int idx = 0; idx < registrySize; ++idx) {
                // Get the indexed item from the registry
                void* registryItem = (*(void* (__thiscall**)(void*, int))(*(uintptr_t*)idRegistry + 0x24))(idRegistry, idx);
                // Retrieve the ID of that item
                int itemId = (*(int (__thiscall**)(void*))(*(uintptr_t*)registryItem + 0x0C))(registryItem);

                if (itemId == currentNode->id) {
                    // The pending node matches a registered item; skip processing
                    foundMatch = true;
                    break;
                }
            }
        }

        if (!foundMatch) {
            // Node does not yet have a matching registry entry – process it
            processNode(this, currentNode);  // FUN_0065d650 (presumed member function)
        }

        // Advance to the next node in the pending list
        if (listCntr == nullptr) {
            currentNode = nullptr;
        } else {
            currentNode = *(PendingNode**)((char*)listCntr + 0x08);
        }
    }
}