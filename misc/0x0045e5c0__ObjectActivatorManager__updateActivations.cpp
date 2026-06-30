// FUNC_NAME: ObjectActivatorManager::updateActivations

class ObjectActivatorManager {
public:
    void updateActivations();
private:
    // +0x184: flags (bit 1 = 0x02: system disabled)
    int flags;
    // +0x21c: pointer to array of 8-byte entries (object pointers)
    int* objectEntryArray;
    // +0x220: number of entries
    int entryCount;
};

void __fastcall ObjectActivatorManager::updateActivations() {
    int* entryArray = this->objectEntryArray;
    int count = this->entryCount;
    int i = 0;

    if (count != 0) {
        do {
            // Each entry is 8 bytes; first 4 bytes are object pointer
            int* object = *(int**)(entryArray + i * 2); // cast to treat as int*; offset = i*8 bytes
            if (((this->flags & 2) == 0) && (object != 0)) {
                if (*(char*)(object + 0x0A) == 0) { // +0x28 in byte offsets, object base is char*? Actually object is int*, so +0x28/4 = +0x0A as int offset
                    FUN_00558860(object);
                    *(char*)(object + 0x0A) = 1; // set activation flag
                }
                else {
                    FUN_00558c60();
                    if ((*(int*)(object + 7) != 0) && (*(int*)(*(int*)(object + 7) + 2) != 0)) { // +0x1c = 7 ints, +0x8 = 2 ints
                        FUN_00558b70();
                    }
                }
            }
            i++;
        } while (i < count);
    }
}