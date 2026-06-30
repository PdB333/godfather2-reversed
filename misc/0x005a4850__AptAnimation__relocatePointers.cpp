// FUNC_NAME: AptAnimation::relocatePointers
// Address: 0x005a4850
// This function adjusts all internal pointers by a given offset (baseOffset) after loading or copying an AptAnimation.
// It handles characters (shapes, text, fonts, sounds, bitmaps, etc.), exports, and imports.
// param_1: this pointer to AptAnimation
// param_2: baseOffset to add to all pointers (e.g., for relocation)
// param_3: unknown (passed to some sub-functions)
// param_4: resource manager pointer (used to load resources)

#include <cstdint>

// Forward declarations of helper functions (from other modules)
void FUN_0059bf00(); // assertion handler
void FUN_005b9560(int* data, int baseOffset, int param_3, int* something);
int FUN_005a0980();
int* FUN_005a2010(int** outPtr, int id);
void FUN_005a1f20();
void FUN_005a5650(int handle);
void (*DAT_0119cb14)(int handle);
void (*DAT_0119caf4)(void* ptr);
void (*DAT_0119caf8)(void* ptr, int size);
int (*DAT_0119cb60)(int resourceMgr, int index);
int (*DAT_0119cb44)(int resourceMgr, int index, int exportName);
int (*DAT_0119cb54)(int resourceMgr, int index);
int* DAT_0119a9c8; // global linked list head

// Assertion macro (simplified)
#define ASSERT(cond, msg, file, line) \
    if (!(cond)) { \
        /* call assertion handler */ \
        FUN_0059bf00(); \
    }

