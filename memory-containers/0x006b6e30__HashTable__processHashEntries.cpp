// FUNC_NAME: HashTable::processHashEntries
void __fastcall HashTable::processHashEntries(int* entryData)
{
    int count = *entryData - 1; // number of entries (first element is count-1? Actually *param_1 is count? But code subtracts 1, so original count stored)
    if (count < 0) {
        return;
    }

    // Each entry is 5 ints (20 bytes). Pointer to current entry's field[3]
    uint* fieldPtr = (uint*)(entryData + count * 5 + 3);

    do {
        uint field1 = fieldPtr[-2]; // entry->field[1]
        uint field2 = fieldPtr[-1]; // entry->field[2]
        uint field3 = *fieldPtr;    // entry->field[3]
        uint field4 = fieldPtr[1];  // entry->field[4]

        // Hash = (((field1 * 33 + field2) * 33 + field3) * 33) + field4
        uint64_t intermediate = (uint64_t)field1 * 33 + field2;
        intermediate = intermediate * 33 + field3;
        int hash = (int)(intermediate * 33) + field4;

        logHash(2, hash, 0, 1); // Assume external hash logging function
        count--;
        fieldPtr -= 5; // Move to previous entry
    } while (count >= 0);
}