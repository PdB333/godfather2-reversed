// FUNC_NAME: StringIDMapper::resolveStringsToIDs
void __thiscall StringIDMapper::resolveStringsToIDs(void *this, IDMappingContext *context) {
    // context structure:
    // +0x00: char* const* pStrings - array of pointers to null-terminated strings
    // +0x04: short* pOutIDs - output buffer for 16-bit IDs
    // +0x08: int* pCount - input: number of strings, output: number of successfully resolved IDs
    // the function modifies the count in-place.

    char *const *pStringPtrs = context->pStrings;
    int *pCount = &context->count;
    short *pOutBuf = context->pOutIDs;
    int currentIdx = 0; // how many IDs we've stored
    int stringIdx = 0;

    if (0 < *pCount) {
        do {
            const char *str = pStringPtrs[stringIdx];
            int hash = 0; // will be built

            if (str != nullptr) {
                char c = *str;
                while (c != '\0') {
                    uint32_t ch = (uint32_t)c;
                    // case-insensitive: convert A-Z to a-z
                    if (ch - 'A' < 26) {
                        ch += 0x20;
                    }
                    hash = hash * 0x1003f + ch;
                    str++;
                    c = *str;
                }
            }

            // Use member data: this + 0x70 points to a table manager object
            // That object's layout (++0x70):
            //   +0x00: vtable
            //   +0x1c: pointer to a base of hash table entries
            // Then inside that base, there's an array of structures of size 0x18.
            // this+0x74 is an index into that array (a short).
            if (*(void **)((uintptr_t)this + 0x70) != nullptr) {
                void *tableMgr = *(void **)((uintptr_t)this + 0x70);
                void *pBase = *(void **)((uintptr_t)tableMgr + 0x1c);
                short index = *(short *)((uintptr_t)this + 0x74);
                void *entryBase = (void *)((uintptr_t)pBase + 0x14 + index * 0x18);
                int tableIdx = FUN_005828a0(hash, entryBase);
                if ((tableIdx != -1) && (tableIdx < 0x7FFFFFFF)) {
                    int id = *(int *)((uintptr_t)entryBase + 0x10 + tableIdx * 0x14);
                    if ((id != -1) && (id >= 0)) {
                        pOutBuf[currentIdx] = (short)id;
                        currentIdx++;
                    }
                }
            }

            stringIdx++;
        } while (stringIdx < *pCount);
    }

    // update output count
    *pCount = currentIdx;
}