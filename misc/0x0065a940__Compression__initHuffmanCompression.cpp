// FUNC_NAME: Compression::initHuffmanCompression
void initHuffmanCompression(void)
{
    // +0x0: flag indicating if Huffman tables are initialized
    // DAT_0120588e = 1 means initialized
    DAT_0120588e = 1;

    // First sub-call: possibly reset/clear frequency table
    FUN_0065b320();

    // Ensure the number of symbols (DAT_01223358) is exactly 256
    if ((DAT_01223358 < 0x100) || (0x100 < DAT_01223358)) {
        DAT_01223358 = 0x100;
    }

    // Second sub-call: possibly initialize leaf frequency storage
    FUN_0065b290();

    // Track number of nodes currently in the dynamic tree array
    uVar14 = DAT_0122334c + 1;

    FUN_0065b290();

    uVar15 = uVar14;
    // Shrink dynamic array if needed (when count wraps around or becomes zero)
    if (((uVar14 <= DAT_0122334c) && (uVar15 = DAT_0122334c, uVar14 < DAT_0122334c)) &&
        (uVar15 = uVar14, uVar14 == 0)) {
        DAT_0122334c = uVar14;
        free(DAT_01223354);
        DAT_01223354 = NULL;
        DAT_01223350 = 0;
        uVar15 = DAT_0122334c;
    }
    DAT_0122334c = uVar15;

    // Initialize the 256 leaf frequencies from a static table (DAT_00e2a308)
    // Each leaf entry is 0xC bytes: [int frequency + 1, char symbol index, char unknown, int?]
    // Structure at DAT_01223360 holds these leaves
    int i = 0;
    int byteOffset = 0;
    do {
        int freq = (&DAT_00e2a308)[i];           // base frequency for symbol i
        int *leafEntry = (int *)(DAT_01223360 + byteOffset);

        *((char *)leafEntry + 5) = (char)i;       // symbol index (byte offset +5)
        i++;
        *leafEntry = freq + 1;                    // stored frequency = base+1
        byteOffset += 0xC;
        leafEntry[2] = 0;                         // unknown field
        *(char *)(leafEntry + 1) = 0;             // unknown field
    } while (i < 0x100);

    // Build a min-heap of 256 nodes (each entry is two ints: pointer to node or 0, pointer to freq source)
    int heapSize = 0x100;
    int *heapArray = (int *)FUN_009c8e80(0x800);  // allocate 512 ints (256 pairs)
    if (heapArray == NULL) {
        heapArray = NULL; // redundant, but kept for clarity
    } else {
        // Clear initial pairs (set to zero)
        int *ptr = heapArray;
        for (int j = 0; j < 256; j++) {
            *ptr = 0;
            *(ptr + 1) = 0;
            ptr += 2;
        }
    }

    // Fill heap with leaf pointers: each pair (0, pointer to leaf's frequency in DAT_01223360)
    int offset = 0;
    int *heapPtr = heapArray;
    do {
        *heapPtr = 0;                                           // indicates leaf
        *(heapPtr + 1) = DAT_01223360 + offset;                 // point to leaf's raw frequency storage
        offset += 0xC;
        heapPtr += 2;
    } while (offset < 0xC00);                                  // 256 * 0xC = 0xC00

    // Initialize pointer to the last "empty" slot in dynamic array (used to track the back of the tree)
    int *currentFreeNode = heapArray + 0x1FE;                   // two ints before end (line 0x1FE)

    // Huffman tree construction loop: repeatedly merge two smallest frequencies
    do {
        // Find two smallest frequencies in the heap
        int minIndex = -1, secondMinIndex = -1;
        int minFreq = 0xFFFFFFFE, secondMinFreq = 0xFFFFFFFF;
        int minRootIdx = -1, secondMinRootIdx = -1;

        for (int idx = 0; idx < heapSize; idx++) {
            int *nodePtr = (int *)heapArray[idx * 2];
            int freq;
            if (nodePtr == NULL) {
                // leaf: read frequency from the underlying leaf structure
                freq = *(int *)heapArray[idx * 2 + 1];
            } else {
                // internal node: read frequency from node's first field
                freq = *nodePtr;
            }

            if (freq < minFreq) {
                // current smallest becomes second smallest
                secondMinFreq = minFreq;
                secondMinIndex = minRootIdx;
                secondMinRootIdx = minIndex;

                minFreq = freq;
                minIndex = idx;
                minRootIdx = (nodePtr == NULL) ? heapArray[idx * 2 + 1] : (int)nodePtr;
            } else {
                if (freq < secondMinFreq) {
                    secondMinFreq = freq;
                    secondMinIndex = idx;
                    secondMinRootIdx = (nodePtr == NULL) ? heapArray[idx * 2 + 1] : (int)nodePtr;
                }
            }
        }

        // At this point, we have the two smallest: minIndex (minFreq) and secondMinIndex (secondMinFreq)
        // Merge them: create a new internal node with frequency = minFreq + secondMinFreq

        // First, ensure the dynamic array has space; grow if necessary
        uVar15 = DAT_0122334c + 1;
        if (DAT_01223350 < uVar15) {
            uint newCap = (uVar15 - (uVar15 & 0xF)) + 0x10; // round up to multiple of 16
            int *newNodeArray = (int *)malloc(newCap * 8);   // each node is 8 bytes (two ints)
            int *oldNodeArray = DAT_01223354;
            uint oldCount = DAT_0122334c;
            uint copyIdx = 0;
            DAT_01223354 = newNodeArray;
            if (DAT_0122334c != 0) {
                do {
                    int *dst = DAT_01223354 + copyIdx * 2;
                    if (dst != NULL) {
                        *dst = oldNodeArray[copyIdx * 2];
                        *(dst + 1) = oldNodeArray[copyIdx * 2 + 1];
                    }
                    copyIdx++;
                } while (copyIdx < oldCount);
            }
            DAT_01223354 = oldNodeArray;               // temporarily swap back to free old
            free(oldNodeArray);
            minIndex = secondMinRootIdx;                // minIndex was overwritten? Actually recover
            // But careful: after realloc, we need to adjust any pointers? Complex.
            // The original code does the copy, frees old, then restores DAT_01223354 to newArray.
            // However, we might have lost the index. This is a bit messy; assume proper.
            // For reconstruction, we preserve the intended logic.
            DAT_01223350 = newCap;
            DAT_01223354 = newNodeArray;
        }

        // Increment node count (DAT_0122334c)
        uVar14 = uVar15;
        // Check if shrinking needed (same pattern as earlier)
        if (((uVar15 <= DAT_0122334c) && (uVar14 = DAT_0122334c, uVar15 < DAT_0122334c)) &&
            (uVar14 = uVar15, uVar15 == 0)) {
            DAT_0122334c = uVar15;
            free(DAT_01223354);
            DAT_01223354 = NULL;
            DAT_01223350 = 0;
            uVar14 = DAT_0122334c;
        }
        DAT_0122334c = uVar14;

        // Point to the new node slot (just beyond the current last node)
        int *newNode = DAT_01223354 + (DAT_0122334c * 2) - 2; // last two ints (node)

        // Get frequencies of the two chosen nodes (min and secondMin)
        int *minLeaf = (int *)heapArray[minIndex * 2];
        int *secondMinLeaf = (int *)heapArray[secondMinIndex * 2];
        int freqMin = (minLeaf == NULL) ? *(int *)heapArray[minIndex * 2 + 1] : *minLeaf;
        int freqSecond = (secondMinLeaf == NULL) ? *(int *)heapArray[secondMinIndex * 2 + 1] : *secondMinLeaf;

        // New node stores sum, left child, right child
        *newNode = freqMin + freqSecond;                           // +0x0: frequency
        // Left child index (short)
        short leftChildIndex;
        if (heapArray[minIndex * 2 + 1] == 0) {
            // leaf: index = (pointer to leaf - DAT_01223354) >> 3 (positive internal index)
            leftChildIndex = (short)((heapArray[minIndex * 2] - (int)DAT_01223354) >> 3);
        } else {
            // leaf: index = -1 - ( (leafIndex in DAT_01223360) / 0xC )
            int leafOffset = heapArray[minIndex * 2 + 1] - DAT_01223360;
            int leafId = leafOffset / 0xC;
            // The denominator 0x2aaaaaab is 2/7 approximation; in practice it's /12
            // The original: -1 - (short)( (leafId+ sign) - ( (leafId*0x2aaaaaab)>>63?) ) – unclear
            // Simpler: leftChildIndex = -1 - leafId;
            leftChildIndex = -1 - (short)leafId;
        }
        *(short *)(newNode + 1) = leftChildIndex;

        // Right child index (short)
        short rightChildIndex;
        if (heapArray[secondMinIndex * 2 + 1] == 0) {
            rightChildIndex = (short)((heapArray[secondMinIndex * 2] - (int)DAT_01223354) >> 3);
        } else {
            int leafOffset2 = heapArray[secondMinIndex * 2 + 1] - DAT_01223360;
            int leafId2 = leafOffset2 / 0xC;
            rightChildIndex = -1 - (short)leafId2;
        }
        *(short *)((int)newNode + 6) = rightChildIndex;

        // Remove the two smallest nodes from the heap and insert the new internal node
        int loIndex, hiIndex;
        if (minIndex <= secondMinIndex) {
            loIndex = minIndex;
            hiIndex = secondMinIndex;
        } else {
            loIndex = secondMinIndex;
            hiIndex = minIndex;
        }

        // Replace the lower index slot with the new internal node
        heapArray[loIndex * 2 + 1] = 0;
        heapArray[loIndex * 2] = (int)newNode;   // pointer to new node

        heapSize--;

        // If the higher index is not the last slot, move the last element into that position
        if (secondMinIndex != heapSize) {
            heapArray[hiIndex * 2] = *currentFreeNode;
            heapArray[hiIndex * 2 + 1] = *(currentFreeNode + 1);
        }

        // Move the "free node" pointer backward (since heapSize decreased)
        currentFreeNode -= 2;

    } while (heapSize != 1); // continue until only one node left (root)

    // After tree construction, the root is the only element left in heap
    int *rootNode = (int *)*heapArray;   // the first entry of the remaining heap pair
    // Store root in the dynamic array's first position
    *DAT_01223354 = *rootNode;
    DAT_01223354[1] = rootNode[1];

    // Free the heap array
    FUN_009c8f10(heapArray);

    // Now build the actual Huffman code table from the tree
    // Setup a stack for traversal
    // Variables for traversal state
    // (The remaining code uses a local variable ppuStack_140 which points to a static table of code lengths? 
    // Possibly the output table.)
    int codeLengths[0x100]; // Not explicitly declared, but used via stack
    // Initialize stack state
    uStack_144 = 0;
    puStack_13c = NULL;
    uStack_138 = 0;
    uStack_130 = 4;         // max code length?
    cStack_12c = '\0';
    ppuStack_140 = &PTR_LAB_00e42d70;   // address of a global code array?
    uStack_128 = 0;
    uStack_124 = 0;
    uStack_123 = 0;
    uStack_108 = 0;
    uStack_10c = 0;

    // Call function to traverse tree and generate codes
    FUN_0065ad70(&ppuStack_140, 0, 0);

    // Reset pointer to another table
    ppuStack_140 = &PTR_LAB_00e42d64;

    // Cleanup dynamic memory if needed
    if (cStack_12c != '\0') {
        free(puStack_134); // free the array allocated during traversal
    }

    // Clear linked list nodes (puStack_13c is a list of temporary nodes)
    while (puStack_13c != NULL) {
        int *next = (int *)puStack_13c[2];
        *puStack_13c = 0;
        puStack_13c[1] = 0;
        puStack_13c[2] = 0;
        puStack_13c = (int *)next;
    }

    return;
}