void AptAnimation::relocatePointers(int baseOffset, int param_3, int resourceManager)
{
    int* fsBase = *(int**)(__readfsdword(0x2c)); // FS segment base for assertion context

    // --- Adjust apCharacters array pointer ---
    ASSERT(*(uint32_t*)(this + 0x10) < 0xfffff, "(unsigned)(apCharacters) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x12);
    if (*(int*)(this + 0x10) != 0) {
        *(int*)(this + 0x10) += baseOffset;
    }

    // --- Adjust aExports array pointer ---
    ASSERT(*(uint32_t*)(this + 0x2c) < 0xfffff, "(unsigned)(aExports) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x15);
    if (*(int*)(this + 0x2c) != 0) {
        *(int*)(this + 0x2c) += baseOffset;
    }

    // --- Adjust each export's szName pointer ---
    int numExports = *(int*)(this + 0x28);
    for (int i = 0; i < numExports; i++) {
        int* exportEntry = *(int**)(this + 0x2c) + i * 2; // each export: [szName, zID]
        ASSERT((uint32_t)exportEntry[0] < 0xfffff, "(unsigned)(aExports[i].szName) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x18);
        if (exportEntry[0] != 0) {
            exportEntry[0] += baseOffset;
        }
    }

    // --- Process each character ---
    int numChars = *(int*)(this + 0x0c);
    for (int i = 0; i < numChars; i++) {
        int* charPtr = *(int**)(*(int*)(this + 0x10) + i * 4);
        ASSERT((uint32_t)charPtr < 0xfffff, "(unsigned)(apCharacters[i]) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x1d);
        if (charPtr != 0) {
            // Adjust character pointer itself (the pointer in the array)
            *(int**)(*(int*)(this + 0x10) + i * 4) = (int*)((int)charPtr + baseOffset);
        }

        int* adjustedChar = *(int**)(*(int*)(this + 0x10) + i * 4);
        if (adjustedChar != 0) {
            // Verify parent animation magic
            ASSERT(adjustedChar[1] == 0x9876543, "(unsigned int)apCharacters[i]->pParentAnim == 0x09876543", "..\\source\\Apt\\AptAnimation.cpp", 0x20);
            // Set parent to the apCharacters array address (seems like a backlink)
            adjustedChar[1] = *(int*)(this + 0x10);

            int type = adjustedChar[0];
            switch (type) {
                case 1: // Shape
                    ASSERT(adjustedChar[6] == i, "(int)apCharacters[i]->shape.zID == i", "..\\source\\Apt\\AptAnimation.cpp", 0x27);
                    adjustedChar[6] = (*DAT_0119cb60)(resourceManager, i);
                    break;

                case 2: // Text
                    ASSERT((uint32_t)adjustedChar[0xd] < 0xfffff, "(unsigned)(apCharacters[i]->text.szInitialText) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x2d);
                    if (adjustedChar[0xd] != 0) {
                        adjustedChar[0xd] += baseOffset;
                    }
                    ASSERT((uint32_t)adjustedChar[0xe] < 0xfffff, "(unsigned)(apCharacters[i]->text.szVariable) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x2e);
                    if (adjustedChar[0xe] != 0) {
                        adjustedChar[0xe] += baseOffset;
                    }
                    break;

                case 3: // Font
                    ASSERT((uint32_t)adjustedChar[2] < 0xfffff, "(unsigned)(apCharacters[i]->font.szName) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x33);
                    if (adjustedChar[2] != 0) {
                        adjustedChar[2] += baseOffset;
                    }
                    ASSERT((uint32_t)adjustedChar[4] < 0xfffff, "(unsigned)(apCharacters[i]->font.apGlyphs) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x34);
                    if (adjustedChar[4] != 0) {
                        adjustedChar[4] += baseOffset;
                    }
                    break;

                case 4: // (unused)
                    ASSERT(0, "0 && \"Flash Morph is disabled - remove it from your fla\"", "..\\source\\Apt\\AptAnimation.cpp", 0x39);
                    break;

                case 5: // (some complex type)
                    FUN_005b9560(adjustedChar + 2, baseOffset, param_3, (int*)(this + 0x30));
                    break;

                case 6: // Sound
                    ASSERT(adjustedChar[2] == i, "(int)apCharacters[i]->sound.zID == i", "..\\source\\Apt\\AptAnimation.cpp", 0x5a);
                    // Find export with matching zID
                    int exportName = 0;
                    if (numExports > 0) {
                        int* exportArray = *(int**)(this + 0x2c);
                        for (int j = 0; j < numExports; j++) {
                            if (exportArray[j * 2 + 1] == i) {
                                exportName = exportArray[j * 2];
                                break;
                            }
                        }
                    }
                    adjustedChar[2] = (*DAT_0119cb44)(resourceManager, i, exportName);
                    break;

                case 7: // Bitmap
                    ASSERT(adjustedChar[2] == i, "(int)apCharacters[i]->bitmap.zID == i", "..\\source\\Apt\\AptAnimation.cpp", 0x70);
                    adjustedChar[2] = (*DAT_0119cb54)(resourceManager, i);
                    break;

                case 8: // Morph (disabled)
                    ASSERT(0, "0 && \"Flash Morph is disabled - remove it from your fla\"", "..\\source\\Apt\\AptAnimation.cpp", 0x75);
                    break;

                case 9: // (some complex type, only first character allowed)
                    FUN_005b9560(adjustedChar + 2, baseOffset, param_3, (int*)(this + 0x30));
                    ASSERT(i == 0, "i == 0", "..\\source\\Apt\\AptAnimation.cpp", 0x7e);
                    break;

                case 10: // (unused)
                    ASSERT(0, "0 && \"Flash Morph is disabled - remove it from your fla\"", "..\\source\\Apt\\AptAnimation.cpp", 0x82);
                    break;

                case 0xc: // No action
                    break;

                default:
                    ASSERT(0, "0", "..\\source\\Apt\\AptAnimation.cpp", 0x94);
                    break;
            }
        }
    }

    // --- Adjust aImports array pointer ---
    ASSERT(*(uint32_t*)(this + 0x24) < 0xfffff, "(unsigned)(aImports) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x9a);
    if (*(int*)(this + 0x24) != 0) {
        *(int*)(this + 0x24) += baseOffset;
    }

    // --- Process each import ---
    int numImports = *(int*)(this + 0x20);
    for (int i = 0; i < numImports; i++) {
        int importOffset = i * 0x10; // each import is 0x10 bytes
        int* importBase = *(int**)(this + 0x24) + importOffset / 4;

        // Adjust szFile pointer
        ASSERT((uint32_t)importBase[0] < 0xfffff, "(unsigned)(aImports[i].szFile) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x9d);
        if (importBase[0] != 0) {
            importBase[0] += baseOffset;
        }

        // Adjust szName pointer
        ASSERT((uint32_t)importBase[1] < 0xfffff, "(unsigned)(aImports[i].szName) < 0xfffff", "..\\source\\Apt\\AptAnimation.cpp", 0x9e);
        if (importBase[1] != 0) {
            importBase[1] += baseOffset;
        }

        // Handle resource reference (likely a string or object)
        int resourceId = FUN_005a0980();
        int* newResource = FUN_005a2010(&resourceId, resourceId); // note: this seems odd, but matches decompiled
        int* oldResourcePtr = (int*)(importBase + 3); // offset 0xc in import

        if (newResource != oldResourcePtr) {
            // Decrement old resource refcount and possibly free
            int* oldResource = (int*)*oldResourcePtr;
            if (oldResource != 0) {
                (*oldResource)--;
                if (*oldResource == 0) {
                    int* resourceToFree = *oldResourcePtr;
                    if (resourceToFree != 0) {
                        FUN_005a1f20();
                        if (resourceToFree[8] == 3 || resourceToFree[8] == 4) {
                            FUN_005a5650(resourceToFree[9]);
                            (*DAT_0119cb14)(resourceToFree[0xb]);
                        }
                        int* innerPtr = (int*)resourceToFree[3];
                        if (innerPtr != resourceToFree + 4 && innerPtr != 0) {
                            (*DAT_0119caf4)(innerPtr);
                        }
                        (*DAT_0119caf8)(resourceToFree, 0x30);
                    }
                }
            }
            // Assign new resource
            *oldResourcePtr = (int)newResource;
            if (newResource != 0) {
                (*newResource)++;
            }
        }

        // Cleanup temporary resource reference
        if (newResource != 0) {
            (*newResource)--;
            if (*newResource == 0) {
                // Remove from global linked list
                int* head = *DAT_0119a9c8;
                int* prev = 0;
                while (head != 0 && (int*)head != newResource) {
                    prev = head;
                    head = (int*)head[1];
                }
                if (head != 0) {
                    if (prev == 0) {
                        *DAT_0119a9c8 = head[1];
                    } else {
                        prev[1] = head[1];
                    }
                    (*DAT_0119caf4)(head);
                }
                // Free resource
                if (newResource[8] == 3 || newResource[8] == 4) {
                    FUN_005a5650(newResource[9]);
                    (*DAT_0119cb14)(newResource[0xb]);
                }
                int* innerPtr = (int*)newResource[3];
                if (innerPtr != newResource + 4 && innerPtr != 0) {
                    (*DAT_0119caf4)(innerPtr);
                }
                (*DAT_0119caf8)(newResource, 0x30);
            }
        }
    }
}