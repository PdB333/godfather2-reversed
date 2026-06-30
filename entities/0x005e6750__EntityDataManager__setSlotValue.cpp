//FUNC_NAME: EntityDataManager::setSlotValue
// Address: 0x005e6750
// Sets a value for an entity slot identified by entityId (lower 16 bits).
// Returns true if successful, false otherwise.

#include <cstdint>

// Global manager pointer (DAT_012234bc)
extern uint8_t* g_pEntityDataManager;

// Structure for the first array (size 0x30, at offset 0x10 from manager base)
struct EntitySlot {
    uint8_t pad_0x00[0x2C];
    uint32_t id; // +0x2C: full entity ID for validation
};

// Structure for the second array (size 0x74, pointed to by offset 0x603c from manager base)
struct DataSlot {
    uint32_t firstField; // +0x00: must be non-zero
    uint8_t pad_0x04[0x04];
    void* targetObject; // +0x08: pointer to another object (e.g., component)
    uint8_t pad_0x0C[0x58]; // up to +0x64
    int32_t value; // +0x64: the value to set
};

// Structure for the target object (pointed to by DataSlot::targetObject)
struct TargetObject {
    uint8_t pad_0x00[0x4A];
    uint16_t flags; // +0x4A: bit 1 set to indicate update
    uint8_t pad_0x4C[0x08];
    int32_t someValue; // +0x54: value stored here as well
};

bool EntityDataManager::setSlotValue(uint32_t entityId, int32_t value)
{
    uint16_t index = static_cast<uint16_t>(entityId & 0xFFFF);
    if (index >= 0x200)
        return false;

    // First array: entity slots at offset 0x10 from manager base
    EntitySlot* slot = reinterpret_cast<EntitySlot*>(g_pEntityDataManager + 0x10 + index * 0x30);
    if (slot == nullptr)
        return false;

    // Validate that the slot's stored ID matches the full entity ID
    if (slot->id != entityId)
        return false;

    // Second array base pointer at offset 0x603c from manager base
    uint8_t* dataArrayBase = *reinterpret_cast<uint8_t**>(g_pEntityDataManager + 0x603c);
    if (dataArrayBase == nullptr)
        return false;

    // Data slots of size 0x74
    DataSlot* dataSlot = reinterpret_cast<DataSlot*>(dataArrayBase + index * 0x74);
    if (dataSlot == nullptr || dataSlot->firstField == 0)
        return false;

    // Store value at offset 0x64
    dataSlot->value = value;

    // If there is a target object pointer at offset 0x08
    if (dataSlot->targetObject != nullptr)
    {
        TargetObject* target = static_cast<TargetObject*>(dataSlot->targetObject);
        // Set flag bit 1 at offset 0x4a
        target->flags |= 2;
        // Store value at offset 0x54
        target->someValue = value;
    }

    return true;
}