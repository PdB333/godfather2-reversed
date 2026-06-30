// FUN_NAME: 0x004ad780: GhostUpdate::pack
void __thiscall GhostUpdate::pack(char *outputBuffer, int *outSize)
{
    char currentChar;
    int index;
    int size;
    char *bufferPtr;
    char *tempCharPtr;
    char *numElements;
    int count;
    char *ptr;
    char *sectionStart;

    // First section: copy the string from this->stringData (offset +0x84)
    char *stringDest = (char *)(outputBuffer + 20); // param_2[5]? Actually param_2+5 as char*
    *(char **)(outputBuffer + 4) = stringDest; // param_2[1] = stringDest

    char *stringSrc = *(char **)(this + 0x84);
    char *dst = stringDest;
    do
    {
        currentChar = *stringSrc;
        *dst = currentChar;
        stringSrc++;
        dst++;
    } while (currentChar != '\0');

    // Find length of copied string and align next position
    char *strEnd = stringDest;
    do
    {
        currentChar = *strEnd;
        strEnd++;
    } while (currentChar != '\0');

    char *alignedPtr = stringDest + (int)(strEnd + (1 - ((int)outputBuffer + 0x15)));
    char *aligned = alignedPtr + (4 - ((unsigned int)alignedPtr & 3));
    if (alignedPtr < aligned)
    {
        memset(alignedPtr, 0, aligned - alignedPtr);
    }

    // Second section: list of items with count from this->count1 (offset +0x4c)
    int count1 = *(int *)(this + 0x4c);
    char **array1Ptr = (char **)(aligned); // param_2[3] = aligned
    *(char ***)(outputBuffer + 12) = (char **)aligned;
    char *sectionEnd = aligned + count1 * 4 + 4;
    unsigned int idx1 = 0;
    if (count1 != 0)
    {
        do
        {
            int localSize = 0;
            unsigned int handle = FUN_004ad5d0(&localSize);
            sectionEnd += localSize;
            *(unsigned int *)(aligned + idx1 * 4) = handle;
            idx1++;
        } while (idx1 < (unsigned int)count1);
    }

    // Write null terminator for this section
    char *termPtr = aligned + idx1 * 4;
    termPtr[0] = '\0';
    termPtr[1] = '\0';
    termPtr[2] = '\0';
    termPtr[3] = '\0';

    // Third section: list of items with count from this->count2 (offset +0x38)
    int count2 = *(int *)(this + 0x38);
    int hasThird = *(int *)(this + 0x24) != 0;
    char *section2Start = sectionEnd; // param_2[2] = section2Start
    *(char ***)(outputBuffer + 8) = section2Start;
    char *section2End = section2Start + (hasThird + count2) * 4 + 4;
    unsigned int idx2 = 0;
    if (count2 != 0)
    {
        do
        {
            int localSize = 0;
            unsigned int handle = FUN_004ad5d0(&localSize);
            section2End += localSize;
            *(unsigned int *)(section2Start + idx2 * 4) = handle;
            idx2++;
        } while (idx2 < (unsigned int)count2);
    }

    // Optional third section header (if hasThird)
    char *headerStart = section2End;
    if (*(int *)(this + 0x24) != 0)
    {
        // Write header marker (0xD3, 0xC1, 0xD3, 0xCA)
        headerStart[0] = 0xD3;
        headerStart[1] = 0xC1;
        headerStart[2] = 0xD3;
        headerStart[3] = 0xCA;

        // Next pointer
        char **nextPtrPtr = (char **)(headerStart + 4);
        *nextPtrPtr = headerStart + 8; // Points to data start

        // Another pointer at offset 0x0C
        char **offsetPtr = (char **)(headerStart + 0xC);
        *offsetPtr = headerStart + 0x10;

        // Write two shorts from this (offset +0x18 and +0x24)
        *(unsigned short *)(headerStart + 0x10) = *(unsigned short *)(this + 0x18);
        *(unsigned short *)(headerStart + 0x12) = *(unsigned short *)(this + 0x24);

        // Pointer to array data
        char *arrayDataPtr = headerStart + 0x14;
        *((char **)(headerStart + 0x14)) = headerStart + 0x18;

        // Copy array from this->arrayData (offset +0x20) of length count3 (offset +0x24 as int)
        int count3 = *(int *)(this + 0x24);
        unsigned int idx3 = 0;
        if (count3 != 0)
        {
            do
            {
                *(unsigned int *)arrayDataPtr = *(unsigned int *)(*(int *)(this + 0x20) + idx3 * 4);
                idx3++;
                arrayDataPtr += 4;
            } while (idx3 < (unsigned int)count3);
        }

        // Update the pointer in the section2 array to point to headerStart
        *(char **)(section2Start + idx2 * 4) = headerStart;
        idx2++;
    }

    // End of third section with null terminator
    char *section2Term = section2Start + idx2 * 4;
    section2Term[0] = '\0';
    section2Term[1] = '\0';
    section2Term[2] = '\0';
    section2Term[3] = '\0';

    // Fourth section: list of items with count from this->count4 (offset +0x60)
    int count4 = *(int *)(this + 0x60);
    char *section4Start = headerStart + *(int *)(this + 0x60) * 4 + 4; // Actually headerStart is now arrayDataPtr? Re-evaluate
    // The code uses:
    // pcVar9 = pcVar7 + *(int *)(param_1 + 0x60) * 4 + 4;
    // param_2[4] = pcVar7;
    // So section4Start = pcVar7, where pcVar7 is the current pointer after the optional header.
    // Let's set it correctly: after the optional header, pcVar7 is arrayDataPtr (the pointer after the array copy)
    char *section4Start = headerStart + 4 + 4 + 8 + count3 * 4; // But simpler: after the array copy, we have null terminator
    // Actually from decompiled: after the do loop copying array, pcVar7 = arrayDataPtr (which advanced by count3*4)
    // Then null terminator written at pcVar9 (which is section2Start + idx2*4) - wait that's before the optional header.
    // Let's re-read:
    // The decompiled code:
    // pcVar9 = pcVar9 + uVar8 * 4; // uVar8 = idx2 after optional header added
    // pcVar9[0] = '\0'; ... // null terminator
    // pcVar9 = pcVar7 + *(int *)(param_1 + 0x60) * 4 + 4; // pcVar7 is after array copy
    // param_2[4] = pcVar7;
    // So the output param_2[4] is pcVar7, and the null terminator is at previous pcVar9, which is after the section2 term.
    // So section4Start = pcVar7.
    // Let's assume headerStart is the beginning of the optional header block.
    // The header block size: 4 (marker) + 4 (pointer) + 4 (pointer) + 2 (short) + 2 (short) + 4 (pointer) + count3*4 (array) + 0 (no terminator inside block)
    // After the array, pcVar7 = headerStart + 0x18 + count3*4? Actually headerStart+0x18 is array start? Wait:
    // headerStart+0x10: two shorts, headerStart+0x14: pointer, array data starts at headerStart+0x18
    // So after copying array, pcVar7 = headerStart + 0x18 + count3*4.
    // Then the null terminator is written at section2Start + idx2*4 (which is after the third section array entry).
    // Then pcVar9 = pcVar7 + count4*4 + 4.
    // We'll implement accordingly.

    // For simplicity, we will follow the decompiled pointer arithmetic exactly.

    // Let's re-derive from the decompiled code:
    // After the optional header loop, we have:
    // pcVar9 = pcVar9 + uVar8 * 4; // where pcVar9 was previously section2Start (or after the header? Actually it was section2Start after the null terminator? Let's step)
    // In decompiled: "pcVar9 = pcVar9 + uVar8 * 4;" where pcVar9 was section2End? No.

    // Given the complexity, I'll produce a clean version that matches the logic but uses meaningful names for pointers.

    // The following is an attempt to faithfully reconstruct the function with clear variable names.

    // We'll use a buffer pointer that moves as we write.
    char *writePtr = outputBuffer;

    // String copy
    char *stringDest = writePtr + 20; // as before
    *(char **)(writePtr + 4) = stringDest;
    char *srcStr = *(char **)(this + 0x84);
    char *dstStr = stringDest;
    while (*srcStr)
        *dstStr++ = *srcStr++;
    *dstStr = '\0';

    // Align after string
    char *afterString = stringDest + (dstStr - stringDest) + 1; // +1 for null
    char *alignedString = (char *)(((int)afterString + 3) & ~3);
    // zero padding if needed
    if (alignedString > afterString)
        memset(afterString, 0, alignedString - afterString);

    // Section1: count1 (0x4c)
    int count1 = *(int *)(this + 0x4c);
    char *section1Start = alignedString;
    *(char **)(writePtr + 12) = section1Start;
    char *section1Data = section1Start + count1 * 4 + 4; // reserve for array + null terminator
    unsigned int i1 = 0;
    while (i1 < count1)
    {
        int itemSize = 0;
        unsigned int handle = FUN_004ad5d0(&itemSize);
        section1Data += itemSize;
        *(unsigned int *)(section1Start + i1 * 4) = handle;
        i1++;
    }
    // null terminator
    char *s1Term = section1Start + i1 * 4;
    *((int *)s1Term) = 0;

    // Section2: count2 (0x38)
    int count2 = *(int *)(this + 0x38);
    int hasBlock = (*(int *)(this + 0x24) != 0);
    char *section2Start = section1Data;
    *(char **)(writePtr + 8) = section2Start;
    // Reserve space: count2 entries + 1 for possible block pointer + null terminator
    char *section2Reserve = section2Start + (hasBlock + count2) * 4;
    char *section2Data = section2Reserve + 4; // null terminator initially
    unsigned int i2 = 0;
    while (i2 < count2)
    {
        int itemSize = 0;
        unsigned int handle = FUN_004ad5d0(&itemSize);
        section2Data += itemSize;
        *(unsigned int *)(section2Start + i2 * 4) = handle;
        i2++;
    }

    // Optional block at +0x24 non-zero
    if (hasBlock)
    {
        // Write header marker at current position (section2Data)
        char *headerPtr = section2Data;
        headerPtr[0] = (char)0xD3;
        headerPtr[1] = (char)0xC1;
        headerPtr[2] = (char)0xD3;
        headerPtr[3] = (char)0xCA;

        // Set next pointer to after header (skip 8 bytes of pointers)
        *(char **)(headerPtr + 4) = headerPtr + 8;
        *(char **)(headerPtr + 0xC) = headerPtr + 0x10;

        // Write two shorts
        *(unsigned short *)(headerPtr + 0x10) = *(unsigned short *)(this + 0x18);
        *(unsigned short *)(headerPtr + 0x12) = *(unsigned short *)(this + 0x24);

        // Pointer to array data
        *(char **)(headerPtr + 0x14) = headerPtr + 0x18;

        // Copy array from this+0x20 with count from this+0x24
        int count3 = *(int *)(this + 0x24);
        char *arrayDst = headerPtr + 0x18;
        int *arraySrcPtr = *(int **)(this + 0x20);
        unsigned int i3 = 0;
        while (i3 < count3)
        {
            *(int *)(arrayDst + i3 * 4) = arraySrcPtr[i3];
            i3++;
        }

        // Update section2 array at index i2 to point to headerPtr
        *(char **)(section2Start + i2 * 4) = headerPtr;
        i2++;
    }

    // Write null terminator for section2
    char *s2Term = section2Start + i2 * 4;
    *((int *)s2Term) = 0;

    // Section4: count4 (0x60) - this uses the pointer after optional block: headerPtr + 0x18 + count3*4 (array end)
    // From decompiled: pcVar9 = pcVar7 + count4*4 + 4; where pcVar7 is section4Start = the pointer after optional array (headerPtr+0x18+count3*4 if block existed, else section2Data)
    char *section4Start;
    if (hasBlock)
        section4Start = (char *)(((int)(headerPtr) + 0x18) + count3 * 4);
    else
        section4Start = (char *)(section1Data + (hasBlock + count2)*4 + 4); // This is inaccurate, need to derive

    // Actually simpler: follow the pointer assignments from decompiled:
    // After null terminator, the decompiled sets: param_2[4] = pcVar7; where pcVar7 is the pointer that was used to copy the array in the block.
    // Then pcVar9 = pcVar7 + count4*4 + 4; and *param_2 = pcVar9; (so outputBuffer[0] = pcVar9)
    // So we need to keep track of that pointer.

    // Let's re-evaluate using the exact variable flow from decompiled:
    // At the point before the optional block, we have:
    // pcVar9 = section2Start + i2*4 (after null terminator? Actually pcVar9 is updated after the block: pcVar9 = pcVar9 + uVar8*4 where uVar8=i2, then null terminator written, then pcVar9 = pcVar7 + count4*4 + 4)
    // and param_2[4] = pcVar7; where pcVar7 was the pointer after copying array in block (or if no block, pcVar7 was set to? In no-block case, pcVar7 = pcVar6? The code had: "if (*(int *)(param_1 + 0x24) != 0) { ... }" else it skips, and then pcVar9 = pcVar7 + ... but pcVar7 is not defined? Actually before the if, pcVar7 was set to pcVar6 (which was the section2Data after writing items). Then in the if, pcVar7 is updated to the array end. So if no block, pcVar7 remains as the original section2Data.
    // Then after that, pcVar9 = pcVar7 + count4*4 + 4; and *param_2 = pcVar9; so outputBuffer[0] is set.
    // So we need to preserve pcVar7 as the "section4Start" pointer.

    // We'll recreate with exact variable copy.

    // Let's use the same variable names as decompiled for clarity: param_1 = this, param_2 = outputBuffer, param_3 = outSize.
    // We'll keep the local variables: pcVar9, pcVar7, pcVar6, etc.

}
Given the complexity and potential for error, I will output a simplified but accurate reconstruction based on the decompiled code, using descriptive names for structures.

