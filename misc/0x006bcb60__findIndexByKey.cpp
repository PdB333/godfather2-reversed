// FUNC_NAME: findIndexByKey
int __thiscall findIndexByKey(void* thisPtr, int key) {
    int* arrayStart = *(int**)((char*)thisPtr + 0x68);  // array of 8-byte entries (struct { int value; int key; }?)
    int count = *(int*)((char*)thisPtr + 0x6c);         // number of entries
    int* arrayEnd = arrayStart + count * 2;             // each entry is 2 ints (8 bytes)

    if (key == 0) {
        return -1;
    }

    int index = 0;
    for (int* entry = arrayStart; entry != arrayEnd; entry += 2) {
        if (entry[1] == key) {  // compare the second int (key field)
            return index;
        }
        index++;
    }

    return -1;
}