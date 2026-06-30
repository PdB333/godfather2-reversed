// FUNC_NAME: EntryList::serializeEntryList
void EntryList::serializeEntryList()
{
    int count = *(int*)(this + 0x38); // +0x38: number of entries
    // Write total count
    g_serializer.write(&count, 4);

    if (count <= 0)
        return;

    int entryIndex = 0;
    int remaining = count;
    do {
        int dataPtr = *(int*)(entryIndex + *(int*)(this + 0x18)); // +0x18: base pointer to entry array
        if (dataPtr == 0 || dataPtr + 0x10 == 0) {
            // Invalid or null data pointer: write zero count
            int zeroCount = 0;
            g_serializer.write(&zeroCount, 4);
        } else {
            int dataSize = *(int*)(dataPtr + 0xc) + 1; // +0x0c: length of data (includes null terminator)
            g_serializer.write(&dataSize, 4);
            g_serializer.write((void*)(dataPtr + 0x10), dataSize); // +0x10: actual data (e.g., string)
        }

        int value1 = *(int*)(*(int*)(this + 0x18) + 4 + entryIndex); // +0x04: first value
        g_serializer.write(&value1, 4);

        int value2 = *(int*)(*(int*)(this + 0x18) + 8 + entryIndex); // +0x08: second value
        g_serializer.write(&value2, 4);

        entryIndex += 0xc; // each entry is 12 bytes
        remaining--;
    } while (remaining != 0);
}