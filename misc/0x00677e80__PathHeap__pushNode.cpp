// FUNC_NAME: PathHeap::pushNode
void __thiscall PathHeap::pushNode(void) {
    short *psVar1;
    short sVar2;
    short sVar3;
    short sVar5;
    int iVar4;
    int iVar6;

    // +0x38: m_capacity (short), +0x36: m_size (short), +0x40: m_keys (short*)
    // +0x3c: m_prefixSum (short*), +0x44: m_x (short*), +0x48: m_y (short*), +0x4c: m_z (char*)
    short capacity = *(short *)(this + 0x38);
    short size = *(short *)(this + 0x36);
    short *keys = *(short **)(this + 0x40);
    short *prefixSum = *(short **)(this + 0x3c);
    short *xArr = *(short **)(this + 0x44);
    short *yArr = *(short **)(this + 0x48);
    char *zArr = *(char **)(this + 0x4c);

    // Condition: if capacity != 0 and (size < 1 or last key != capacity-1)
    if (capacity != 0 && (size < 1 || (int)keys[size - 1] != capacity - 1)) {
        // Call helper (likely reallocate or reset)
        FUN_00677de0();

        // Set new key at position size
        if (capacity < 1) {
            *(short *)(keys + size) = 0;
        } else {
            *(short *)(keys + size) = capacity - 1;
        }

        // Increment size
        size = size + 1;
        *(short *)(this + 0x36) = size;

        // Recompute prefix sums: prefixSum[i] = sum_{j=0}^{i-1} (keys[j] + 1)
        sVar3 = 0;
        sVar5 = 0;
        if (0 < size) {
            do {
                *(short *)(prefixSum + sVar5) = sVar3;
                sVar3 = keys[sVar5] + 1;
                sVar5 = sVar5 + 1;
            } while (sVar5 < size);
        }

        // Check for duplicate node at the last position
        sVar3 = capacity;
        if (0 < sVar3) {
            iVar4 = size * 2; // byte offset for last element
            sVar5 = *(short *)((char *)prefixSum + iVar4 - 2); // prefixSum[size-1]
            psVar1 = (short *)((char *)keys + iVar4 - 2); // &keys[size-1]
            sVar2 = *psVar1; // keys[size-1]
            if (sVar5 < sVar2) {
                iVar6 = (int)sVar5;
                iVar4 = (int)sVar2;
                // Compare coordinates at indices sVar5 and sVar2
                if (xArr[iVar6] == xArr[iVar4] &&
                    yArr[iVar6] == yArr[iVar4] &&
                    zArr[iVar6] == zArr[iVar4]) {
                    // Duplicate found: reduce capacity and adjust last key
                    *(short *)(this + 0x38) = sVar3 - 1; // capacity--
                    *psVar1 = sVar3 - 2; // keys[size-1] = capacity-2
                }
            }
        }
    }
    return;
}