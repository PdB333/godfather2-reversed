// FUNC_NAME: PacketWindow::updateSlot

void __thiscall PacketWindow::updateSlot(uint slotIndex)
{
    int newSequence;
    int currentValue;
    int entryPtr;
    int node1;
    int node2;

    newSequence = getNextSequenceNumber(); // FUN_004c4a10
    slotIndex = slotIndex * 0x20; // each slot is 32 bytes
    currentValue = *(int *)(*(int *)(this + 0x10) + slotIndex);
    if (currentValue != newSequence) {
        if (*(byte *)(this + 0x3c) != 0) { // slot active flag
            clearSlot(this, 0); // FUN_004c4870(this, 0)
            // store new sequence into the slot
            *(int *)(slotIndex + *(int *)(this + 0x10)) = newSequence;
            entryPtr = *(int *)(this + 0x10);
            // link the slot's data into two linked lists
            node1 = FUN_004c4610(*(int *)(entryPtr + slotIndex), this + 0x24);
            node2 = FUN_004c4610(*(int *)(entryPtr + slotIndex + 4), node1 + 0xc);
            updateSlotList(this, node2 + 0xc); // FUN_004c4730
            *(byte *)(this + 0x18) = 0; // clear dirty flag
            return;
        }
        // just update the slot value if not active
        *(int *)(*(int *)(this + 0x10) + slotIndex) = newSequence;
    }
}