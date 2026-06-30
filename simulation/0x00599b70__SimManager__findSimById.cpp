// FUNC_NAME: SimManager::findSimById
// Function address: 0x00599b70
// Searches for an object with matching ID (+0x74) using a list of indices.
// The "this" object holds:
//   - count (byte) at +0x9a
//   - array of indices (bytes) at +0x9c
//   - pointer to a pool structure (ObjectPool) at +0x1bc
// The pool structure contains:
//   - validation flags (int*) at +0x30 (entry == -2 means invalid)
//   - object pointers (int**) at +0x2c

int SimManager::findSimById(int thisPtr, int targetId) {
    int idxCount = *(char*)(thisPtr + 0x9a);
    int i = 0;
    if (idxCount != 0) {
        do {
            unsigned int index = (unsigned int)*(unsigned char*)(thisPtr + 0x9c + i);
            int poolPtr = *(int*)(thisPtr + 0x1bc);
            int* validTable = *(int**)(poolPtr + 0x30);
            if (validTable[index] != -2) {
                // Global debug/error handler (likely assertion failure)
                (**(code**)(*DAT_01205590 + 4))();
            }
            int** objectTable = *(int***)(poolPtr + 0x2c);
            int* object = objectTable[index];
            if (*(int*)(object + 0x74) == targetId) {
                return (int)object;
            }
            i++;
        } while (i < (int)(unsigned int)*(unsigned char*)(thisPtr + 0x9a));
    }
    return 0;
}