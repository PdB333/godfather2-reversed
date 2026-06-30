// FUNC_NAME: PathString::InitializeFromResource

void __fastcall PathString::InitializeFromResource(int sourceObj, PathStringContext *destInESI)
{
    char *sourcePath;
    char curChar;
    int stringLength;
    undefined4 allocatorResult; // Actually pointer from allocation
    void *allocatedMemory;

    // Clear the destination structure fields (two zero init)
    destInESI->field0 = 0;
    destInESI->field2_byte = 0; // offset +0x08 byte (written as byte at &dest[2])

    // Select the source path: prefer full path at +0x88, fallback to relative at +0x7c
    sourcePath = *(char **)(sourceObj + 0x88);
    if (sourcePath == (char *)0x0) {
        sourcePath = *(char **)(sourceObj + 0x7c);
    }

    // Store the original pointer (without ownership)
    destInESI->sourcePointer = sourcePath; // offset +0x0C

    // Count characters until null
    destInESI->charCount = 0; // offset +0x10
    curChar = *sourcePath;
    while (curChar != '\0') {
        destInESI->charCount++;
        curChar = *(sourcePath + destInESI->charCount);
    }

    // Store the length (same as count)
    destInESI->stringLength = destInESI->charCount; // offset +0x04

    // Prepare allocator parameters (stack locals for allocation)
    undefined4 allocParam[3] = {0, 0, 0};

    // Call allocator from global function table (DAT_012234ec + 4) with size = length+1
    allocatorResult = ((undefined4 (*)(int, undefined4 *))(*((undefined4 **)DAT_012234ec + 1)))
                        (destInESI->stringLength + 1, allocParam);
    destInESI->allocatedCopy = allocatorResult; // offset +0x14

    // Initialize remaining fields to zero
    destInESI->field24 = 0; // offset +0x18
    destInESI->field28 = 0; // offset +0x1C
}

// Note: Offsets relative to destInESI pointer:
//   +0x00: field0 (int)
//   +0x04: stringLength (int, also stored as int at +0x10 after counting)
//   +0x08: field2_byte (char, written as byte)
//   +0x0C: sourcePointer (char*)
//   +0x10: charCount (int)
//   +0x14: allocatedCopy (void*)
//   +0x18: field24 (int)
//   +0x1C: field28 (int)