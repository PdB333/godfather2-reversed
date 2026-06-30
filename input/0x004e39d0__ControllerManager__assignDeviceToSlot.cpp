// FUNC_NAME: ControllerManager::assignDeviceToSlot
// Address: 0x004e39d0
// This function assigns a device (ID in eax) and associated data (in edx) to a
// controller slot (index in esi). It first searches a global table of 20 device
// mappings (each 8 bytes: deviceId + flags). If the device ID is already
// assigned to another slot, it clears the bottom two bits of that slot's flags
// (making the slot available). Then it stores the device ID and data into the
// slot's entry. Finally calls an update routine.

// Global arrays (likely static members of ControllerManager):
// m_deviceMapping: array of 20 entries, each 8 bytes: [0] = deviceId, [4] = flags
// m_slotData: array of 20 entries, each 8 bytes: [0] = deviceId assigned to slot, [4] = some data

// The caller ensures ESI = slotIndex, EAX = deviceId, EDX = data, ECX = this (unused)
void __fastcall ControllerManager::assignDeviceToSlot(void* this, int data, int deviceId, int slotIndex)
{
    int i;

    // If slot index is 4, skip the removal of previous mapping (maybe slot 4 is special)
    if (slotIndex != 4) {
        i = 0;
        do {
            // Check if device ID already mapped in the global device list
            if (s_deviceMapping[i] == deviceId) {
                if (i < 20) {
                    // Clear flags bits [1:0] (make slot available)
                    s_deviceMapping[i + 1] &= ~3;
                }
                break;
            }
            i++;
        } while (i < 20);
    }

    // Store the mapping:
    // s_slotDeviceIds[slotIndex] = deviceId
    // s_slotData[slotIndex] = data
    s_slotDeviceIds[slotIndex] = deviceId;
    s_slotData[slotIndex] = data;

    // Post-assignment update (e.g., activate slot, notify input system)
    ControllerManager::updateDeviceAssignments();
}