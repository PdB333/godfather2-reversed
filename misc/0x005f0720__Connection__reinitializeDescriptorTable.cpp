// FUNC_NAME: Connection::reinitializeDescriptorTable
__thiscall int Connection::reinitializeDescriptorTable(void) {
    int *pSegmentSize;
    uint uNumObjects;
    int iCumulativeOffset;
    int *pPrevCumulative;
    uint i;
    uint j;

    // Initialize packet descriptor header at +0x8
    if (this + 0x8 != 0) {
        *(undefined4 *)(this + 0x8) = 0;                     // +0x8: start offset, zeroed
        *(undefined4 *)(this + 0xc) = 0;                     // +0xc: maybe next pointer
        *(undefined2 *)(this + 0x10) = 0x23;                // +0x10: max descriptors (35)
        *(undefined2 *)(this + 0x12) = 0;                    // +0x12: count
        FUN_005dbc10(this + 0x8, 0x23);                     // Initialize header array of 35 bytes?
    }

    // Initialize descriptor table at +0x18 (0x23 entries, each 0x10 bytes)
    // Each descriptor: +0x00: segmentSize (int, set to -1), +0x08: used (byte, set to 0)
    uNumObjects = *(uint *)(this + 0x250);                  // +0x250: number of object pointers in array
    pSegmentSize = (int *)(this + 0x20);                   // Start at +0x20 (second descriptor field?)
    i = 0x23;                                              // Number of descriptors
    do {
        *(int *)(pSegmentSize - 2) = -1;                   // Write -1 to descriptor's segmentSize (int at offset 0x18,0x28,...)
        *(undefined1 *)pSegmentSize = 0;                   // Write 0 to descriptor's used flag (byte at offset 0x20,0x30,...)
        pSegmentSize = (int *)((char *)pSegmentSize + 0x10); // Advance 16 bytes to next descriptor
        i = i - 1;
    } while (i != 0);

    // Set cumulative offset to 0 (at +0x14)
    iCumulativeOffset = 0;
    i = 0;                                                  // Descriptor index
    if (uNumObjects != 0) {
        j = 0;
        do {
            int *pObject = *(int **)(*(int *)(this + 0x24c) + j * 4); // +0x24c: array of object pointers
            if ((pObject != 0) && (*(int *)(pObject + 0x24 / 4) != 0)) { // pObject->numSegments (at +0x24)
                pPrevCumulative = (int *)(i * 0x10 + 0x18 + this); // Pointer to descriptor base (at +0x18)
                uint uSegments = 0;
                do {
                    int iSegmentSize = *(int *)(pObject + 0x20 / 4) * 0x400; // pObject->segmentSize (at +0x20) * 1024
                    // Store cumulative offset before segment in the dword before the descriptor (at +0x14, but for index i it's at base - 4)
                    pPrevCumulative[-1] = iCumulativeOffset;
                    iCumulativeOffset += iSegmentSize;
                    *pPrevCumulative = iSegmentSize;        // Store segment size in descriptor's segmentSize field
                    *(undefined1 *)(pPrevCumulative + 2) = 0; // Clear used flag (at +0x08 of descriptor)
                    uSegments++;
                    i++;
                    pPrevCumulative += 4;                   // Advance to next descriptor (16 bytes)
                } while (uSegments < *(uint *)(pObject + 0x24 / 4)); // Until all segments processed
            }
            j++;
        } while (j < uNumObjects);
    }

    // Clear object list and metadata
    *(uint *)(this + 0x250) = 0;                           // +0x250: clear object count
    FUN_009c8f10(*(undefined4 *)(this + 0x24c));           // Free object pointer array
    *(int *)(this + 0x24c) = 0;                            // +0x24c: clear array pointer
    *(int *)(this + 0x254) = 0;                            // +0x254: clear some other field

    return 1;
}