// FUNC_NAME: CommandBuffer::processCommand
// Address: 0x006761b0
// Role: Parses a 10-byte command from the internal buffer and executes delete or returns success indicator.
// The command buffer has fields: m_pBuffer (+0), m_currentOffset (+4), m_baseOffset (+12 maybe).
// Command tags: 0x00010000/0x00020000 (delete), "OTTO" (delete), "ttcf"/"true" (return 1).

int __thiscall CommandBuffer::processCommand(void) {
    int& currentOffset = *(int*)((char*)this + 4); // +0x04
    int& baseOffset = *(int*)((char*)this + 12);   // +0x0C
    char* buffer = *(char**)this;                   // +0x00

    int base = baseOffset;
    char* commandPtr = buffer + base;
    currentOffset = base; // save base as current offset for potential rollback

    // Read 10-byte command record
    unsigned int tag = *(unsigned int*)commandPtr;
    unsigned int data1 = *(unsigned int*)(commandPtr + 4);
    unsigned short data2 = *(unsigned short*)(commandPtr + 8);
    currentOffset = base + 10; // advance past command

    // Extract tag bytes
    char byte0 = (char)tag;
    char byte1 = (char)(tag >> 8);
    char byte2 = (char)(tag >> 16);
    char byte3 = (char)(tag >> 24);

    // Check for delete commands
    if (byte0 == '\0') {
        // Accept: tag = 0x00010000 (byte0=0, byte1=1, byte2=0, byte3=0)
        // OR tag = 0x00020000 (byte0=0, byte1=2, byte2=0, byte3=0)
        if (!((byte1 != 1 && byte1 != 2) || byte2 != 0)) {
            if (byte3 == '\0') {
                goto deleteCommand;
            }
        }
        goto errorExit;
    } else if (byte0 == 'O') {
        // Check for "OTTO"
        if (byte1 == 'T' && byte2 == 'T' && byte3 == 'O') {
            goto deleteCommand;
        }
    }

    // Check for success commands: "ttcf" (0x74746366) or "true" (0x74727565)
    if (byte0 == 't') {
        if (byte1 == 't' && byte2 == 'c' && byte3 == 'f') {
            currentOffset = baseOffset; // rollback to base for success
            return 1;
        } else if (byte1 == 'r' && byte2 == 'u' && byte3 == 'e') {
            currentOffset = baseOffset;
            return 1;
        }
    }

    // Fall through to error
    goto errorExit;

deleteCommand:
    {
        // Process the delete: re-read 10 bytes from base (tag was already read)
        currentOffset = base;
        unsigned int fullTag = *(unsigned int*)commandPtr;  // same as tag
        unsigned int extraData1 = *(unsigned int*)(commandPtr + 4);
        unsigned short extraData2 = *(unsigned short*)(commandPtr + 8);
        // local_10 is the 10-byte record
        char record[10];
        memcpy(record, commandPtr, 10);

        // Find object by the record
        int objIndex = findObjectByData(record); // FUN_00672e60
        int* listHead = getListHead();           // FUN_00673070
        *listHead = 0;
        beginOperation();                       // FUN_00675350

        // Remove from linked list at offset +0x0C
        *(int*)(*(int*)(objIndex + 12) + (listHead[-2] * 4)) = 0;
        *(int*)(objIndex + 4) = *(int*)(objIndex + 4) - 1;

        // Free memory blocks
        releaseMemory(listHead - 4);             // (*DAT_01206694)(puVar3 - 4)
        endOperation();                         // FUN_00672fd0
        releaseMemory(*(void**)(objIndex + 12)); // free list
        releaseMemory((void*)objIndex);          // free object

        // Restore tag for final checks
        unsigned int restoredTag = fullTag;
        // Note: after delete, the code continues to the final comparisons but for delete tags
        // the final comparisons will fail, so it falls to errorExit.
        // However the decompiled code shows it goes through final checks after delete block.
        // We simulate that by not returning here.
    }

    // Re-check for success commands (after delete block the code does this)
    // But the decompiled logic re-evaluates the tag bytes:
    // local_c = uVar1; then if cVar2 't' etc.
    // This is effectively a duplicate check that will fail for delete tags.
    // So we skip and go to error exit.
    goto errorExit;

errorExit:
    currentOffset = baseOffset; // reset offset to base on failure
    return 0;
}