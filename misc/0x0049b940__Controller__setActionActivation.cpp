// FUNC_NAME: Controller::setActionActivation
void Controller::setActionActivation(int actionId, int activationLevel) // actionId in EAX, activationLevel on stack
{
    // +0xcc: mapping from abstract action ID to concrete action index (array of ints, 4 bytes each)
    int actionIndex = *(int *)(this + 0xcc + actionId * 4);
    if (actionIndex != 0x10) {
        // Virtual call: translate action index to storage slot index (via vtable at this+4)
        int storageSlot = (*(code **)(**(int **)(this + 4) + 0xc))(actionIndex);
        uint bitMask = 1 << (storageSlot & 0x1f);
        uint currentFlags = (uint)*(ushort *)(this + 0x10c);
        
        // Check if this action slot is currently blocked
        if ((currentFlags & bitMask) == 0) {
            if (activationLevel != 0) {
                // Set active: add bit to flags and store activation level
                *(ushort *)(mActionStates + 0x10) |= (ushort)bitMask;
                *(byte *)(mActionStates + storageSlot + 0x16) = 0xff; // store max level?
            } else {
                // Clear active: remove bit and store 0
                *(ushort *)(mActionStates + 0x10) &= ~(ushort)bitMask;
                *(byte *)(mActionStates + storageSlot + 0x16) = 0;
            }
            return;
        }
        
        // Action slot is blocked/permanent
        if (activationLevel >= *(int *)(this + 0xb4)) { // max threshold
            *(ushort *)(mActionStates + 0x10) |= (ushort)bitMask;
            *(byte *)(mActionStates + storageSlot + 0x16) = (byte)activationLevel;
        } else if (activationLevel <= *(int *)(this + 0xb0)) { // min threshold
            *(ushort *)(mActionStates + 0x10) &= ~(ushort)bitMask;
        }
        // Otherwise, just store the activation level without changing flag
        *(byte *)(mActionStates + storageSlot + 0x16) = (byte)activationLevel;
    }
}