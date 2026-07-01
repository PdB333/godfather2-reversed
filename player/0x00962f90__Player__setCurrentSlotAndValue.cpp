// FUNC_NAME: Player::setCurrentSlotAndValue
void __thiscall Player::setCurrentSlotAndValue(int this, int slotIndex, int value)
{
    int *slotValuePtr = nullptr;

    // Store previous current slot index
    *(int *)(this + 0xc0) = *(int *)(this + 0xc4);
    *(int *)(this + 0xc4) = slotIndex;

    // Map slot index to member variable pointer
    switch (slotIndex) {
    case 1:
        slotValuePtr = (int *)(this + 0x1b8);
        break;
    case 2:
        slotValuePtr = (int *)(this + 0x1b0);
        break;
    case 3:
        slotValuePtr = (int *)(this + 0x1dc);
        break;
    case 4:
        slotValuePtr = (int *)(this + 0x1cc);
        break;
    case 5:
        slotValuePtr = (int *)(this + 0x1d0);
        break;
    case 6:
        slotValuePtr = (int *)(this + 0x1bc);
        break;
    case 7:
        slotValuePtr = (int *)(this + 0x1c8);
        break;
    case 9:
        slotValuePtr = (int *)(this + 0x1c4);
        break;
    }

    if (slotIndex == 0) {
        // Slot 0 is stored directly at +0x1a8
        if (*(int *)(this + 0x1a8) == value) goto LAB_00963019;
        *(int *)(this + 0x1a8) = value;
    } else {
        if ((slotValuePtr == nullptr) || (*slotValuePtr == value)) goto LAB_00963019;
        *slotValuePtr = value;
        if (slotIndex == 1) {
            // Callback for slot 1 changes
            FUN_0095cf20(); // likely onSlot1Changed()
        }
    }
    // Mark slot value as dirty (bit 0x400)
    *(uint *)(this + 0x6f4) |= 0x400;

LAB_00963019:
    // Mark general dirty flag (bit 0x20)
    *(uint *)(this + 0x6f4) |= 0x20;
}