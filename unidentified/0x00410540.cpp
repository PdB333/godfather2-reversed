// Function: 0x00410540 - ControllerManager::GetControllerSlot
// Returns a pointer to the controller state structure for the given index.
// Parameter: controllerIndex - 0-15 for individual controllers, 0x11 for combined/local controller.
// Each controller state block is 0x44 bytes.
// The array of controller states starts at offset 0x2c from this.
int __thiscall ControllerManager::GetControllerSlot(byte controllerIndex) {
    // Special slot 0x11: return the base pointer of the array (index 0? or just the offset)
    if (controllerIndex == 0x11) {
        return (int)(this) + 0x2c;  // +0x2c: base of controller state array
    }
    // For indices 0-15, return the address of the specific slot
    if (controllerIndex < 0x10) {
        return (int)(this) + 0x2c + (uint32_t)controllerIndex * 0x44;  // each slot is 0x44 bytes
    }
    // Invalid index (16 or other) returns 0
    return 0;
}