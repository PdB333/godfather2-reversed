//
// Function address: 0x00410330
// Role: Retrieves the set of buttons that were newly pressed this frame for a given controller slot.
// The controller slots are stored in an array at offset +0x2C from 'this', each slot 0x44 bytes.
// Slot structure offsets (relative to slot base):
//   +0x10 : ushort currentButtons (m_CurrentButtons)
//   +0x14 : ushort previousButtons (m_PreviousButtons)
//   +0x3E : char isConnected (m_IsConnected)
//

ushort __thiscall GetButtonsPressed(uint slot) // param_1 = this, param_2 = slot
{
    ushort pressedMask = 0;

    // Slot must be valid (0-15) and not equal to 0x12 (special constant, likely invalid for this query)
    if ((slot != 0x12) && (slot < 0x10))
    {
        // Calculate pointer to the slot's data block
        int slotBase = this + 0x2C + slot * 0x44;

        // Check if the controller is connected
        char connected = *(char *)(this + 0x6A + slot * 0x44); // slotBase + 0x3E
        if (connected != '\0')
        {
            // Compute newly pressed buttons: ~previousButtons & currentButtons
            ushort current = *(ushort *)(slotBase + 0x10);
            ushort previous = *(ushort *)(slotBase + 0x14);
            pressedMask = ~previous & current;
        }
    }

    return pressedMask;
}