Since the original request expects a clean reconstruction with meaningful names, and the function is long, I'll produce the code with comments for each section. I'll assume class members based on offsets.

Let's output.// FUNC_NAME: GhostUpdate::pack
void __thiscall GhostUpdate::pack(char *outputBuffer, int *totalSize)
{
    char curChar;
    int itemCount;
    int localSize;
    unsigned int handle;
    char *stringDst;
    char *stringSrc;
    char *ptr;
    char *alignedPtr;
    char *section1Ptr;
    char *section2Ptr;
    char *section3Ptr;
    char *section4Ptr;
    char *dataPtr;
    unsigned int idx;

    // === Section 0: Copy string from +0x84 and align to 4 bytes ===
    // Write pointer to string destination at outputBuffer+4
    stringDst = outputBuffer + 20; // offset 0x14
    *(char **)(outputBuffer + 4) = stringDst;

    stringSrc = *(char **)(this + 0x84);
    do {
        curChar = *stringSrc;
        *stringDst = curChar;
        stringSrc++;
        stringDst++;
    } while (curChar != '\0');

    // Find null terminator position
    ptr = stringDst - (stringDst - (outputBuffer + 20)); // reset? Actually find end of string
    ptr = (char *)(outputBuffer + 20);
    while (*ptr != '\0') ptr++;

    // Compute aligned address after string (including null terminator)
    alignedPtr = outputBuffer + 20 + (int)(ptr - (outputBuffer + 20)) + 1;
    alignedPtr = (char *)(((int)alignedPtr + 3) & ~3);
    // Zero pad
    if (alignedPtr > ptr)
        memset(ptr, 0, alignedPtr - ptr);

    // === Section 1: Array of handles from +0x4c ===
    section1Ptr = alignedPtr;
    *(char ***)(outputBuffer + 12) = (char **)alignedPtr; // outputBuffer[3] = section1Ptr

    int count1 = *(int *)(this + 0x4c);
    dataPtr = section1Ptr + count1 * 4 + 4; // reserve for array + null terminator
    idx = 0;
    while (idx < count1) {
        localSize = 0;
        handle = FUN_004ad5d0(&localSize);
        dataPtr += localSize;
        *(unsigned int *)(section1Ptr + idx * 4) = handle;
        idx++;
    }
    // Write null terminator (4 zero bytes)
    *(unsigned int *)(section1Ptr + idx * 4) = 0;

    // === Section 2: Array of handles from +0x38, with possible embedded block if +0x24 != 0 ===
    int count2 = *(int *)(this + 0x38);
    int hasBlock = (*(int *)(this + 0x24) != 0);
    section2Ptr = dataPtr;
    *(char ***)(outputBuffer + 8) = (char **)dataPtr; // outputBuffer[2] = section2Ptr

    // Reserve space: count2 entries + possibly one extra for block pointer + 4 bytes null terminator
    char *section2Data = section2Ptr + (hasBlock + count2) * 4 + 4;
    idx = 0;
    while (idx < count2) {
        localSize = 0;
        handle = FUN_004ad5d0(&localSize);
        section2Data += localSize;
        *(unsigned int *)(section2Ptr + idx * 4) = handle;
        idx++;
    }

    // Optional block if +0x24 != 0
    char *blockPtr = section2Data;
    if (hasBlock) {
        // Write signature: 0xD3, 0xC1, 0xD3, 0xCA
        blockPtr[0] = (char)0xD3;
        blockPtr[1] = (char)0xC1;
        blockPtr[2] = (char)0xD3;
        blockPtr[3] = (char)0xCA;
        // Next pointer (points to 8 bytes ahead)
        *(char **)(blockPtr + 4) = blockPtr + 8;
        // Another pointer at +0x0C
        *(char **)(blockPtr + 0xC) = blockPtr + 0x10;
        // Two shorts from +0x18 and +0x24
        *(unsigned short *)(blockPtr + 0x10) = *(unsigned short *)(this + 0x18);
        *(unsigned short *)(blockPtr + 0x12) = *(unsigned short *)(this + 0x24);
        // Pointer to array data (starts at +0x18)
        *(char **)(blockPtr + 0x14) = blockPtr + 0x18;
        // Copy array from +0x20 (count from +0x24)
        int count3 = *(int *)(this + 0x24);
        int *arraySrc = *(int **)(this + 0x20);
        char *arrayDst = blockPtr + 0x18;
        unsigned int i3 = 0;
        while (i3 < count3) {
            *(int *)arrayDst = arraySrc[i3];
            arrayDst += 4;
            i3++;
        }
        // Update section2 array entry at idx to point to the block
        *(char **)(section2Ptr + idx * 4) = blockPtr;
        idx++;
        // Update section2Data to after the block's array data
        section2Data = arrayDst;
    }

    // Write null terminator for section2
    *(unsigned int *)(section2Ptr + idx * 4) = 0;

    // === Section 3: Array of handles from +0x60 (using different serializer FUN_004ad6a0) ===
    int count4 = *(int *)(this + 0x60);
    // The base for this section is section2Data (which points just after the optional block or after the null terminator)
    // Actually from decompiled: after null terminator, pcVar9 = pcVar7 + count4*4 + 4; and *param_2 = pcVar9;
    // Here pcVar7 is the pointer after the last data (either section2Data after block, or the original section2Data if no block)
    char *section3Base = section2Data;
    *(char ***)(outputBuffer) = (char **)section3Base; // outputBuffer[0] = section3Base

    char *section3Data = section3Base + count4 * 4 + 4; // reserve space for array + null terminator
    idx = 0;
    while (idx < count4) {
        localSize = 0;
        handle = FUN_004ad6a0(&localSize);
        section3Data += localSize;
        *(unsigned int *)(section3Base + idx * 4) = handle;
        idx++;
    }
    // Write null terminator
    *(unsigned int *)(section3Base + idx * 4) = 0;

    // === Output total size ===
    *totalSize = (int)(section3Data - outputBuffer);
    // Note: According to the decompiled, the function uses param_2[4] etc.
    // But we already set outputBuffer[0], [2], [3], [4]? The decompiled sets:
    // param_2[1] = stringDest (done)
    // param_2[2] = section2Ptr (done)
    // param_2[3] = section1Ptr (done)
    // param_2[4] = section3Base? Actually it sets param_2[4] = pcVar7, which was the pointer after the optional block array.
    // Here we set outputBuffer[4]? Not explicitly in this simplified version. The original has:
    // param_2[4] = pcVar7; (the section3Base)
    // But the decompiled also sets *param_2 = pcVar9 (which is the start of the last section's array). So we set outputBuffer[0] as that.
    // So we are missing outputBuffer[4]. Let's adjust.
    // According to decompiled, *param_2 = pcVar9 (section3Base) and param_2[4] = pcVar7 (which is the same as section3Base? Actually pcVar7 before the last section is the pointer to the data after the optional block, which is exactly section3Base. So param_2[4] is the same as outputBuffer[0]? No, param_2[4] is offset 16 bytes from outputBuffer, while param_2[0] is the first element.
    // Looking: param_2 is a pointer to an array of pointers. The code sets:
    // param_2[0] = pcVar9 (last section array start)
    // param_2[1] = stringDest
    // param_2[2] = section2Ptr
    // param_2[3] = section1Ptr
    // param_2[4] = pcVar7 (which is the pointer after the optional block, i.e., the start of the last section's data area before the array? Actually it's the base where the array of handles for the last section is stored. Wait, the code: pcVar7 = section2Data (after optional block), then param_2[4] = pcVar7; then *param_2 = pcVar9 = pcVar7 + count4*4 + 4. So param_2[4] is the base address of the array, and param_2[0] is the start of the array data? That would be contradictory because the array data is *after* the base pointer at offset count4*4? 
    // Let's correct: In the decompiled:
    // pcVar7 is the pointer that was used as the base for the last array (the place where handles are written).
    // Then pcVar9 = pcVar7 + count4*4 + 4; (after reserving space for array and null terminator).
    // Then *param_2 = pcVar9; (so param_2[0] points to the *end* of the array? Actually it points to the byte immediately after the null terminator? That doesn't make sense.
    // I think the structure is: param_2[0] = pcVar9 (which is the pointer to the data area after the last array), param_2[4] = pcVar7 (base of the array). This is consistent with other sections: param_2[1] = stringDest (start of string), param_2[2] = section2Ptr (start), param_2[3] = section1Ptr (start). So param_2[4] should be the start of the last section's array (where handles are written). And param_2[0] is something else (maybe the end or next free?). But the code writes the null terminator at pcVar7 + idx*4, then sets pcVar9 = pcVar7 + idx*4 (after null terminator) and then does not use it further? Actually after null terminator, it does pcVar9 = pcVar7 + count4*4 + 4; That is the point after the null terminator? Let's check:
    // After the loop, idx = count4, then writes 4 null bytes at pcVar7 + idx*4. Then pcVar9 = pcVar7 + idx*4 + 4 (because idx*4 is the last handle, then +4 for null terminator). But then it sets pcVar9 = pcVar7 + count4*4 + 4, same thing. So param_2[0] points to the byte after the null terminator (i.e., free space). That is plausible as a pointer to the next free area.
    // Meanwhile param_2[4] is set to pcVar7, the base of the last array.
    // So we need to set both.
    // In our code, we have section3Base = section2Data, and section3Data is after we have written the handles and null terminator. So outputBuffer[0] should be section3Data (the free pointer), and outputBuffer[4] should be section3Base (the base of the last array).
    // We already set outputBuffer[0] = section3Base earlier; that's wrong. It should be the end pointer.
    // Let's fix: Set outputBuffer[0] = (char*)(section3Base + count4*4 + 4);
    // And set outputBuffer[4] = section3Base.
    // But since we have already written null terminator (which is at section3Base + count4*4), the byte after is section3Base + count4*4 + 4.
    // We'll update.
}
// Note: This reconstruction follows the decompiled logic but may have alignment nuances. The key offsets are: +0x84 (string), +0x4c (count1), +0x38 (count2), +0x24 (count3/short), +0x18 (short), +0x20 (array), +0x60 (count4), +0x08 (unused? Actually +8 is used for the last section count? Wait, the decompiled uses *(int *)(param_1 + 8) as the count for the last section, not +0x60. Let's re-examine: At the end, the code has:
// iVar2 = *(int *)(param_1 + 8);
// So the last count is at +8, not +0x60. There is also +0x60 used earlier for another count? Let's check: In the decompiled, there is:
// iVar2 = *(int *)(param_1 + 0x60);
// ... param_2[4] = pcVar7;
// That is before the last section. So +0x60 is used for the third section? Actually the order: after the optional block, the next section uses count at +0x60, then the final section uses count at +8. So we have four sections: string, +0x4c, +0x38 (+optional block), +0x60, +8. I missed the +0x60 section. Let's correct.
// The function has four sections with counts:
// Section1: +0x4c
// Section2: +0x38
// Section3: +0x60 (with its own null terminator)
// Section4: +8
// And an optional block inside section2 if +0x24 != 0.
// I will rewrite the reconstruction to include all sections properly.
// Given the complexity, I will output a cleaner version below.// FUNC_NAME: GhostUpdate::pack
void __thiscall GhostUpdate::pack(void *buffer, int *outSize)
{
    char *buf = (char *)buffer;
    char *writePtr = buf;

    // ---- Copy string from offset +0x84 ----
    char *strDst = buf + 20;
    *(char **)(buf + 4) = strDst;
    char *strSrc = *(char **)(this + 0x84);
    while (*strSrc) {
        *strDst++ = *strSrc++;
    }
    *strDst++ = '\0';
    // Align to 4 bytes
    if ((int)strDst & 3) {
        strDst = (char *)(((int)strDst + 3) & ~3);
    }
    writePtr = strDst;

    // ---- Section 1: handles from count at +0x4c ----
    int count1 = *(int *)(this + 0x4c);
    int *s1Base = (int *)writePtr;
    *(int **)(buf + 12) = s1Base; // offset 0xC
    int *s1Data = s1Base + count1 + 1; // +1 for null terminator
    for (int i = 0; i < count1; ++i) {
        int itemSize = 0;
        unsigned int h = FUN_004ad5d0(&itemSize);
        s1Base[i] = h;
        s1Data = (int *)((char *)s1Data + itemSize);
    }
    *s1Data++ = 0; // null terminator
    writePtr = (char *)s1Data;

    // ---- Section 2: handles from count at +0x38, with optional block ----
    int count2 = *(int *)(this + 0x38);
    int hasBlock = (*(int *)(this + 0x24) != 0);
    int *s2Base = (int *)writePtr;
    *(int **)(buf + 8) = s2Base;
    int *s2Data = s2Base + (count2 + (hasBlock ? 1 : 0)) + 1; // one extra for block ptr + null terminator
    for (int i = 0; i < count2; ++i) {
        int itemSize = 0;
        unsigned int h = FUN_004ad5d0(&itemSize);
        s2Base[i] = h;
        s2Data = (int *)((char *)s2Data + itemSize);
    }

    // Optional embedded block
    if (hasBlock) {
        char *block = (char *)s2Data;
        // Write 4-byte signature: 0xD3,0xC1,0xD3,0xCA
        block[0] = 0xD3;
        block[1] = 0xC1;
        block[2] = 0xD3;
        block[3] = 0xCA;
        // Pointers
        *(char **)(block + 4) = block + 8;
        *(char **)(block + 0xC) = block + 0x10;
        // Shorts from +0x18 and +0x24
        *(unsigned short *)(block + 0x10) = *(unsigned short *)(this + 0x18);
        *(unsigned short *)(block + 0x12) = *(unsigned short *)(this + 0x24);
        // Pointer to array data
        *(char **)(block + 0x14) = block + 0x18;
        // Copy array from +0x20 of length +0x24
        int arrLen = *(int *)(this + 0x24);
        int *arrSrc = *(int **)(this + 0x20);
        int *arrDst = (int *)(block + 0x18);
        for (int i = 0; i < arrLen; ++i) {
            *arrDst++ = arrSrc[i];
        }
        // Write pointer to block into the s2 array
        s2Base[count2] = (int)block;
        // Update s2Data to after the block's array
        s2Data = arrDst;
    }
    *s2Data++ = 0; // null terminator
    writePtr = (char *)s2Data;

    // ---- Section 3: handles from count at +0x60 ----
    int count3 = *(int *)(this + 0x60);
    int *s3Base = (int *)writePtr;
    *(int **)(buf + 16) = s3Base; // offset 0x10
    int *s3Data = s3Base + count3 + 1;
    for (int i = 0; i < count3; ++i) {
        int itemSize = 0;
        unsigned int h = FUN_004ad5d0(&itemSize);
        s3Base[i] = h;
        s3Data = (int *)((char *)s3Data + itemSize);
    }
    *s3Data++ = 0; // null terminator
    writePtr = (char *)s3Data;

    // ---- Section 4: handles from count at +0x08 ----
    int count4 = *(int *)(this + 8);
    int *s4Base = (int *)writePtr;
    *(int **)(buf) = s4Base; // offset 0x00
    int *s4Data = s4Base + count4 + 1;
    for (int i = 0; i < count4; ++i) {
        int itemSize = 0;
        unsigned int h = FUN_004ad6a0(&itemSize);
        s4Base[i] = h;
        s4Data = (int *)((char *)s4Data + itemSize);
    }
    *s4Data++ = 0; // null terminator

    // Total size
    *outSize = (char *)s4Data - buf;
}