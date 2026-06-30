// FUNC_NAME: StringTable::findIndexByName

void StringTable::findIndexByName(const char* name, uint& outIndex) const {
    // this struct layout:
    // +0x0C: char* entries (array of 8-byte fixed-size strings)
    // +0x14: uint count
    uint count = *(uint*)((char*)this + 0x14);
    if (count == 0) {
        return;
    }

    char* entries = *(char**)((char*)this + 0x0C);
    for (uint i = 0; i < count; ++i) {
        char* entry = entries + i * 8;

        int cmp;
        if (name == nullptr || entry == nullptr) {
            // When either pointer is null, compare addresses directly.
            if (name <= entry) {
                cmp = (name < entry) ? -1 : 0; // yields 0 if equal, -1 if less
            } else {
                cmp = 1; // name > entry
            }
        } else {
            cmp = __stricmp(name, entry);
        }

        if (cmp == 0) {
            outIndex = i;
            return;
        }
    }
}