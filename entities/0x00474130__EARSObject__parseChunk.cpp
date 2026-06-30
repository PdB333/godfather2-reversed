// FUNC_NAME: EARSObject::parseChunk
void __thiscall EARSObject::parseChunk(void* this, void* stream) {
    // local iterator state
    bool bIsEmpty = false;          // bVar6
    void* pRef = nullptr;           // local_68
    char bitfieldModeEnabled;       // local_64 (0 = linear, else bitfield)
    int bitfieldBase;               // local_60 (base address for bitfield mask)
    void* pDataArray;               // local_5c (original data array for bitfield)
    unsigned int currentIndex;      // local_58
    unsigned int totalCount;        // local_54
    void* pCurrElement;            // local_50
    unsigned short currIndexShort;  // local_4c
    unsigned int currField;         // local_48 (bitmask field)
    void* iterator;                 // local_8

    // Push marker/scope on stream (magic 0xb390b11a)
    FUN_0043aff0(stream, 0xb390b11a);
    // Pop/init something
    FUN_0043af00(1);

    // Check if iterator is empty
    if (bitfieldModeEnabled == 0) {
        bIsEmpty = (*((void**)iterator) == (void*)0x0);
    } else {
        bIsEmpty = (currentIndex == totalCount);
    }

    // If not empty, clear member at +0xf0
    if (!bIsEmpty) {
        FUN_0043ad90(this + 0xf0);
    }

    bIsEmpty = false;
    pRef = (void*)0x0;

    // Second marker (magic 0x1fb0c602)
    FUN_0043aff0(stream, 0x1fb0c602);

    void* pIter = iterator; // ppuVar3

    do {
        // Check if iterator is empty
        if (bitfieldModeEnabled == 0) {
            bIsEmpty = (*(void**)pIter == (void*)0x0);
        } else {
            bIsEmpty = (currentIndex == totalCount);
        }

        if (bIsEmpty) {
            if (!bIsEmpty) {
                // Use virtual function to get default value for +0x130
                unsigned int defaultVal = (*(unsigned int (**)(void*))PTR_FUN_0110ac0c)(pRef);
                *(unsigned int*)(this + 0x130) = defaultVal;
            }
            return;
        }

        // Determine current element pointer
        void* pElement; // ppuVar5
        if (bitfieldModeEnabled == 0) {
            pElement = pIter;
        } else {
            pElement = &pCurrElement;
        }

        // Check if element is a 16-bit or 32-bit type identifier
        unsigned int typeId;
        if (*(short*)((int)pElement + 6) == 0x25e3) {
            typeId = (unsigned int)*(unsigned short*)(pElement + 1);
        } else {
            typeId = (unsigned int)*((void**)pElement + 1);
        }

        switch (typeId) {
            case 0: // String property at +0x54
            {
                void* pStr;
                if (bitfieldModeEnabled == 0) {
                    pStr = pIter;
                } else {
                    pStr = &pCurrElement;
                }
                if (*(short*)((int)pStr + 6) == 0x25e3) {
                    if (*(void**)pStr == (void*)0x0) {
                        pStr = (void**)&DAT_00e2a89b;
                    } else {
                        pStr = (void**)((int)*((void**)pStr + 2) + (int)*pStr);
                    }
                } else {
                    pStr = (void**)((int)pStr + 2);
                }
                int* targetStr = (int*)(this + 0x54);
                goto LAB_00474226;
            }
            case 1: // String property at +0x5c
            {
                void* pStr;
                if (bitfieldModeEnabled == 0) {
                    pStr = pIter;
                } else {
                    pStr = &pCurrElement;
                }
                if (*(short*)((int)pStr + 6) == 0x25e3) {
                    if (*(void**)pStr == (void*)0x0) {
                        pStr = (void**)&DAT_00e2a89b;
                        targetStr = (int*)(this + 0x5c);
                    } else {
                        pStr = (void**)((int)*((void**)pStr + 2) + (int)*pStr);
                        targetStr = (int*)(this + 0x5c);
                    }
                } else {
                    pStr = (void**)((int)pStr + 2);
                    targetStr = (int*)(this + 0x5c);
                }
                goto LAB_00474226;
            }
            case 2: // String property at +0x134
            {
                void* pStr;
                if (bitfieldModeEnabled == 0) {
                    pStr = pIter;
                } else {
                    pStr = &pCurrElement;
                }
                if (*(short*)((int)pStr + 6) == 0x25e3) {
                    if (*(void**)pStr == (void*)0x0) {
                        pStr = (void**)&DAT_00e2a89b;
                        targetStr = (int*)(this + 0x134);
                    } else {
                        pStr = (void**)((int)*((void**)pStr + 2) + (int)*pStr);
                        targetStr = (int*)(this + 0x134);
                    }
                } else {
                    pStr = (void**)((int)pStr + 2);
                    targetStr = (int*)(this + 0x134);
                }
LAB_00474226:
                // Initialize string (clear then assign if non-empty)
                FUN_004086d0(targetStr);
                FUN_00408310(targetStr);
                if ((pStr != (void**)0x0) && (*(char*)pStr != '\0')) {
                    unsigned int val = FUN_004dafd0(pStr);
                    FUN_00408260(targetStr, val);
                    if (*targetStr != 0) {
                        FUN_00407e60(this + 0x3c, targetStr);
                    }
                }
                break;
            }
            case 3: // Clear list at +0x6c
            {
                FUN_0043ad10(this + 0x6c);
                pIter = iterator; // Reset or continue?
                break;
            }
            case 5: // Set reference pointer
            {
                void* pElem;
                if (bitfieldModeEnabled == 0) {
                    pElem = pIter;
                } else {
                    pElem = &pCurrElement;
                }
                pRef = *((void**)pElem + 2); // Store reference
                break;
            }
            case 6: // Set data pointer at +0x130 with default fallback
            {
                void* pElem;
                if (bitfieldModeEnabled == 0) {
                    pElem = pIter;
                } else {
                    pElem = &pCurrElement;
                }
                void* pData = *((void**)pElem + 2);
                *(void**)(this + 0x130) = pData;
                if (pData == (void*)0x0) {
                    *(unsigned int*)(this + 0x130) = DAT_0110ac04; // Default global
                } else {
                    bIsEmpty = true; // Mark that a custom pointer was set
                }
                break;
            }
            case 7: // String property at +100 (0x64)
            {
                void* pStr;
                if (bitfieldModeEnabled == 0) {
                    pStr = pIter;
                } else {
                    pStr = &pCurrElement;
                }
                if (*(short*)((int)pStr + 6) == 0x25e3) {
                    if (*(void**)pStr == (void*)0x0) {
                        pStr = (void**)&DAT_00e2a89b;
                    } else {
                        pStr = (void**)((int)*((void**)pStr + 2) + (int)*pStr);
                    }
                } else {
                    pStr = (void**)((int)pStr + 2);
                }
                int* targetStr = (int*)(this + 100); // +0x64
                FUN_00408310(targetStr);
                if ((pStr != (void**)0x0) && (*(char*)pStr != '\0')) {
                    unsigned int val = FUN_004dafd0(pStr);
                    FUN_00408260(targetStr, val);
                }
                break;
            }
        }

        // Advance iterator
        if (bitfieldModeEnabled == 0) {
            // Linear list: either null-terminated or counted based on sign
            if ((int)currentIndex < 0) {
                // Negative index => advance using current element as linked list
                iterator = (void**)((int)pIter + (int)*pIter);
                FUN_0043b140(); // Possibly advance something else?
                pIter = iterator;
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex++;
                iterator = (void**)((int)pIter + (int)*pIter);
                pIter = (void**)((int)pIter + (int)*pIter);
            } else {
                iterator = (void**)&DAT_01163cf8; // End sentinel
                pIter = (void**)&DAT_01163cf8;
            }
        } else {
            // Bitfield-based: iterate by index through a dense array
            currentIndex++;
            if (currentIndex != totalCount) {
                currIndexShort = (short)currentIndex;
                // Check if this index is present in bitmask
                if ((*(byte*)((currentIndex >> 3) + bitfieldBase) & (1 << (currentIndex & 7))) == 0) {
                    // Not present: skip, set current element to 0
                    pCurrElement = (void*)0x0;
                    currField = 0;
                } else {
                    // Present: load next data pointer
                    currField = *(unsigned int*)pDataArray;
                    pCurrElement = pDataArray;
                    pDataArray = (void**)((int)pDataArray + 4);
                }
            }
        }
    } while (true);
}