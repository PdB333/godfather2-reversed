// FUNC_NAME: LookupIndexByFloat
// Address: 0x00499010
// Fastcall: ecx ignored (reserved but unused), edx = pointer to search params struct
// Struct offsets: +0x00 unknown, +0x04 int startIndex?, +0x08 uint count, +0x0c float targetValue
// Global state: gCurrentSearchIndex (DAT_012054b4), gTableMask (DAT_010c2678), gThresholdTable (DAT_010c2680) - float array

uint __fastcall LookupIndexByFloat(void* /*unused ecx*/, int* params)
{
    uint localIndex;      // index within the unrolled scan (0,1,2,...)
    uint currentGlobal;   // current absolute index before mask
    uint maxIndex;        // total number of entries to scan

    // The effective number of entries to test is min(count, startIndex+2)
    maxIndex = *(int*)(params + 4) + 2;  // +0x04
    if (*(uint*)(params + 8) < maxIndex) {   // +0x08
        maxIndex = *(uint*)(params + 8);
    }

    currentGlobal = gCurrentSearchIndex;
    localIndex = 0;

    // Unrolled loop: process 4 entries per iteration
    if (maxIndex > 3) {
        do {
            // Check first of the batch
            if (*(float*)(params + 0x0c) < gThresholdTable[gTableMask & currentGlobal] ||
                *(float*)(params + 0x0c) == gThresholdTable[gTableMask & currentGlobal]) {
                gCurrentSearchIndex = currentGlobal + 1;
                return localIndex;
            }
            gCurrentSearchIndex = currentGlobal + 2;

            // Check second
            if (*(float*)(params + 0x0c) < gThresholdTable[gTableMask & (currentGlobal + 1)] ||
                *(float*)(params + 0x0c) == gThresholdTable[gTableMask & (currentGlobal + 1)]) {
                return localIndex + 1;
            }
            gCurrentSearchIndex = currentGlobal + 3;

            // Check third
            if (*(float*)(params + 0x0c) < gThresholdTable[gTableMask & (currentGlobal + 2)] ||
                *(float*)(params + 0x0c) == gThresholdTable[gTableMask & (currentGlobal + 2)]) {
                return localIndex + 2;
            }
            currentGlobal += 4;

            // Check fourth
            if (*(float*)(params + 0x0c) < gThresholdTable[gTableMask & gCurrentSearchIndex] ||
                *(float*)(params + 0x0c) == gThresholdTable[gTableMask & gCurrentSearchIndex]) {
                gCurrentSearchIndex = currentGlobal;
                return localIndex + 3;
            }
            localIndex += 4;
            gCurrentSearchIndex = currentGlobal;
        } while (localIndex < maxIndex - 3);
    }

    // Process remaining entries (less than 4)
    if (localIndex < maxIndex) {
        while (true) {
            currentGlobal = gTableMask & gCurrentSearchIndex;
            gCurrentSearchIndex = gCurrentSearchIndex + 1;
            if (*(float*)(params + 0x0c) < gThresholdTable[currentGlobal] ||
                *(float*)(params + 0x0c) == gThresholdTable[currentGlobal]) {
                break;
            }
            localIndex++;
            if (maxIndex <= localIndex) {
                return localIndex;
            }
        }
    }
    return localIndex;
}