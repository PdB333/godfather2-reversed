// FUNC_NAME: SlotAllocator::addSlots
void __fastcall SlotAllocator::addSlots(int this, int count)
{
    // +0x1c: pointer to internal data block
    int* dataBlock = *(int**)(this + 0x1c);

    // +0xd (offset 0x34): counter tracking number of used slots
    dataBlock[0xd] += count;

    if (count != 0) {
        do {
            // Compute base index: current tail position minus remaining count
            int baseIndex = dataBlock[0xd] - count;
            count--;

            // Read the slot index from the indices array (+0xae = offset 0x2b8)
            int slotIndex = dataBlock[baseIndex + 0xae];

            // Dereference: *(dataBlock[0]) points to a master table
            // +0x18 gives a pointer to a slot table (each slot is 12 bytes)
            int* slotTable = *(int**)(dataBlock[0] + 0x18);

            // Write the constant value (dataBlock[6] at +0x18) into the slot structure
            // at offset +4 within the 12-byte slot (i.e. second int in the slot)
            slotTable[slotIndex * 3 + 1] = dataBlock[6];
        } while (count != 0);
    }
}