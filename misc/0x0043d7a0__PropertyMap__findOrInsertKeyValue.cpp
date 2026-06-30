// FUNC_NAME: PropertyMap::findOrInsertKeyValue

int* PropertyMap::findOrInsertKeyValue(Container* container, int* key, int value)
{
    int count = container->elementCount;  // param_1[1] = count of stored entries
    int* data = container->dataArray;     // param_1[0] = pointer to array of 7-int elements
    int i = 0;

    // Linear search for a matching key (6 ints)
    if (count > 0) {
        int* currentEntry = data;
        do {
            // Compare all 6 key integers
            if (key[0] == currentEntry[0] &&
                key[1] == currentEntry[1] &&
                key[2] == currentEntry[2] &&
                key[3] == currentEntry[3] &&
                key[4] == currentEntry[4] &&
                key[5] == currentEntry[5]) {
                // Found existing entry – return pointer to its value (7th int)
                return &currentEntry[6];
            }

            // Check for early termination (likely a cancel/abort flag)
            if (FUN_0043cc20() != 0)
                break;

            i++;
            currentEntry += 7; // Step to next entry (each entry is 28 bytes)
        } while (i < count);
    }

    // Not found – allocate a new slot at index i (should be count if loop finished)
    int* newEntry = (int*)FUN_0043d9e0(i); // Possibly resizes and returns pointer to slot i
    if (newEntry != key) { // Guard against self-assignment (shouldn't happen normally)
        // Copy the 6 key integers into the new slot
        newEntry[0] = key[0];
        newEntry[1] = key[1];
        newEntry[2] = key[2];
        newEntry[3] = key[3];
        newEntry[4] = key[4];
        newEntry[5] = key[5];
    }
    // Set the value (7th integer)
    newEntry[6] = value;

    // Return pointer to the value field
    return &newEntry[6];
}