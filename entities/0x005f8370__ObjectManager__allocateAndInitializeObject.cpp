// FUNC_NAME: ObjectManager::allocateAndInitializeObject
// Address: 0x005f8370
// This function appears to allocate an object from a memory pool and perform initialization or state checks depending on input parameters.
// It likely belongs to a central object/manager class using EA's EARS engine memory pool.
// The function returns a pointer to the allocated block, or nullptr on failure.

#include <cstdint>

// Forward declarations for called functions (addresses provided)
bool CheckCondition(int param_1, int param_2, uint param_3); // 0x005f8190
bool CheckSlotOccupied(uint index);                            // 0x005fcd80
int* FindOrCreateObject(uint param_3);                        // 0x005f8300
void InitObject(int base, int obj, uint param_5);             // 0x005f8260
uint GetTimestamp();                                           // 0x005f6430

// External global memory manager
extern MemoryManager* gMemoryManager; // DAT_01223520

// Memory pool descriptor (offset 0x30 from gMemoryManager)
struct MemoryPool {
    int freeCount;       // +0x14
    int minFreeCount;    // +0x18
    void* firstFree;     // +0x08
    int unknown;         // +0x1c (function pointer?)
    int data1;           // +0x0c
    int data2;           // +0x10
};

// The calling object (this) has fields at offsets:
// +0x20: flags (byte)
// +0x24: base pointer for object array
// +0x30: allocated block pointer
// +0x34: timestamp
// +0x38: status flags
// +0x3c: self pointer (for reference)
// +0x4c: ??? (not used directly here)

#define FLAG_BIT_1    0x02
#define FLAG_BITS_2_3 0x0C
#define STATUS_ALLOCATED   0x01
#define STATUS_PENDING     0x02
#define STATUS_FAILED      0x44

undefined4* FUN_005f8370(int param_1, int param_2, undefined4 param_3, int param_4, undefined4 param_5)
{
    bool bVar1;        // result from loop
    bool bVar2;        // temporary
    int iVar3;         // condition result
    int iVar4;         // index or temp
    undefined4 uVar5;  // timestamp or other
    undefined4* puVar6; // allocated block pointer
    uint uVar7;        // loop counter

    if (param_2 == param_4) {
        // Case 1: same slot indices
        if ((*(int*)(param_2 + 0x40) != 0) && ((*(byte*)(param_1 + 0x20) & FLAG_BIT_1) == 0)) {
            iVar3 = CheckCondition(param_1, param_2, param_3); // FUN_005f8190
            bVar1 = false;
            if ((iVar3 != 2) &&
                (((*(byte*)(param_1 + 0x20) & FLAG_BITS_2_3) == 0) &&
                 (*(short*)(param_2 + 0x3c) != 0))) {
                uVar7 = 0;
                bVar2 = false;
                do {
                    bVar1 = bVar2;
                    if (bVar1) break;
                    iVar4 = CheckSlotOccupied(uVar7); // FUN_005fcd80
                    if (iVar4 != 0) {
                        bVar1 = true;
                    }
                    uVar7 = uVar7 + 1;
                    bVar2 = bVar1;
                } while (uVar7 < *(ushort*)(param_2 + 0x3c));
            }

            if (iVar3 == 1) {
                if (bVar1) {
                    // Some condition met, set self-reference
                    *(int*)(param_1 + 0x3c) = param_1;
                } else {
                    iVar3 = FindOrCreateObject(param_3); // FUN_005f8300
                    if (iVar3 != 0) {
                        InitObject(*(int*)(param_1 + 0x24) + (uint)*(byte*)(iVar3 + 0x0b) * 0x0c,
                                   iVar3, param_5); // FUN_005f8260
                        uVar5 = GetTimestamp(); // FUN_005f6430
                        *(uint*)(param_1 + 0x38) |= STATUS_ALLOCATED;
                        *(undefined4*)(param_1 + 0x34) = uVar5;
                    }
                }
            } else {
                if (iVar3 == 0) goto LAB_005f84a0;
                if ((iVar3 == 2) && ((*(byte*)(param_1 + 0x20) & 0x08) != 0)) goto LAB_005f84a2;
            }
        }
    } else {
        // Case 2: different slot indices
        if ((*(byte*)(param_1 + 0x20) & FLAG_BITS_2_3) == 0) {
            uVar7 = 0;
            bVar1 = false;
            if (*(short*)(param_2 + 0x3c) != 0) {
                do {
                    if (bVar1) goto LAB_005f84a6;
                    iVar3 = CheckSlotOccupied(uVar7); // FUN_005fcd80
                    if (iVar3 != 0) {
                        bVar1 = true;
                    }
                    uVar7 = uVar7 + 1;
                } while (uVar7 < *(ushort*)(param_2 + 0x3c));
LAB_005f84a0:
                if (bVar1) goto LAB_005f84a6;
            }
        }
LAB_005f84a2:
        *(uint*)(param_1 + 0x38) |= STATUS_PENDING;
    }

LAB_005f84a6:
    // Memory pool allocation
    iVar4 = gMemoryManager;
    iVar3 = *(int*)(gMemoryManager + 0x30); // MemoryPool*

    if (*(int*)(iVar3 + 0x14) != 0) { // freeCount > 0
        puVar6 = *(undefined4**)(iVar3 + 8); // firstFree
        if (puVar6 == nullptr) {
            if (*(int**)(iVar3 + 0x1c) == nullptr) goto LAB_005f850d;
            // Use custom allocation function from pool
            puVar6 = (undefined4*)(**(code**)(**(int**)(iVar3 + 0x1c) + 4))
                                  (*(undefined4*)(iVar3 + 0x0c), *(undefined4*)(iVar3 + 0x10));
        } else {
            uVar5 = *puVar6; // next free block
            *(int*)(iVar3 + 0x14) -= 1; // decrement freeCount
            *(undefined4*)(iVar3 + 8) = uVar5; // update firstFree
            if (*(uint*)(iVar3 + 0x14) < *(uint*)(iVar3 + 0x18)) {
                *(uint*)(iVar3 + 0x18) = *(uint*)(iVar3 + 0x14); // track minimum
            }
        }
        if (puVar6 != nullptr) {
            uVar5 = *(undefined4*)(gMemoryManager + 0x1c); // some global or pool data
            puVar6[2] = (undefined4)(puVar6 + 3); // self-pointer or offset
            puVar6[1] = uVar5; // copy data
            *puVar6 = 0; // clear first word
            *(undefined4**)(param_1 + 0x30) = puVar6; // store handle
            return puVar6;
        }
    }

LAB_005f850d:
    *(uint*)(param_1 + 0x38) |= STATUS_FAILED;
    return nullptr;
}