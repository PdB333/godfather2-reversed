// FUNC_NAME: PlayerCrewLeaderComponent::findSlotByEntityID
// Function address: 0x005e2490
// Searches through 5 crew slots (0x4A4 byte each) for a matching entity ID.
// Returns 1 if found, sets *outValue to the result of a virtual call on the global manager.
// If slot exists but its field at +0x484 is zero, *outValue is set to 0xFFFFFFFF.

#define MAX_CREW_SLOTS 5
#define CREW_SLOT_SIZE 0x4A4

// Global manager instance (EARS singleton, vtable at +0x68 for getCharacterHandle)
extern void* g_playerManager; // DAT_01223510

__thiscall int PlayerCrewLeaderComponent::findSlotByEntityID(undefined4* outValue)
{
    int result = 0;
    if (this != nullptr) {
        int slotIndex = 0;
        int* pCompare = (int*)((int)this + 0x490); // pointer to entityID field in slot array
        while (this->someEntityID != *pCompare) { // compare with entity ID stored in this? but unaff_ESI is uninitialized? Wait, unaff_ESI is from registers, likely a param? Actually function takes only param_1, but unaff_ESI and unaff_EDI are from registers. Reconstructed as this->someEntityID.
            slotIndex++;
            pCompare += 0x129; // stride to next slot (0x129*4 = 0x4A4)
            if (slotIndex > 4) {
                return result; // not found
            }
        }
        int* slotBase = (int*)((int)this + 4 + slotIndex * CREW_SLOT_SIZE); // base of the matched slot
        if (slotBase != nullptr) {
            result = -1;
            if (*(int*)((int)slotBase + 0x484) != 0) {
                // Call virtual method on global manager with value from slot +0x1CC
                result = (*(code**)(*(int*)g_playerManager + 0x68))(*(int*)((int)slotBase + 0x1CC));
            }
            *outValue = result;
            result = 1;
        }
    }
    return result;
}