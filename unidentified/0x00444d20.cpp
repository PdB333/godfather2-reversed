// FUN_00444d20: SlotManager::setSlotActive
// Function address: 0x00444d20
// Role: Sets the active state (byte) of a slot (index 0..15). If deactivating a previously active slot,
//       calls a deactivation handler with the slot index and two byte flags stored at +0x195 and +0x196.
// Internal layout: m_slots[16] at offset +0x14, each slot 0x18 bytes. The first byte of each slot is the active flag.
// Offsets +0x195 and +0x196 hold some global state used by the deactivation handler.

void __thiscall SlotManager::setSlotActive(uint slotIndex, char isActive)
{
    // Bounds check: maximum 16 slots
    if (slotIndex >= 16)
        return;

    // Pointer to the slot's active byte
    char* slotActivePtr = reinterpret_cast<char*>(reinterpret_cast<uint>(this) + 0x14 + slotIndex * 0x18);
    if (slotActivePtr == nullptr)
        return;

    if (*slotActivePtr != '\0' && isActive == '\0')
    {
        // Slot was active, now being deactivated – fire deactivation event
        triggerSlotDeactivated(
            slotIndex,
            *(reinterpret_cast<char*>(this + 0x195)),
            *(reinterpret_cast<char*>(this + 0x196))
        );
    }

    // Update the slot's active flag
    *slotActivePtr = isActive;
}