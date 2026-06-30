// FUNC_NAME: StringTable::findOrCreateEntry
int StringTable::findOrCreateEntry(int thisPtr, KeyPair* key) {
    uint count = *(uint*)(thisPtr + 0x124); // number of entries
    if (count != 0) {
        int* entryPtrArray = (int*)(thisPtr + 0x24); // array of entry pointers
        for (uint i = 0; i < count; i++) {
            int entry = entryPtrArray[i];
            if (*(int*)(entry + 0x28) == key->second) { // compare integer key
                if (*(int*)(entry + 0x28) == 0) {
                    return entry;
                }
                // Compare strings case-insensitively
                byte* str1 = *(byte**)(entry + 0x24);
                byte* str2 = (byte*)key->first;
                int cmpResult;
                do {
                    byte c1 = *str1;
                    byte c2 = *str2;
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        goto done;
                    }
                    if (c1 == 0) break;
                    c1 = str1[1];
                    c2 = str2[1];
                    if (c1 != c2) {
                        cmpResult = (c1 < c2) ? -1 : 1;
                        goto done;
                    }
                    str1 += 2;
                    str2 += 2;
                } while (c1 != 0);
                cmpResult = 0;
done:
                if (cmpResult == 0) {
                    return entry;
                }
            }
        }
    }

    // Allocate new entry
    int newEntry = FUN_009c8e50(0x40); // allocate 64 bytes
    if (newEntry != 0) {
        // Zero-initialize fields from +0x10 to +0x38
        *(int*)(newEntry + 0x10) = 0;
        *(int*)(newEntry + 0x14) = 0;
        *(int*)(newEntry + 0x18) = 0;
        *(int*)(newEntry + 0x1c) = 0;
        *(int*)(newEntry + 0x20) = 0;
        *(int*)(newEntry + 0x24) = 0;
        *(int*)(newEntry + 0x28) = 0;
        *(int*)(newEntry + 0x2c) = 0;
        *(int*)(newEntry + 0x30) = 0;
        *(int*)(newEntry + 0x34) = 0;
        *(int*)(newEntry + 0x38) = 0;
    }

    // Add to array if not full
    if (*(uint*)(thisPtr + 0x124) < 0x40) {
        int* entryArray = (int*)(thisPtr + 0x24);
        entryArray[*(uint*)(thisPtr + 0x124)] = newEntry;
        *(int*)(thisPtr + 0x124) = *(int*)(thisPtr + 0x124) + 1;
    }

    // Set some value from this+0x128
    *(int*)(newEntry + 0x38) = *(int*)(thisPtr + 0x128);

    // Copy the string (key->first) into the entry
    FUN_004d3e20(key); // likely copies string to entry->string

    // Compute hash of the string (case-insensitive for letters)
    byte* str = (byte*)key->first;
    if (str == nullptr) {
        str = (byte*)&DAT_0120546e; // default empty string?
    }
    int hash = 0;
    if (str != nullptr) {
        byte c = *str;
        while (c != 0) {
            uint uc = (uint)c;
            str++;
            if (uc - 0x41 < 0x1a) { // 'A' to 'Z'
                uc = uc + 0x20; // lowercase
            }
            hash = hash * 0x1003f + uc;
            c = *str;
        }
    }
    *(int*)(newEntry + 0x3c) = hash;

    return newEntry;
}