// FUNC_NAME: PlayerCrewLeaderComponent::isCrewSlotAvailable

// Function at 0x00705bc0
// Checks if a crew slot (index param_2) is occupied and its corresponding crew member has capacity to accommodate param_3 items.
// Returns 1 if the slot is valid and capacity is sufficient, otherwise 0.
// Slot array is at this+0x18, each entry is 0x14 bytes; first 4 bytes is a pointer to a crew member object.
// The crew member object has a capacity field at offset 0x4c8 (e.g., inventory space, max items).
// A slot is considered empty if the pointer is null or equals the sentinel value 0x48.

bool __thiscall PlayerCrewLeaderComponent::isCrewSlotAvailable(uint slotIndex, uint itemCount)
{
    bool result = false;

    if (slotIndex < 11) // Max crew size? (0-10)
    {
        // +0x18: base of array of crew slot descriptors (each 0x14 bytes)
        int* crewMemberPtr = *(int**)(this + 0x18 + slotIndex * 0x14);

        // Check if slot is occupied (non-null and not sentinel 0x48)
        if (crewMemberPtr != nullptr && crewMemberPtr != (int*)0x48)
        {
            // +0x4c8: capacity field in the crew member object (e.g., m_crewInventoryCapacity or m_maxItems)
            if (itemCount <= *(uint*)(crewMemberPtr + 0x4c8 / 4))
            {
                result = true;
            }
        }
    }

    return result;
}