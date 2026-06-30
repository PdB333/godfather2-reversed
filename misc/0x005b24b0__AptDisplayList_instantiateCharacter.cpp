// Xbox PDB: AptDisplayList::instantiateCharacter
// FUNC_NAME: AptDisplayList::appendCharacterInstance
// Address: 0x005b24b0
// Role: Creates or finds a character instance handle (CIH) entry in the Apt display list,
// assigning geometry data, animation data, and coordinates. Handles different character types
// (5 = font, 2 = image, 1 = fill style) and manages a pool of new instances.

#include <cstdint>

// Forward declarations for functions called (mapped to guessed names based on context)
uint32_t FUN_005b1f80(uint32_t param_1, uint32_t param_2, uint8_t* param_4, uint32_t* param_5, uint32_t** param_6); // AptDisplayList::findOrCreateCIH?
void FUN_005b3030(); // AptDisplayList::handleUnknownCase?
void FUN_005a4560(); // FontConstructor?
uint32_t FUN_005b1f30(); // ImageConstructor?
uint32_t FUN_0059bf00(const char* msg, const char* file, int line, int level); // DebugAssert?
uint32_t FUN_005a19c0(); // AptDisplayList::getGlobalRenderState?
uint32_t FUN_005b2240(uint32_t param_1, uint32_t param_2, int param_3); // AptDisplayList::createNewCIH?
void FUN_005b2380(); // AptDisplayList::cleanupOldCIH?
void FUN_005b22e0(); // AptDisplayList::updateCIHMapping?
uint32_t FUN_0059cae0(); // Allocator::allocateCharacterData?
void FUN_005b8920(uint32_t param_1); // AptDisplayList::setCharacterDataFlags?
uint32_t FUN_005a3f20(uint32_t param_1, uint32_t param_2); // AptDisplayList::linkCharacterToLayer?
void FUN_005ba7d0(uint32_t param_1, uint32_t param_2, uint32_t param_3); // AptDisplayList::setupCharacterRender?
void FUN_0059c690(); // AptDisplayList::notifyDataChange?
uint32_t FUN_0059c810(); // AptDisplayList::getCurrentPlayhead?
uint32_t FUN_005aea60(uint32_t* param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5); // ResourceManager::loadTexture?
void FUN_005ad5b0(uint32_t* param_1, uint32_t param_2, uint32_t param_3, uint32_t* param_4, uint32_t param_5, uint32_t param_6); // ResourceManager::scheduleTextureLoad?
void FUN_005b49f0(uint32_t* param_1); // AptDisplayList::updateCharacterBounds?
void FUN_0059c230(uint32_t* param_1); // AptDisplayList::advanceAnimation?

// Global data references
extern uint32_t DAT_0119caf0; // Allocator function pointer?
extern uint32_t DAT_0119cbbc; // Some static resource ID?
extern uint32_t DAT_0119a9cc; // Global display list state?
extern uint32_t DAT_01129012;
extern uint32_t DAT_01129013;
extern uint32_t DAT_01129014;
extern uint32_t DAT_01129015;
extern uint32_t DAT_0103aee0; // Virtual function table for resource types?

struct CharacterInstanceHandle {
    uint32_t* vtable; // +0x00
    uint32_t flags;   // +0x04
    uint32_t tag;     // +0x08
    uint32_t id;      // +0x0C
    uint32_t field10; // +0x10
    uint32_t field14; // +0x14
    uint32_t dataPtr; // +0x18
    uint32_t font;    // +0x1C
    uint32_t image;   // +0x20
    uint32_t fill;    // +0x24
    // ... more fields
};

