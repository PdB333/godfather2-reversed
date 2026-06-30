// FUNC_NAME: HashTable::getDataByKey
int HashTable::getDataByKey(char* outType, int* outHandle) {
    // lookupContext is used for internal lookup state
    int lookupContext[2];
    lookupContext[0] = 0;

    // Perform a hash table lookup; returns a handle to the found entry (or 0)
    int foundEntry = findHashEntry(lookupContext); // FUN_005f04e0

    // Validate inputs and lookup result
    if (outHandle != 0 && foundEntry != 0) {
        // +0x0C: pointer to the data block
        int* dataBlock = *(int**)(foundEntry + 0x0C);
        if (dataBlock != 0) {
            // +0x04: first byte is a type/flag (char)
            *outType = *(char*)(dataBlock + 1);
            // Store the found entry handle as an output
            *outHandle = foundEntry;

            // After the lookup, lookupContext[0] is a pointer to some structure
            // that contains an index at offset +0x04
            int index = *(int*)(lookupContext[0] + 4);

            // Return a value from an array at offset +0x58 in the data block,
            // indexed by the computed index (each element is 4 bytes)
            return *(int*)((int)dataBlock + 0x58 + index * 4);
        }
    }
    return 0;
}