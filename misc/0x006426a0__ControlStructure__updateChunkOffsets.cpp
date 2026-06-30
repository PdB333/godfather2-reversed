// FUNC_NAME: ControlStructure::updateChunkOffsets
// Address: 0x006426a0
// Role: Updates packed control block entries in an array, adjusting offsets and flags for nodes in a linked structure.
// The array at (+0x0c from *param_3) contains uint32 entries with bitfields: low 6 bits = type, bits 6-23 = relative offset, bits 24-31 = extra data.
// The function traverses the chain starting at currentIndex, updating offsets based on provided parameters.

void __fastcall updateChunkOffsets(int unused /* param_1, not used */,
                                   int currentIndex,              // param_2: index of current node in the chain
                                   int *controlStruct,            // param_3: pointer to control structure (first element points to an array)
                                   int newStartOffset,            // param_4: new offset for start node
                                   uint startExtra,               // param_5: extra data for start node (if not 0xFF, uses the value directly)
                                   int newEndOffset,              // param_6: new offset for end node
                                   uint endExtra,                 // param_7: extra data for end node (if not 0xFF, uses the value directly)
                                   int newMiddleOffset)           // param_8: new offset for middle nodes (when type != 0x18)
{
    // Bitmap table for character classification of previous node's low 6 bits.
    // Each character's high bit (0x80) indicates whether the previous node is a "start" marker.
    static const char s_typeClassification[] = "$a $ a4A";

    if (currentIndex == -1) {
        return;
    }

    int iVar7;
    uint uVar3, uVar5;
    uint *puVar8, *puVar6;
    int nextIndex;

    do {
        // Base of the uint32 array (offset +0x0c from the content of controlStruct)
        uint *chunkArray = (uint *)(*(int *)(*controlStruct + 0xc));
        puVar8 = &chunkArray[currentIndex];

        // Extract the 18-bit relative offset field (bits 6-23)
        int relOffset = (*puVar8 >> 6) & 0x3ffff;

        // Determine next index: if relOffset == 0x1fffe, chain ends; else nextIndex = currentIndex + (relOffset - 0x1fffe)
        if (relOffset == 0x1fffe) {
            nextIndex = -1;
        } else {
            nextIndex = (relOffset - 0x1fffe) + currentIndex;
        }

        // Determine if we should use the current element or the previous one (based on type classification of previous element)
        if (currentIndex < 1) {
            // At beginning of chain, always use current
            puVar6 = puVar8;
        } else {
            // Peek at previous element's low 6 bits as index into classification table
            uint prevType = puVar8[-1] & 0x3f;
            if ((s_typeClassification[prevType] & 0x80) == 0) {
                puVar6 = puVar8; // Use current
            } else {
                puVar6 = puVar8 - 1; // Use previous
            }
        }

        uVar3 = *puVar6;
        // Check the type (low 6 bits) of the selected node
        if ((uVar3 & 0x3f) == 0x18) {
            // Type 0x18: end-of-chain marker or similar
            if ((uVar3 & 0x7fc0) == 0) {
                // No extra offset bits set — treat as end node
                uVar5 = (endExtra == 0xff) ? ((uVar3 >> 15) & 0x1ff) : endExtra;
                *puVar6 = (uVar3 & 0xffffff) | (uVar5 << 24);
                iVar7 = *(int *)(*controlStruct + 0xc);
                // Use newEndOffset for the offset update
                int offsetDelta = newEndOffset - currentIndex;
                puVar8 = (uint *)(iVar7 + currentIndex * 4);
                if (abs(offsetDelta) > 0x1ffff) {
                    goto errorTooLong;
                }
                *puVar8 = (*puVar8 & 0xffffc0) | ((offsetDelta + 0x1fffe) << 6);
            } else {
                // Has extra offset bits — treat as start node
                uVar5 = (startExtra == 0xff) ? ((uVar3 >> 15) & 0x1ff) : startExtra;
                *puVar6 = (uVar3 & 0xffffff) | (uVar5 << 24);
                iVar7 = *(int *)(*controlStruct + 0xc);
                // Use newStartOffset for the offset update
                int offsetDelta = newStartOffset - currentIndex;
                puVar8 = (uint *)(iVar7 + currentIndex * 4);
                if (abs(offsetDelta) > 0x1ffff) {
                    goto errorTooLong;
                }
                *puVar8 = (*puVar8 & 0xffffc0) | ((offsetDelta + 0x1fffe) << 6);
            }
        } else {
            // Type other than 0x18: intermediate/middle node
            int offsetDelta = newMiddleOffset - currentIndex;
            if (abs(offsetDelta) > 0x1ffff) {
                goto errorTooLong;
            }
            *puVar8 = (*puVar8 & 0xffffc0) | ((offsetDelta + 0x1fffe) << 6);
        }

        currentIndex = nextIndex;
    } while (currentIndex != -1);

    return;

errorTooLong:
    reportError("control structure too long");
    // Break into debugger (software interrupt 3)
    __asm { swi 3 }
    // The break will halt execution; unreachable return for completeness
    return;
}