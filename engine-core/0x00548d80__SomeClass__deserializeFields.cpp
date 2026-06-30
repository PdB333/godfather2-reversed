// FUNC_NAME: SomeClass::deserializeFields
void SomeClass::deserializeFields(void)
{
    // in_EAX is passed to FUN_0043aff0 (likely a hash/type check)
    FUN_0043aff0(in_EAX, 0x50f03f03);

    uint index = local_58; // current index in iteration
    while (true) {
        bool done;
        if (local_64 == '\0') {
            // linear list: check if next pointer is null
            done = (*local_8 == (undefined4 *)0x0);
        } else {
            // bitmask-based: check if index reached count
            done = (index == local_54);
        }
        if (done) break;

        // Determine which node pointer to use
        undefined4 **nodePtr;
        if (local_64 == '\0') {
            nodePtr = local_8; // linked list node
        } else {
            nodePtr = &local_50; // current array element
        }

        // Extract field type from node
        undefined4 *fieldType;
        if (*(short *)((int)nodePtr + 6) == 0x25e3) {
            // Special case: type stored as ushort at offset 6
            fieldType = (undefined4 *)(uint)*(ushort *)(nodePtr + 1);
        } else {
            // Normal case: type stored as pointer at offset 4
            fieldType = nodePtr[1];
        }

        // Write the field value (nodePtr[2]) to the appropriate member
        switch ((int)fieldType) {
        case 0: // +0x2c
            *(undefined4 **)(unaff_EDI + 0x2c) = nodePtr[2];
            break;
        case 1: // +0x08
            *(undefined4 **)(unaff_EDI + 8) = nodePtr[2];
            break;
        case 2: // +0x0c
            *(undefined4 **)(unaff_EDI + 0xc) = nodePtr[2];
            break;
        case 3: // +0x10
            *(undefined4 **)(unaff_EDI + 0x10) = nodePtr[2];
            break;
        case 4: // +0x14
            *(undefined4 **)(unaff_EDI + 0x14) = nodePtr[2];
            break;
        case 5: // +0x18
            *(undefined4 **)(unaff_EDI + 0x18) = nodePtr[2];
            break;
        case 6: // +0x1c
            *(undefined4 **)(unaff_EDI + 0x1c) = nodePtr[2];
            break;
        case 7: // +0x20
            *(undefined4 **)(unaff_EDI + 0x20) = nodePtr[2];
            break;
        case 8: // +0x24
            *(undefined4 **)(unaff_EDI + 0x24) = nodePtr[2];
            break;
        case 9: // +0x28
            *(undefined4 **)(unaff_EDI + 0x28) = nodePtr[2];
            break;
        }

        // Advance to next node/element
        if (local_64 == '\0') {
            // Linked list: follow next pointer (offset 0 is next)
            if ((int)index < 0) {
                local_8 = (undefined4 **)((int)local_8 + (int)*local_8);
                FUN_0043b140(); // likely some iterator helper
                index = local_58;
            } else if ((int)index < (int)(local_54 - 1)) {
                local_8 = (undefined4 **)((int)local_8 + (int)*local_8);
                local_58 = index + 1;
                index = local_58;
            } else {
                local_8 = (undefined4 **)&DAT_01163cf8; // sentinel
                local_8 = (undefined4 **)&DAT_01163cf8;
            }
        } else {
            // Bitmask array: move to next index
            local_58 = index + 1;
            index = local_58;
            if (local_58 != local_54) {
                local_4c = (short)local_58; // store as short
                // Check bitmask: if bit is clear, read next element from data pointer
                if ((*(byte *)((local_58 >> 3) + local_60) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    local_50 = local_5c; // current element = data pointer
                    local_48 = *local_5c; // store first word (maybe size?)
                    local_5c = local_5c + 1; // advance data pointer
                } else {
                    // Bit set: skip this index (field not present)
                    local_50 = (undefined4 *)0x0;
                    local_48 = 0;
                }
            }
        }
    }
    return;
}