void FUN_005b24b0(uint32_t* param_1, uint32_t param_2, int* param_3, uint8_t* param_4, 
                  uint32_t* param_5, int param_6, uint32_t param_7, 
                  uint32_t* param_8, uint32_t* param_9) {
    int iVar6;
    uint32_t uVar4;
    uint32_t uVar7;
    uint32_t* puVar8;
    uint32_t* local_34;
    uint32_t* local_30;
    uint32_t local_2c[1];
    const char* errorMsg;
    const char* errorFile;
    int errorLine;
    int errorLevel;
    uint32_t* errorData;
    uint32_t* puVar11;
    int iVar10;
    bool bVar12;
    uint8_t* pbVar5;
    uint8_t* pbVar9;
    uint8_t bVar1;

    // Assert pParent not null
    if (param_5 == nullptr) {
        errorMsg = "pParent";
        errorFile = "..\\source\\Apt\\AptDisplayList.cpp";
        errorLine = 0x79;
        errorLevel = 2;
        errorData = &DAT_01129012;
        if (DAT_01129012 != 0) {
            // Debug break logic...
            return;
        }
    }

    local_34 = nullptr;
    FUN_005b1f80(*param_1, param_2, param_4, local_2c, &local_30);
    
    if (local_30 != nullptr) {
        if (param_6 == 0) {
            // Check if CIH is a font (bit 15 of flags)
            if ((local_30[0] >> 0x0F) & 1) {
                // Compare name strings for font matching
                if (param_4 != nullptr) {
                    pbVar9 = (uint8_t*)*(uint32_t*)(local_30[0x0D] + 0x0C);
                    pbVar5 = param_4;
                    do {
                        bVar1 = *pbVar5;
                        if (bVar1 != *pbVar9) {
                            iVar10 = (*pbVar5 < *pbVar9) ? -1 : 1;
                            break;
                        }
                        if (bVar1 == 0) break;
                        bVar1 = pbVar5[1];
                        if (bVar1 != pbVar9[1]) {
                            iVar10 = (bVar1 < pbVar9[1]) ? -1 : 1;
                            break;
                        }
                        pbVar5 += 2;
                        pbVar9 += 2;
                    } while (bVar1 != 0);
                    
                    if (iVar10 == 0) {
                        local_30[0] |= 0x00008000; // Mark as font match
                        local_34 = local_30;
                    }
                }
            } else {
                local_34 = local_30;
                param_6 = 0;
                goto LAB_005b2924;
            }
        } else {
            FUN_005b3030();
        }
    }

    iVar6 = *param_3;
    iVar10 = 0;
    puVar11 = nullptr;
    param_6 = 1;

    // Allocate based on character type
    if (iVar6 == 5) { // Font type
        puVar11 = (uint32_t*)(*DAT_0119caf0)(0x24, 0);
        if (puVar11 != nullptr) {
            FUN_005a4560();
        }
        puVar11[5] |= 0x01000000;
        iVar10 = 0x0D;
        puVar11[4] = 0xFFFFFFFF;
    } else if (iVar6 == 2) { // Image type
        iVar10 = (*DAT_0119caf0)(0x5C, 0);
        if (iVar10 != 0) {
            puVar11 = (uint32_t*)FUN_005b1f30();
        }
        puVar11[2] = (uint32_t)param_3;
        puVar11[9] = param_3[8];
        puVar11[0x13] = ((float)param_3[4] - (float)param_3[2]) + (float)param_3[2];
        iVar10 = 0x0F;
        puVar11[0x14] = ((float)param_3[5] - (float)param_3[3]) + (float)param_3[3];
    } else if (iVar6 == 1) { // Fill style type
        puVar11 = (uint32_t*)(*DAT_0119caf0)(0x10, 0);
        if (puVar11 != nullptr) {
            puVar11[1] = 0;
            puVar11[2] = 0;
            puVar11[3] = 0;
            puVar11[0] = 0xFFFFFFFF;
            iVar10 = 0x0C;
        } else {
            iVar10 = 0x0C;
        }
    } else {
        // Unknown type - assert
        errorMsg = "0";
        errorFile = "..\\source\\Apt\\AptDisplayList.cpp";
        errorLine = 0xDA;
        errorLevel = 2;
        errorData = &DAT_01129013;
        FUN_0059bf00();
    }

    uVar4 = *param_5 & 0x7FFF;
    if (((*param_5 & 0x8000) == 0) || ((uVar4 != 0x0D) && (uVar4 != 0x12))) {
        puVar11[1] = 0xFFFFFFFF;
    } else {
        iVar6 = FUN_005a19c0();
        puVar11[1] = *(uint32_t*)(iVar6 + 0x10);
    }

    if (local_34 == nullptr) {
        local_34 = (uint32_t*)FUN_005b2240(*param_1, param_2, iVar10);
    } else {
        if (param_2 != local_34[0x0C]) {
            FUN_005b2380();
            FUN_005b22e0();
        }
        local_34[0x16] = (uint32_t)puVar11;
    }

    if (param_4 != nullptr) {
        // Allocate and set character data
        iVar6 = (*DAT_0119caf0)(0x24, 0);
        if (iVar6 == 0) {
            uVar4 = 0;
        } else {
            uVar4 = FUN_0059cae0();
        }
        FUN_005b8920(uVar4);
        
        puVar8 = (uint32_t*)local_34[0x0D];
        if (puVar8 != nullptr) {
            (*(void (**)(uint32_t*))(&DAT_0103aee0 + (*puVar8 & 0x7FFF) * 4))(puVar8);
        }
        local_34[0x0D] = uVar4;
        FUN_0059c690();
        
        puVar8 = local_34;
        iVar6 = FUN_005a3f20(uVar4, (uint32_t)local_34);
        FUN_005ba7d0(*(uint32_t*)(iVar6 + 0x0C), uVar4, (uint32_t)puVar8);
    }

    if (iVar10 == 0x0D) {
        // Add to new instances pool
        if (*(int*)(DAT_0119a9cc + 0x1C08) > 0x1FF) {
            errorMsg = "gpPool->nNewInsts < ((int)(sizeof(gpPool->apNewInsts) / sizeof(gpPool->apNewInsts[0])))";
            errorFile = "..\\source\\Apt\\AptDisplayList.cpp";
            errorLine = 0x108;
            errorLevel = 2;
            errorData = &DAT_01129014;
            FUN_0059bf00();
        }
        *(uint32_t**)(DAT_0119a9cc + 0x1408 + *(int*)(DAT_0119a9cc + 0x1C08) * 4) = local_34;
        (*(int*)(DAT_0119a9cc + 0x1C08))++;
        FUN_0059c690();
    } else if (iVar10 == 0x0F) {
        // Handle image playhead and texture loading
        iVar10 = FUN_0059c810();
        if (**(char**)(*(int*)(iVar10 + 8) + 0x38) != '\0') {
            puVar8 = *(uint32_t**)(iVar10 + 0x1C);
            if (puVar8 != nullptr) {
                (*(void (**)(uint32_t*))(&DAT_0103aee0 + (*puVar8 & 0x7FFF) * 4))(puVar8);
            }
            iVar6 = (*DAT_0119caf0)(0x24, 0);
            if (iVar6 == 0) {
                uVar7 = 0;
            } else {
                uVar7 = FUN_0059cae0();
            }
            *(uint32_t*)(iVar10 + 0x1C) = uVar7;
            FUN_0059c690();
            FUN_005b8920(*(uint32_t*)(iVar10 + 0x1C));
            
            puVar8 = (uint32_t*)FUN_005aea60(param_5, 0, *(uint32_t*)(*(int*)(iVar10 + 0x1C) + 0x0C), 1, 1);
            if (!((*puVar8 >> 0x0F) & 1)) {
                FUN_005ad5b0(param_5, 0, *(uint32_t*)(*(int*)(iVar10 + 0x1C) + 0x0C), &DAT_0119cbbc, 1, 1);
            }
        }
        FUN_005b49f0(param_5);
    }

LAB_005b2924:
    if (local_34 == nullptr) {
        errorMsg = "pCurCIH";
        errorFile = "..\\source\\Apt\\AptDisplayList.cpp";
        errorLine = 0x128;
        errorLevel = 2;
        errorData = &DAT_01129015;
        if (DAT_01129015 != 0) {
            // Debug break logic...
            return;
        }
    }

    if (param_5 != &DAT_0119cbbc) {
        uVar4 = *param_5 & 0x7FFF;
        if ((uVar4 != 0x19) && 
            (!((*param_5 >> 0x0F) & 1) || 
            ((uVar4 != 0x0B && uVar4 != 0x18) && uVar4 != 0x17))) {
            FUN_0059c230(param_5);
        }
    }

    // Set the parent (callback?) for the CIH
    puVar8 = (uint32_t*)local_34[0x15];
    if (puVar8 != nullptr) {
        (*(void (**)(uint32_t*))(&DAT_0103aee0 + (*puVar8 & 0x7FFF) * 4))(puVar8);
    }
    local_34[0x15] = (uint32_t)param_5;

    // Set transform and data
    *(int**)(local_34[0x16] + 8) = param_3;
    *(uint32_t*)local_34[0x16] = param_7;
    
    *param_8 = (uint32_t)local_34;
    *param_9 = param_6;

    return;
}