// FUNC_NAME: EntityDataManager::notifyGUIDRemoved
void __thiscall EntityDataManager::notifyGUIDRemoved(void* thisPtr, uint32_t* guidParts)
{
    // guidParts points to two uint32s forming a 64-bit GUID
    uint32_t guidHigh = guidParts[0];
    uint32_t guidLow  = guidParts[1];

    // Lookup object by GUID; returns pointer to internal node or 0
    int* nodePtr = reinterpret_cast<int*>(findObjectByGUID(guidHigh, guidLow));
    void* objectBase = nullptr;
    if (nodePtr != nullptr) {
        // The found node is at offset +0x58 from the actual object base
        objectBase = reinterpret_cast<void*>(nodePtr - 0x58);
    }

    // Prepare output for interface query (will be set if successful)
    void* interfacePtr = nullptr;
    // Query interface with ID 0x55859efa (e.g., "IEventReceiver")
    bool hasInterface = (*(bool (__thiscall **)(void*, uint32_t, void**))(
        *(uint32_t*)objectBase + 0x10))(objectBase, 0x55859efa, &interfacePtr) != 0;

    // Clear flag bit 6 at this+0x178 (e.g., "pendingRemovalFlag")
    *(uint32_t*)((char*)thisPtr + 0x178) &= ~0x40;

    if (hasInterface) {
        // Call virtual function at vtable offset 0x248 on the interface object
        // Passing a pointer to the parent (this - 0x58) as argument
        (*(void (__thiscall **)(void*, void*))(
            *(uint32_t*)interfacePtr + 0x248))(interfacePtr, (char*)thisPtr - 0x58);
    }
}