// FUNC_NAME: ObjectSlotManager::assignSlot
// Address: 0x00454650
// Role: Assigns an object to a slot in the manager's slot array. Marks the slot as active (status=2) and stores the object's unique identifier.

#pragma pack(push, 1)
struct SlotEntry {
    uint32_t status;    // +0x00: 0 = empty, 2 = active
    uint64_t identifier; // +0x04: object's unique ID (two DWORDs)
};
#pragma pack(pop)

class ObjectSlotManager {
public:
    uint32_t slotCount;        // +0x38: number of allocated slots
    SlotEntry* slotArray;      // +0x34: pointer to array of slot entries

    // __thiscall
    void assignSlot(uint32_t slotIndex, BaseObject* obj) {
        // Validate slot index and object pointer
        if (slotIndex < slotCount && obj != nullptr) {
            // Perform any necessary setup on the object (likely increments ref count or registers it)
            FUN_00481d20(obj, slotIndex);

            // Mark slot as active (status = 2)
            SlotEntry* entry = &slotArray[slotIndex];
            entry->status = 2;

            // Retrieve the object's 64-bit identifier via a virtual function (vtable offset 4)
            // The function takes a pointer to an 8-byte buffer and returns a pointer to the same buffer filled.
            uint8_t buffer[8];  // 8 bytes for identifier
            uint32_t* idParts = (uint32_t*)(*(void (__thiscall**)(BaseObject*, uint8_t*))(*(uintptr_t*)obj + 4))(obj, buffer);
            entry->identifier = *(uint64_t*)idParts;
        }
    }
};