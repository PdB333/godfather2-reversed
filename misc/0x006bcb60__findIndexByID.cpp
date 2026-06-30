// FUNC_NAME: findIndexByID
// Address: 0x006bcb60
// Searches an array of 8-byte pairs (ID at offset +4) for a matching ID, returns index or -1.
// Structure offsets: +0x68 = pointer to array of pairs (int, int), +0x6c = count of pairs.

int __thiscall findIndexByID(int this, int id) {
    int resultIndex = -1;
    if (id != 0) {
        int* currentPtr = *(int**)(this + 0x68);       // +0x68: array base
        int count = *(int*)(this + 0x6c);              // +0x6c: element count
        int* endPtr = currentPtr + count * 2;          // each pair is 2 ints (8 bytes)
        int index = 0;
        while (true) {
            resultIndex = index;
            if (*(currentPtr + 1) == id) {             // second int in pair is the ID
                break;
            }
            currentPtr += 2;                           // advance to next pair
            index++;
            if (currentPtr == endPtr) {
                return -1;                             // not found
            }
        }
    }
    return resultIndex;
}