// FUNC_NAME: SlotPool::allocateSlot
uint* SlotPool::allocateSlot()
{
    int i = 0;
    uint* slotFlags = reinterpret_cast<uint*>(reinterpret_cast<char*>(this) + 0x10); // +0x10: m_slots array start
    do {
        if (*slotFlags & 0x80000000) { // Slot is free (high bit set)
            uint* slot = reinterpret_cast<uint*>(reinterpret_cast<char*>(this) + 0x10 + i * 0x14); // Each slot is 0x14 bytes
            if (slot != nullptr) {
                *slot &= ~0x80000000; // Mark as allocated
                *(int*)(reinterpret_cast<char*>(this) + 0x74) += 1; // +0x74: m_allocatedCount
            }
            return slot;
        }
        i++;
        slotFlags += 5; // Move to next slot (5 uints per slot)
    } while (i < 5); // m_maxSlots = 5
    return nullptr;
}