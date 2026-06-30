// FUNC_NAME: PacketSlotManager::freeSlot
int __thiscall PacketSlotManager::freeSlot(uint slotIndex)
{
    int result = 0;

    // Check if the slot array exists and index is within range (512 max slots)
    if ((this->m_pSlotArray != nullptr) && (slotIndex < 0x200))
    {
        // Pointer to the specific slot (each slot is 0x74 bytes)
        PacketSlot* slot = &this->m_pSlotArray[slotIndex];

        if (slot != nullptr)
        {
            // If there is a secondary object (e.g., a buffer or child), release it first
            if (slot->m_pSecondaryObj != nullptr)
            {
                releaseSecondaryObject(slot->m_pSecondaryObj); // FUN_005f1ef0
            }

            // If there is a primary object, notify its removal and clear the slot
            if (slot->m_pPrimaryObj != nullptr)
            {
                notifySlotFreed(slotIndex, slot->m_pPrimaryObj); // FUN_005dbc10
                resetSlotCounter(0);                               // FUN_005e5200(0)
                slot->m_pPrimaryObj = nullptr;
                return 1;
            }
            else
            {
                // Primary object already null, just notify with null handle
                notifySlotFreed(slotIndex, 0); // FUN_005dbc10
                result = 1;
            }
        }
    }
    return result;
}