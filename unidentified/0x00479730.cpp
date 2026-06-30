// FUN_00479730: InputManager::applyBindingList
void __thiscall InputManager::applyBindingList(void* thisPtr, void* bindingData) {
    // param_1 = thisPtr, param_2 = bindingData
    // Debug validation (likely a CRC or checksum)
    FUN_0043aff0(bindingData, 0x7be194ee); // Assume validation function

    // Iteration state variables (local_64 flags mode)
    bool useLinkedList = (local_64 == 0); // local_64
    // For linked list mode
    void** currentListEntry = local_8; // ppuVar4
    int listIndex = local_58; // index in bitfield mode
    int totalCount = local_54; // total items in bitfield mode
    int* bitfieldBase = local_60; // address of bitfield array
    unsigned int* bitfieldArray = local_5c; // pointer to current bitfield word
    void* currentItem = local_50; // current item pointer
    int currentItemExtra = local_48; // extra field
    short shortLocal = local_4c; // index short

    do {
        // Termination check (local_64 == 0 means linked list, else bitfield)
        bool done;
        if (useLinkedList) {
            done = (*currentListEntry == NULL);
        } else {
            done = (listIndex == totalCount);
        }
        if (done) {
            return;
        }

        void** itemPtr;
        if (useLinkedList) {
            itemPtr = currentListEntry;
        } else {
            itemPtr = &currentItem;
        }

        // Determine the action ID (switch value) from the item
        int actionId;
        // Check if the item is a "direct" type (offset +6 has magic 0x25e3)
        if (*(short*)((int)itemPtr + 6) == 0x25e3) {
            // Direct type: action ID stored as short in next field (itemPtr + 4)
            actionId = (unsigned short)*(int*)((int)itemPtr + 4);
        } else {
            // Indirect type: action ID stored as pointer to value
            actionId = (int)*(void**)((int)itemPtr + 4);
        }

        // Based on the action ID, apply the binding
        switch (actionId) {
            case 0: { // Action Up (or similar)
                // Determine source data for binding value
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                // Check type again
                if (*(short*)((int)src + 6) == 0x25e3) {
                    // Direct type: if *src is NULL, use global default
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b; // global default string or value
                    } else {
                        src = (void*)((int)src[2] + (int)*src); // computed offset
                    }
                } else {
                    src = (void*)((int)src + 8); // skip past type? (struct size 8)
                }

                // Access binding slot at +0x50
                int* binding = (int*)((int)thisPtr + 0x50); // m_upBinding
                FUN_004086d0(binding); // Clear binding
                FUN_00408310(binding); // Initialize binding
                if (src == NULL || *(char*)src == '\0') {
                    // No valid source: check if binding was already loaded
                    if (*binding != 0) {
                        // Mark flag bit 0 as valid
                        *(unsigned int*)((int)thisPtr + 0x70) |= 1; // m_bindingFlags bit0
                        currentListEntry = local_8; // reset iterator
                        break;
                    }
                } else {
                    // Convert source string to hash (or key code)
                    unsigned int val = FUN_004dafd0(src); // Hash or parse
                    FUN_00408260(binding, val); // Set binding value
                    if (*binding != 0) {
                        // Register binding in container at +0x3c
                        FUN_00407e60((int)thisPtr + 0x3c, binding); // m_bindingList
                        goto LAB_00479800; // same as no source case
                    }
                }
                // If binding failed, clear flag bit 0
                *(unsigned int*)((int)thisPtr + 0x70) &= 0xFFFFFFFE;
                currentListEntry = local_8;
                break;
            }
            case 1: { // Action Down
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                if (*(short*)((int)src + 6) == 0x25e3) {
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b;
                    } else {
                        src = (void*)((int)src[2] + (int)*src);
                    }
                } else {
                    src = (void*)((int)src + 8);
                }

                int* binding = (int*)((int)thisPtr + 0x58); // m_downBinding
                FUN_004086d0(binding);
                FUN_00408310(binding);
                if (src == NULL || *(char*)src == '\0') {
                    if (*binding != 0) {
                        *(unsigned int*)((int)thisPtr + 0x70) |= 2; // bit1
                        currentListEntry = local_8;
                        break;
                    }
                } else {
                    unsigned int val = FUN_004dafd0(src);
                    FUN_00408260(binding, val);
                    if (*binding != 0) {
                        FUN_00407e60((int)thisPtr + 0x3c, binding);
                        goto LAB_004798cf;
                    }
                }
                *(unsigned int*)((int)thisPtr + 0x70) &= 0xFFFFFFFD;
                currentListEntry = local_8;
                break;
            }
            case 2: { // Action Left
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                if (*(short*)((int)src + 6) == 0x25e3) {
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b;
                    } else {
                        src = (void*)((int)src[2] + (int)*src);
                    }
                } else {
                    src = (void*)((int)src + 8);
                }

                int* binding = (int*)((int)thisPtr + 0x60); // m_leftBinding
                FUN_004086d0(binding);
                FUN_00408310(binding);
                if (src == NULL || *(char*)src == '\0') {
                    if (*binding != 0) {
                        *(unsigned int*)((int)thisPtr + 0x70) |= 4; // bit2
                        currentListEntry = local_8;
                        break;
                    }
                } else {
                    unsigned int val = FUN_004dafd0(src);
                    FUN_00408260(binding, val);
                    if (*binding != 0) {
                        FUN_00407e60((int)thisPtr + 0x3c, binding);
                        goto LAB_0047994e;
                    }
                }
                *(unsigned int*)((int)thisPtr + 0x70) &= 0xFFFFFFFB;
                currentListEntry = local_8;
                break;
            }
            case 3: { // Action Right
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                if (*(short*)((int)src + 6) == 0x25e3) {
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b;
                    } else {
                        src = (void*)((int)src[2] + (int)*src);
                    }
                } else {
                    src = (void*)((int)src + 8);
                }

                int* binding = (int*)((int)thisPtr + 0x68); // m_rightBinding
                FUN_004086d0(binding);
                FUN_00408310(binding);
                if (src == NULL || *(char*)src == '\0') {
                    if (*binding != 0) {
                        *(unsigned int*)((int)thisPtr + 0x70) |= 8; // bit3
                        currentListEntry = local_8;
                        break;
                    }
                } else {
                    unsigned int val = FUN_004dafd0(src);
                    FUN_00408260(binding, val);
                    if (*binding != 0) {
                        FUN_00407e60((int)thisPtr + 0x3c, binding);
                        goto LAB_004799cd;
                    }
                }
                *(unsigned int*)((int)thisPtr + 0x70) &= 0xFFFFFFF7;
                currentListEntry = local_8;
                break;
            }
            case 4: { // Action Confirm (or special)
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                if (*(short*)((int)src + 6) == 0x25e3) {
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b;
                    } else {
                        src = (void*)((int)src[2] + (int)*src);
                    }
                } else {
                    src = (void*)((int)src + 8);
                }
                // Initialize binding at +0x7c (m_confirmBinding?)
                FUN_00408310((int)thisPtr + 0x7c);
                if (src != NULL && *(char*)src != '\0') {
                    unsigned int val = FUN_004dafd0(src);
                    FUN_00408260((int)thisPtr + 0x7c, val);
                }
                break;
            }
            case 5: { // Action Special (set pointer)
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                // Store pointer from src+8 into +0x78
                *(void**)((int)thisPtr + 0x78) = *((void**)src + 2); // m_specialPtr
                break;
            }
            case 6: { // Action Other (another binding)
                void* src;
                if (useLinkedList) {
                    src = currentListEntry;
                } else {
                    src = &currentItem;
                }
                if (*(short*)((int)src + 6) == 0x25e3) {
                    if (*src == NULL) {
                        src = (void*)&DAT_00e2a89b;
                    } else {
                        src = (void*)((int)src[2] + (int)*src);
                    }
                } else {
                    src = (void*)((int)src + 8);
                }

                int* binding = (int*)((int)thisPtr + 0x84); // m_extraBinding
                FUN_004086d0(binding);
                FUN_00408310(binding);
                if (src != NULL && *(char*)src != '\0') {
                    unsigned int val = FUN_004dafd0(src);
                    FUN_00408260(binding, val);
                    if (*binding != 0) {
                        FUN_00407e60((int)thisPtr + 0x3c, binding);
                    }
                }
                break;
            }
        }

        // Update iteration state
        if (useLinkedList) {
            // Linked list: advance to next node
            if ((int)listIndex < 0) {
                // Special case: negative index means restart from current + offset?
                local_8 = (void**)((int)currentListEntry + (int)*currentListEntry);
                FUN_0043b140(); // Some iteration helper
                currentListEntry = local_8;
            } else if ((int)listIndex < (int)(totalCount - 1)) {
                // Advance to next entry
                listIndex++;
                local_8 = (void**)((int)currentListEntry + (int)*currentListEntry);
                currentListEntry = (void**)((int)currentListEntry + (int)*currentListEntry);
            } else {
                // End of list, loop back to global sentinel
                local_8 = (void**)&DAT_01163cf8; // Global end marker
                currentListEntry = (void**)&DAT_01163cf8;
            }
        } else {
            // Bitfield mode: advance index
            listIndex++;
            if (listIndex != totalCount) {
                shortLocal = (short)listIndex; // Not used further? Maybe debug
                // Check if bit at this index is set in bitfield
                unsigned char bitMask = (unsigned char)(1 << ((unsigned char)listIndex & 7));
                if ((*(unsigned char*)((int)bitfieldBase + (listIndex >> 3)) & bitMask) == 0) {
                    // Bit not set: skip, use next value from bitfield array
                    currentItemExtra = *bitfieldArray; // actually this might be the extra data
                    currentItem = (void*)bitfieldArray; // Overwrites currentItem?
                    bitfieldArray++;
                } else {
                    // Bit set: this item is valid
                    currentItem = NULL; // marker for missing?
                    currentItemExtra = 0;
                }
            }
        }
    } while (true);
}