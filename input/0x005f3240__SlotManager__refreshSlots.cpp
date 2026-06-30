// FUNC_NAME: SlotManager::refreshSlots
int SlotManager::refreshSlots(int param_2, bool checkPriority)
{
    ushort counter;
    int retVal;
    int slot;
    byte step;
    byte bVar6;
    byte bVar6;
    uint uVar7;
    undefined4 uStack;

    int result = 0;
    if (this == 0) {
        return result;
    }

    // parent manager structure at +0x08
    ManagerState* parent = *(ManagerState**)(this + 0x08);
    byte currentIndex = *(byte*)(this + 0x6e);                // +0x6e: head index
    byte maxSlots = *(byte*)(this + 0x6f);                    // +0x6f: total number of slots

    // Determine iteration step: 2 if parent flags has bit0 set (double buffered?), else 1
    step = ((*(byte*)(parent + 0x08) & 1) != 0) ? 2 : 1;

    // Temporary variable for loop count (embedded in uStack)
    uStack._0_3_ = CONCAT12(currentIndex, (ushort)uStack);
    uStack = (uint)(uint3)uStack;

    // Loop through slots starting at currentIndex, stepping by step
    if (*(byte*)(this + 0x6f) != 0) {
        do {
            slot = *(int*)(this + 0x0c + (uint)currentIndex * 4); // activeSlots array at +0x0c
            if (slot == 0) {
                // Empty slot – if double-buffered, also clear reserve slot at +0x10
                if (step > 1 && *(int*)(this + 0x10 + (uint)currentIndex * 4) != 0) {
                    FUN_005f16b0();                     // free the reserve
                    *(int*)(this + 0x10 + (uint)currentIndex * 4) = 0;
                    // Update counter at +0x6c (8-step counter)
                    counter = *(ushort*)(this + 0x6c);
                    *(ushort*)(this + 0x6c) = (byte)(((char)(counter >> 3) + -1) * '\b' ^ (byte)counter) & 0x78 ^ counter;
                }
                break;
            }
            // Check the slot's "lifetime" or "distance" at +0x18
            int slotValue = *(int*)(slot + 0x18);
            // If checkPriority is true, threshold is 1; otherwise threshold is 0
            // Free the slot if value is less than threshold OR zero
            if ((slotValue < (int)(uint)(checkPriority != '\0')) || (slotValue == 0)) {
                FUN_005f16b0();                         // free the slot object
                uVar7 = (uint)currentIndex;
                *(int*)(this + 0x0c + uVar7 * 4) = 0;   // clear active slot
                // Update counter
                counter = *(ushort*)(this + 0x6c);
                *(ushort*)(this + 0x6c) = (byte)(((char)(counter >> 3) + -1) * '\b' ^ (byte)counter) & 0x78 ^ counter;
                if (step > 1 && *(int*)(this + 0x10 + uVar7 * 4) != 0) {
                    FUN_005f16b0();
                    *(int*)(this + 0x10 + uVar7 * 4) = 0;
                    // Another counter update
                    counter = *(ushort*)(this + 0x6c);
                    *(ushort*)(this + 0x6c) = (byte)(((char)(counter >> 3) + -1) * '\b' ^ (byte)counter) & 0x78 ^ counter;
                }
                break;
            }
            // Advance by step, wrap around if needed
            currentIndex = currentIndex + step;
            uStack._0_3_ = CONCAT12(currentIndex, (ushort)uStack);
            if (*(byte*)(this + 0x6f) <= currentIndex) {
                uStack._2_1_ = 0;
                currentIndex = uStack._2_1_;
                uStack._0_3_ = (uint3)(ushort)uStack;
            }
            // Increment loop counter
            uStack._3_1_ = uStack._3_1_ + step;
        } while (uStack._3_1_ < *(byte*)(this + 0x6f));
    }

    // After the sweep, if the loop terminated normally (didn't break) -> allocate new slots
    if (uStack._3_1_ < *(byte*)(this + 0x6f)) {
        // Allocate up to 'step' new slots starting at the saved index
        byte allocIndex = 0;
        if (step != 0) {
            do {
                int newSlot = FUN_005f10d0();              // allocate new slot object
                if (newSlot == 0) {
                    // Allocation failed – rollback any partial allocations
                    if (allocIndex != 0) {
                        // For each previously allocated slot in this batch:
                        for (byte idx = 0; idx < allocIndex; idx++) {
                            int failedSlot = *(int*)(this + 0x0c + ((uint)idx + (uint)uStack._2_1_) * 4);
                            // Send an "unlink" event using the slot's ID and value
                            FUN_005dbc10(*(ushort*)(failedSlot + 8), *(int*)(failedSlot + 0x18));
                            // Call a global function via pointer (probably engine-specific dispatch)
                            (**(code**)(*DAT_01223510 + 0x20))(*(ushort*)(failedSlot + 8));
                            FUN_005dbc10(*(ushort*)(failedSlot + 8), *(int*)(failedSlot + 0x18));
                            if ((*(byte*)(failedSlot + 0x10) & 0x40) == 0) {
                                FUN_005f1660();            // some cleanup
                            }
                            // Reset remaining fields
                            *(int*)(failedSlot + 0x24) = 0;
                            *(int*)(failedSlot + 0x28) = 0;
                            *(int*)(failedSlot + 0x2c) = 0;
                            *(int*)(this + 0x0c + ((uint)idx + (uint)uStack._2_1_) * 4) = 0;
                        }
                    }
                    goto endLabel;
                }
                // Successful allocation – store in the slot array
                int slotIndex = (uint)allocIndex + (uint)uStack._2_1_;
                *(int*)(this + 0x0c + slotIndex * 4) = newSlot;
                // Update counter (8-step rolling)
                byte counterByte = *(byte*)(this + 0x6c);
                *(ushort*)(this + 0x6c) = (byte)((counterByte & 0xf8) + 8 ^ counterByte) & 0x78 ^ *(ushort*)(this + 0x6c);
                allocIndex++;
            } while (allocIndex < step);
        }

        // Advance the head index by the allocated count and wrap
        result = this + 0x0c + (uint)uStack._2_1_ * 4;
        *(byte*)(this + 0x6e) = uStack._2_1_ + allocIndex;
        if (*(byte*)(this + 0x6f) <= (byte)(uStack._2_1_ + allocIndex)) {
            *(byte*)(this + 0x6e) = 0;
        }

        // Apply parent flags to the counter
        if ((*(byte*)(parent + 8) & 1) != 0) {
            *(ushort*)(this + 0x6c) = *(ushort*)(this + 0x6c) ^ 4; // toggle bit 2
        }
        if ((*(byte*)(parent + 8) & 0x40) != 0) {
            *(ushort*)(this + 0x6c) = *(ushort*)(this + 0x6c) | 0x100; // set bit 8
            return result;
        }
    } else {
endLabel:
        result = 0;
    }
    return result;
}