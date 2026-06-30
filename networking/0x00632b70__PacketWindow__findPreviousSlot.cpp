// FUNC_NAME: PacketWindow::findPreviousSlot
// Function address: 0x00632b70
// Role: Searches backwards through a packet list (0x18-byte entries) from a current position,
// decrementing a count by 1 per step and additionally subtracting a value from each entry if its
// flag bit 0 is clear. Returns the index of the entry where the count becomes <= 0, or 0 if not found.
// Stores the result index at this+0x5c.

bool __fastcall PacketWindow::findPreviousSlot(int count, PacketList* list)
{
    uint currentPtr = list->currentPtr;   // +0x14
    uint basePtr = list->basePtr;         // +0x28

    if (count > 0) {
        do {
            if (currentPtr <= basePtr) {
                if (count > 0) {
                    return false; // reached base without satisfying condition
                }
                break;
            }
            count--;
            if ((*(byte*)(currentPtr + 8) & 1) == 0) {
                count -= *(int*)(currentPtr + 0x14);
            }
            currentPtr -= 0x18; // move to previous entry
        } while (count > 0);
    }

    if (currentPtr == basePtr) {
        return false;
    }

    if (count < 0) {
        *(undefined4*)(this + 0x5c) = 0;
        return true;
    }

    // Compute index: (currentPtr - basePtr) / 0x18
    *(int*)(this + 0x5c) = (int)(currentPtr - basePtr) / 0x18;
    return true;
}