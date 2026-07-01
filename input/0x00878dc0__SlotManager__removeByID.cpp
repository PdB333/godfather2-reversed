// FUNC_NAME: SlotManager::removeByID
// Function at 0x00878dc0 - Removes a slot entry by matching the ID stored at offset +0x48 from the pointed object.
// Assumes a container of 4 slots at this+0xed4, each slot is 0xC bytes: [pointer, ?, activeFlag]
// The ID is obtained by reading *(slot_ptr - 0x48)
// Returns 1 if found and removed, 0 otherwise.

int __thiscall SlotManager::removeByID(int this, int id)
{
    int index;          // uVar2 - loop counter
    int currSlot;       // piVar4 - current slot pointer
    int result;         // uVar1 - return value
    int slotID;         // iVar3 - extracted ID from object

    result = 0;
    index = 0;
    currSlot = this + 0xed4;   // +0xed4: start of 4-slot array, each 12 bytes

    while (true) {
        // Read the pointer at current slot; if null, slotID = 0; else read ID at offset -0x48 from that object
        if (*(int*)currSlot == 0) {
            slotID = 0;
        } else {
            slotID = *(*(int*)currSlot + (-0x48/4));   // equivalent to *(ptr - 0x48)
        }

        if (slotID == id) break;

        index++;
        currSlot += 3;   // advance to next slot (3 ints = 12 bytes)
        if (index > 3) {
            return result;   // not found
        }
    }

    // Found matching slot (index < 4)
    if (index < 4) {
        // Clear the active flag at slot+8 (offset +0xedc + index*12)
        // "activeFlag" at +0xedc corresponding to this slot
        *(int*)(this + (index * 3 + 0x3b7) * 4) = 0;   // equivalent to this + 0xedc + index*12

        // If the slot contains a valid object pointer, release it and null the pointer
        if (*(int*)currSlot != 0) {
            FUN_004daf90(currSlot);   // likely releases the object (destructor or delete)
            *(int*)currSlot = 0;
        }
        result = 1;
    }
    return result;
}