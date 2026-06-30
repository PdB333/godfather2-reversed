// FUNC_NAME: Animation::processFrameData
// Address: 0x00580230
// Role: Process animation keyframe data, branching based on character type (<10 is player, else NPC)
// Offsets:
//   this+0x00: base resource pointer
//   this+0x04: character data pointer
//   this+0x08: float parameter (cast to int for callees)
//   this+0x0C: entry count
//   characterData+0x04: type ID (byte)
//   characterData+0x24: name hash table (player)
//   characterData+0x2C: name hash table (NPC)
//   baseResource+0x34: buffer pointer
//   baseResource+0x38: cached animation data pointer
//   nameTableEntry+0x00: flags (0 = type A, non-zero = type B)
//   nameTableEntry+0x0C: short used for activation test (type A)
//   nameTableEntry+0x24: short used for activation test (type B)

#include <cstdint>

typedef unsigned int uint;

// Forward declarations
uint FUN_0056ef10(int param);                          // allocateAnimationData?
void FUN_0057f8a0(int param);                          // setupAnimationTypeA
void FUN_0057f9d0(uint baseAddr);                      // processDeltaTypeA
void FUN_005800a0();                                    // processOtherTypeA
void FUN_00581080(int param);                          // setupAnimationTypeB
void FUN_00581220(uint baseAddr);                      // processDeltaTypeB
void FUN_00581370();                                    // processOtherTypeB

uint Animation::processFrameData()
{
    // this in EAX: layout as above
    int* baseResource = (int*)this->field_0;
    int* charData = (int*)this->field_4;
    float floatParam = this->field_8;
    int count = this->field_C;

    // Determine which name hash table to use based on type ID
    int* nameTable;
    if ((*(uint*)(charData + 1) & 0xFF) < 10) {
        nameTable = *(int**)(charData + 0x24); // +0x24
    } else {
        nameTable = *(int**)(charData + 0x2C); // +0x2C
    }

    // Initialize cached animation data if needed
    int cachedData = *(int*)(baseResource + 0x38); // +0x38
    if (cachedData == 0) {
        cachedData = FUN_0056ef10((int)charData[3]); // +0x0C? Actually param is iVar5 which is this->field_C
        // Update struct: baseResource[0x38] = cachedData
        baseResource = (int*)this->field_0; // re-fetch because FUN_0056ef10 might modify something? Actually the code re-reads *in_EAX after call
        // In decompiled: iVar4 = *in_EAX; reset
        baseResource = (int*)this->field_0; // assume it's correct
        *(int*)(baseResource + 0x38) = cachedData;
    }

    uint baseAddr = cachedData + 0x10; // +0x10 offset
    char* trackTypes = (char*)(*(int*)(baseResource + 0x34) + 0x14); // +0x34 -> +0x14

    if (*nameTable == 0) {
        // Type A processing
        if (*(short*)(nameTable + 3) != 0) { // +0x0C (3 ints = 12 bytes, cast to short)
            FUN_00581080((int)floatParam); // setup type A
            for (int i = 0; i < count; i++) {
                if (*trackTypes == '\x02') {
                    FUN_00581220(baseAddr);
                } else if (*trackTypes != '\0') {
                    FUN_00581370();
                }
                baseAddr += 0x20;
                trackTypes++;
            }
            return 1; // success (CONCAT31(extraout,1))
        }
    } else {
        // Type B processing
        int* charData2 = (int*)this->field_4;
        uint nameTable2;
        if ((*(uint*)(charData2 + 1) & 0xFF) < 10) {
            nameTable2 = *(uint*)(charData2 + 0x24);
        } else {
            nameTable2 = *(uint*)(charData2 + 0x2C);
        }
        if (*(short*)(nameTable2 + 0x24) != 0) { // +0x24 offset in nameTable entry
            FUN_0057f8a0((int)floatParam); // setup type B
            for (int i = 0; i < count; i++) {
                if (*trackTypes == '\x02') {
                    FUN_0057f9d0(baseAddr);
                } else if (*trackTypes != '\0') {
                    FUN_005800a0();
                }
                baseAddr += 0x20;
                count--; // Note: loop counter is decremented inside loop? Actually decompiled does iVar5 = iVar5 + -1 and continues while 0 < iVar5
                // The original uses iVar5-- and checks before call, but for simplicity use for loop.
                // We'll replicate using a do-while pattern as in decompiled.
            }
            // The decompiled returns after the loop, so we break out and return 1
            return 1;
        }
    }
    // If no branch taken, return lower byte of nameTable? Actually uVar2 & 0xffffff00
    // uVar2 is from the re-evaluated nameTable (the pointer itself) masked to high 24 bits
    // This seems like an error or default
    uint uVar2;
    if ((*(uint*)(charData + 1) & 0xFF) < 10) {
        uVar2 = *(uint*)(charData + 0x24);
    } else {
        uVar2 = *(uint*)(charData + 0x2C);
    }
    return uVar2 & 0xFFFFFF00;
}