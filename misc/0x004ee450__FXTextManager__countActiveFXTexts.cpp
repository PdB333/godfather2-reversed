// FUNC_NAME: FXTextManager::countActiveFXTexts
int __thiscall FXTextManager::countActiveFXTexts(int* this) {
    int slotCount;
    int activeCount = 0;

    if (*this == 0) {
        slotCount = 0;
    } else {
        // +0x80: Number of slots in the effect array (short)
        slotCount = *(short*)(*this + 0x80);
    }

    if (slotCount == 0) {
        return 0;
    }

    // Array of slot descriptors starts at +0xf0, each 0x14 bytes
    int slotOffset = 0xf0;
    for (int i = 0; i < slotCount; i++) {
        if (*this != 0) {
            int slotAddr = *this + slotOffset;
            if (slotAddr != 0) {
                // slot entry: +4 = pointer to the effect object
                int** ppFxObj = (int**)(slotAddr + 4);
                int* pFxObj = *ppFxObj;
                if (pFxObj != (int*)0x0) {
                    // Call virtual function at index 2 (vtable+8) – returns a name/type info pointer
                    int* pNameInfo = (int*)((**ppFxObj)(pFxObj)); // __thiscall call via vtable
                    if (pNameInfo != 0) {
                        // Compare string at pNameInfo+4 with "FXText" (6 chars + null = 7 chars)
                        char* name = (char*)pNameInfo[1]; // offset 4
                        bool bMatch = true;
                        char* ref = "FXText";
                        int cmpLen = 7; // includes terminator
                        char* np = name;
                        char* rp = ref;
                        do {
                            if (cmpLen == 0) break;
                            cmpLen--;
                            bMatch = (*np == *rp);
                            np++;
                            rp++;
                        } while (bMatch);

                        if (bMatch) {
                            // pFxObj[9] (offset 0x24) is a flag indicating active/visible
                            if (pFxObj[9] != 0) {
                                activeCount++;
                            }
                        }
                    }
                }
            }
        }
        slotOffset += 0x14;
    }
    return activeCount;
}