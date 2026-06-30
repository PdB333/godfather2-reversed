// FUNC_NAME: NameTable::findIndex
int NameTable::findIndex(const char* name)
{
    char** entries = *(char***)(this + 0xb0); // +0xb0: array of entries (each 0x60 bytes)
    int count = *(int*)(this + 0xa8);          // +0xa8: number of entries

    if (count == 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        char* entryName = entries[i]; // each entry starts with a char* (string name)
        if (entryName == nullptr || name == nullptr) {
            if (entryName <= name) {
                if (entryName < name) {
                    // not equal
                } else {
                    // equal (both null pointers or same pointer)
                    if (entryName == name) {
                        return i;
                    }
                }
            }
        } else {
            if (__stricmp(entryName, name) == 0) {
                return i;
            }
        }
    }
    return -1;
}