// FUNC_NAME: InputManager::updateButtonMapping
// Function address: 0x0049ab20
// Role: Updates a single button mapping slot from an input event timestamp.
// Uses ESI as slot index (0-15). Writes mapped button index to mapping array
// at offset +0x16, updates bitfield at +0x10, and synchronizes activation state
// at object offset +0x190. Fires notification if state change matches required bit.

void InputManager::updateButtonMapping(void* pMapping) // param_2 = mapping structure (ControllerMapping?)
{
    // unaff_ESI holds the slot index (0..15), provided by caller (likely loop in FUN_0049abe0)
    uint slotIndex = unaff_ESI; // Compiler likely kept in ESI across call

    // Virtual call: get current timestamp/sequence from some engine system
    // Offset +4 in 'this' points to a vtable pointer; vtable entry +12 (0xc) is a function returning uint64
    uint64_t timestamp = (**(uint64_t (__thiscall**)(void*))(*(int*)((char*)this + 4) + 0xc))();

    int mappedButton = FUN_0049aad0(timestamp); // Convert timestamp to button index (0-15) or -1 if invalid

    if (mappedButton != -1)
    {
        if (slotIndex < 16)
        {
            // Write button index into mapping array at offset +0x16
            *((char*)pMapping + 0x16 + slotIndex) = (char)mappedButton;

            // Set or clear the corresponding bit in a 16-bit flag at +0x10
            ushort bitMask = (ushort)(1 << (slotIndex & 0x1f));
            if (mappedButton == 0)
            {
                *(ushort*)((char*)pMapping + 0x10) &= ~bitMask;
            }
            else
            {
                *(ushort*)((char*)pMapping + 0x10) |= bitMask;
            }
        }

        // Compare with current activation state at object offset +0x190 (bool array per slot)
        bool currentState = *(bool*)((char*)this + 0x190 + slotIndex);
        bool newState = (mappedButton != 0);
        byte notifyFlag = 0;

        if (currentState == newState)
        {
            if (newState)
                notifyFlag = 2;
        }
        else
        {
            // Changed state: flag = 4 if new state is true, else 2? (bitwise logic)
            notifyFlag = (byte)((-(newState) & 0xfdU) + 4); // yields 4 if newState true, else 2
        }

        // Update stored state
        *(bool*)((char*)this + 0x190 + slotIndex) = newState;

        // Check if the high byte of timestamp matches notifyFlag? (bitwise &)
        if ((notifyFlag & (byte)(timestamp >> 48)) != 0)
        {
            FUN_0049a560(this, timestamp, this, pMapping); // Notify about mapping change
        }
    }
}