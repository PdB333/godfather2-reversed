// FUNC_NAME: processResourceEntry
void processResourceEntry(void)
{
    int entryIndex;
    int *stackTop;
    int entryOffset;
    uint64 field1;
    uint64 field2;
    uint32 field3;

    // Global resource array index (DAT_00e50bc4)
    entryIndex = DAT_00e50bc4;
    entryOffset = entryIndex * 0x14; // 20 bytes per entry

    // Load 3 fields from the resource table at offsets 0, 8, 16
    field1 = *(uint64 *)(&DAT_00e50bd0 + entryOffset);
    field2 = *(uint64 *)(&DAT_00e50bd8 + entryOffset);
    field3 = *(uint32 *)(&DAT_00e50be0 + entryOffset);

    // Push a pointer (likely a vtable or command ID) onto a global stack/task queue
    stackTop = (int *)(DAT_01206880 + 0x14);  // +0x14 stack pointer
    **(uint32 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e50c5c;
    *stackTop += 4;  // advance stack pointer

    // Copy the 3 fields into a local buffer (maybe for further processing)
    FUN_0049c430(&field1, 0x14, 4);  // possibly memcpy? (destination, size, something)

    // Dispatch the actual processing with the raw fields from the global table
    FUN_0069fcb0(field1, field2, field3);
}