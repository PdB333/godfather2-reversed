// FUNC_NAME: MeterController::updateSlots
void __thiscall MeterController::updateSlots(int thisPtr, char bDecrease)
{
    // thisPtr points to a class with an array of 20 slots (4 groups of 5 slots each)
    // Each slot is 0x30 bytes, each group is 0xF0 bytes
    // Slot structure:
    // +0x00: current value (int)
    // +0x04: max value (int)
    // +0x08: speed (int)   // rate of change per frame
    // +0x14: state (int)   // 0 = inactive, 3 = locked, other = active
    // Global flag at thisPtr+0x3D4 bit 0 overrides state check

    int* pSlotMax;  // points to max field of current slot (slot start + 4)
    int slotIndex;
    int groupBase;

    pSlotMax = (int*)(thisPtr + 0x24);  // first slot's max field (slot0 starts at thisPtr+0x20)
    slotIndex = 1;  // used to track which slot within group (0-4) and overall index

    do {
        // Process slot index-1 (first slot of group)
        if ((slotIndex - 1 < 0x14) &&
            ((pSlotMax[4] != 0 || ((*(byte*)(thisPtr + 0x3D4) & 1) == 0)) && (pSlotMax[4] != 3)))
        {
            int delta = pSlotMax[1] * 3;  // speed * 3
            if (bDecrease == '\0') {
                // Increase: current = min(current + delta, max)
                delta += pSlotMax[-1];
                if (*pSlotMax <= delta) {
                    delta = *pSlotMax;
                }
            }
            else {
                // Decrease: current = max(current - delta, 0) with underflow check
                if (SBORROW4(pSlotMax[-1], delta) == pSlotMax[-1] + pSlotMax[1] * -3 < 0) {
                    goto LAB_006ac46e;  // skip update if would underflow
                }
            }
            pSlotMax[-1] = delta;  // update current value
        }
LAB_006ac46e:
        // Process slot index (second slot of group)
        if (((-1 < slotIndex) && (slotIndex < 0x14)) &&
            ((pSlotMax[0x10] != 0 || ((*(byte*)(thisPtr + 0x3D4) & 1) == 0)) && (pSlotMax[0x10] != 3)))
        {
            int delta = pSlotMax[0xD] * 3;
            if (bDecrease == '\0') {
                delta += pSlotMax[0xB];
                if (pSlotMax[0xC] <= delta) {
                    delta = pSlotMax[0xC];
                }
            }
            else if (SBORROW4(pSlotMax[0xB], delta) == pSlotMax[0xB] + pSlotMax[0xD] * -3 < 0) {
                goto LAB_006ac4ae;
            }
            pSlotMax[0xB] = delta;
        }
LAB_006ac4ae:
        // Process slot index+1 (third slot)
        if (((-1 < slotIndex + 1) && (slotIndex + 1 < 0x14)) &&
            ((pSlotMax[0x1C] != 0 || ((*(byte*)(thisPtr + 0x3D4) & 1) == 0)) && (pSlotMax[0x1C] != 3)))
        {
            int delta = pSlotMax[0x19] * 3;
            if (bDecrease == '\0') {
                delta += pSlotMax[0x17];
                if (pSlotMax[0x18] <= delta) {
                    delta = pSlotMax[0x18];
                }
            }
            else if (SBORROW4(pSlotMax[0x17], delta) == pSlotMax[0x17] + pSlotMax[0x19] * -3 < 0) {
                goto LAB_006ac4f1;
            }
            pSlotMax[0x17] = delta;
        }
LAB_006ac4f1:
        // Process slot index+2 (fourth slot)
        if (((-1 < slotIndex + 2) && (slotIndex + 2 < 0x14)) &&
            ((pSlotMax[0x28] != 0 || ((*(byte*)(thisPtr + 0x3D4) & 1) == 0)) && (pSlotMax[0x28] != 3)))
        {
            int delta = pSlotMax[0x25] * 3;
            if (bDecrease == '\0') {
                delta += pSlotMax[0x23];
                if (pSlotMax[0x24] <= delta) {
                    delta = pSlotMax[0x24];
                }
            }
            else if (SBORROW4(pSlotMax[0x23], delta) == pSlotMax[0x23] + pSlotMax[0x25] * -3 < 0) {
                goto LAB_006ac546;
            }
            pSlotMax[0x23] = delta;
        }
LAB_006ac546:
        // Process slot index+3 (fifth slot)
        if (((-1 < slotIndex + 3) && (slotIndex + 3 < 0x14)) &&
            ((pSlotMax[0x34] != 0 || ((*(byte*)(thisPtr + 0x3D4) & 1) == 0)) && (pSlotMax[0x34] != 3)))
        {
            int delta = pSlotMax[0x31] * 3;
            if (bDecrease == '\0') {
                delta += pSlotMax[0x2F];
                if (pSlotMax[0x30] <= delta) {
                    delta = pSlotMax[0x30];
                }
            }
            else if (SBORROW4(pSlotMax[0x2F], delta) == pSlotMax[0x2F] + pSlotMax[0x31] * -3 < 0) {
                goto LAB_006ac59b;
            }
            pSlotMax[0x2F] = delta;
        }
LAB_006ac59b:
        // Advance to next group (5 slots)
        int nextSlotIndex = slotIndex + 4;
        pSlotMax += 0x3C;  // advance by 0xF0 bytes (5 slots * 0x30)
        slotIndex += 5;
        if (0x13 < nextSlotIndex) {
            return;
        }
    } while (true);
}