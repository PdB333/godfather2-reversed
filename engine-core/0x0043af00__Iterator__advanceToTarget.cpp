// FUNC_NAME: Iterator::advanceToTarget
void __thiscall Iterator::advanceToTarget(int target) {
    // this+0x00: type flag (0 = linked list, non-zero = bitvector)
    // this+0x04: for bitvector: pointer to bit array (bytes)
    // this+0x08: for bitvector: pointer to data array (uint32)
    // this+0x0c: current index (int)
    // this+0x10: max index count (int)
    // this+0x14-0x17: temporary storage for value when not occupied (uint32)
    // this+0x18: current index stored as short (for visibility?)
    // this+0x1c-0x1f: more value storage (uint32)
    // this+0x5c: linked list iterator: pointer to pointer to node (node: +0x00 next pointer, +0x04 ID)

    if (*this == '\0') {
        // Linked list mode
        int currentNode = **(int**)(this + 0x5c);
        while (currentNode != 0 && (*(int*)(*(int*)(this + 0x5c) + 4) != target)) {
            if (*(int*)(this + 0x0c) < 0) {
                *(int*)(this + 0x5c) = **(int**)(this + 0x5c) + (int)*(int**)(this + 0x5c);
                SomeFunction(); // FUN_0043b140
            } else if (*(int*)(this + 0x0c) < *(int*)(this + 0x10) - 1) {
                *(int*)(this + 0x5c) = **(int**)(this + 0x5c) + (int)*(int**)(this + 0x5c);
                *(int*)(this + 0x0c) = *(int*)(this + 0x0c) + 1;
            } else {
                *(int**)(this + 0x5c) = &DAT_01163cf8; // sentinel
            }
            currentNode = **(int**)(this + 0x5c);
        }
    } else if (*(int*)(this + 0x0c) < *(int*)(this + 0x10)) {
        // Bitvector mode
        while (*(int*)(this + 0x0c) != target) {
            uint index = *(int*)(this + 0x0c) + 1;
            *(uint*)(this + 0x0c) = index;
            if (index != *(uint*)(this + 0x10)) {
                *(short*)(this + 0x18) = (short)index;
                if ((*(byte*)((index >> 3) + *(int*)(this + 4)) & (byte)(1 << ((byte)index & 7))) == 0) {
                    // Slot not occupied, read data
                    uint32 val = **(uint32**)(this + 8);
                    *(uint32**)(this + 0x14) = *(uint32**)(this + 8);
                    *(uint32*)(this + 0x1c) = val;
                    *(int*)(this + 8) = *(int*)(this + 8) + 4;
                } else {
                    // Slot occupied, clear temporary storage
                    *(int*)(this + 0x14) = 0;
                    *(int*)(this + 0x18) = 0; // overwritten by short above, but order kept
                    *(int*)(this + 0x1c) = 0;
                    *(int*)(this + 0x20) = 0; // unsafe, but decompiled shows zeroing 4 bytes starting at 0x1c? Actually only 0x1c-0x1f
                }
            }
            if (*(int*)(this + 0x10) <= *(int*)(this + 0x0c)) {
                return;
            }
        }
    }
    return;
}