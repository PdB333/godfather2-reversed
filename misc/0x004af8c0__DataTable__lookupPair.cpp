// FUNC_NAME: DataTable::lookupPair
int* DataTable::lookupPair(int id, int* outValues)
{
    // Array of 4-int entries stored at +0x74, count at +0x78
    if (0 < count) {
        int* entry = dataArray; // +0x74
        for (int i = 0; i < count; i++) {
            if (entry[i * 4] == id) {
                outValues[1] = entry[i * 4 + 3]; // second value
                outValues[0] = entry[i * 4 + 2]; // first value
                return outValues;
            }
        }
    }
    outValues[0] = 0;
    outValues[1] = 0;
    return outValues;
}