// FUNC_NAME: ObjectTable::findByQuadKey
int __thiscall ObjectTable::findByQuadKey(int thisPtr, int *key) {
    int count = *(int *)(thisPtr + 0x18); // +0x18: number of elements
    int *arrayBase = *(int **)(thisPtr + 0x14); // +0x14: pointer to array of pointers
    if (count != 0) {
        int *iter = arrayBase;
        for (uint i = 0; i < (uint)count; i++) {
            int *element = (int *)*iter;
            // Compare 4 ints at element offsets +0x24, +0x28, +0x2C, +0x30 with key[0..3]
            if (element[9] == key[0] &&    // +0x24
                element[10] == key[1] &&   // +0x28
                element[11] == key[2] &&   // +0x2C
                element[12] == key[3]) {   // +0x30
                return arrayBase[i];       // Return pointer to matching element
            }
            iter++;
        }
    }
    return 0; // Not found
}