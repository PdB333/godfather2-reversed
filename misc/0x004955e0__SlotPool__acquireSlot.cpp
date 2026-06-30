// FUNC_NAME: SlotPool::acquireSlot
int __thiscall SlotPool::acquireSlot(uint* this) {
    uint slotIndex = 0; // Track current slot index
    while (true) {
        uint slotIndexLoop = 0;
        // Pointer to current slot (each slot is 0x20 bytes)
        uint* currentSlot = this;
        if (this[0x84] != 0) { // +0x84: number of slots (slotCount)
            do {
                // Read the ticket value from the slot (offset +4 from slot start)
                uint oldTicket = currentSlot[1];
                uint* ticketPtr = currentSlot + 1; // Address of ticket field
                // If ticket does not match the key (offset 0), attempt atomic increment
                if (oldTicket != *currentSlot) {
                    do {
                        LOCK(); // Simulate memory barrier / lock prefix
                        uint currentTicket = *ticketPtr;
                        if (oldTicket == currentTicket) {
                            *ticketPtr = oldTicket + 1; // Atomically increment ticket
                            currentTicket = oldTicket;
                        }
                        UNLOCK();
                        if (currentTicket == oldTicket) { // Successfully captured ticket
                            goto foundSlot;
                        }
                        // Ticket changed; reload and retry
                        oldTicket = *ticketPtr;
                    } while (oldTicket != *currentSlot);
                }
                // Move to next slot
                slotIndexLoop++;
                currentSlot += 0x20 / sizeof(uint); // Each slot is 0x20 bytes
            } while (slotIndexLoop < this[0x84]);
        }
foundSlot:
        if (slotIndexLoop != this[0x84]) {
            // Compute offset into data array using per-slot modulus and base
            // +0x85: array of modulus values for each slot (uint)
            // +0x89: array of base offsets for each slot (uint)
            uint modulus = this[slotIndexLoop + 0x85];
            uint base    = this[slotIndexLoop + 0x89];
            // Each data entry is 0x1c bytes
            return base + (oldTicket % modulus) * 0x1c;
        }
        // No slot found; retry the entire scan
    }
}