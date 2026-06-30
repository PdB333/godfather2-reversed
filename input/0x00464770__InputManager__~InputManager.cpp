// FUNC_NAME: InputManager::~InputManager
// Function at 0x00464770: Destructor for InputManager (16 controller slots, each 0x168 bytes)
// Cleans up per-slot state, frees memory, releases references, calls shutdown

#include <cstdint>

// Forward declarations
void decRefCount(void* ptr);
void operatorDelete(void* ptr);
void someCleanup();
void anotherDelete(void* ptr);
void shutdown();

// Global pointer for linked list of slots or something
static int* g_pSlotList = nullptr;
// Global flag for some initialization state
static int g_shutdownFlag = 0;

// Slot structure (0x168 bytes = 90 ints)
struct ControllerSlot {
    // +0x00: pointer to something (maybe dynamic allocation)
    int* pSomething;
    // +0x04: another pointer
    int* pOther;
    // +0x08: reference count or some flag
    char field_0x08;
    // ... many fields
    // +0x47: unknown byte
    char byte_47;
    // +0x5f: unknown byte
    char byte_5f;
    // +0x70: unknown array (accessed as int[48]? Starting at offset 0x1c ints from slot base)
    int unknownArray[48]; // Actually zeros 48 ints at offsets 0x1c, 0x1d, ... as ints
};

// The main object
struct InputManager {
    // +0x00: vtable pointer
    int* vtable;
    // +0x04: some pointer
    int* field_0x04;
    // +0x08: ...
    // +0x0c: another vtable?
    int* field_0x0c;
    // ... many fields up to offset 0x5c * 4 = 0x170
    // Then 16 controller slots of 0x168 bytes each, total 0x1680 bytes
    ControllerSlot slots[16];
    // After slots, at offset 0x1690 ( = 0x5a4 ints), a pointer to another object
    void* pPostSlotObject;
};

// Constructor (not shown) sets up vtable etc.

// Destructor
void InputManager::_destruct_00464770(InputManager* thisObj) {
    int* piVar1;
    uint uVar2;
    int* puVar3;
    int iVar4;
    int* piVar5;
    uint local_4;

    // Set vtable pointer
    thisObj->vtable = &PTR_FUN_00e31e6c;
    thisObj->field_0x0c = &PTR_LAB_00e31e7c;

    // Decrement reference counts on global objects
    decRefCount(&DAT_012069c4);
    decRefCount(&DAT_012069b4);

    local_4 = 0;
    piVar5 = &thisObj->slots[0].pSomething; // +0x5c ints from start (since slots start at offset 0x5c*4)

    do {
        uVar2 = local_4 & 0xff;
        // Zero some flags per slot
        *(char*)((int)thisObj + uVar2 * 0x168 + 0x47) = 0;
        *(char*)((int)thisObj + uVar2 * 0x168 + 0x5f) = 0;
        thisObj->slots[uVar2].pOther = 0; // Actually param_1[uVar2 * 0x5a + 0x5a] = 0; offset 0x5a ints = 0x168 bytes
        puVar3 = &thisObj->slots[uVar2].unknownArray[0]; // param_1 + uVar2*0x5a + 0x1c as int*
        iVar4 = 0x10;
        do {
            puVar3[-2] = 0;
            puVar3[-1] = 0;
            *puVar3 = 0;
            puVar3 = puVar3 + 4;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        // Free the pointer in slot->pOther (piVar5[-1] is &thisObj->slots[uVar2].pOther)
        piVar1 = (int*)piVar5[-1];
        if (piVar1 != (int*)0x0) {
            if (*piVar1 != 0) {
                operatorDelete(*piVar1);
            }
            operatorDelete(piVar1);
        }
        // Free the pointer in slot->pSomething (piVar5[0])
        iVar4 = *piVar5;
        piVar5[-1] = 0;
        if (iVar4 != 0) {
            someCleanup();
            operatorDelete(iVar4);
        }
        // Adjust linked list? piVar5[-0x58] is at int index 0x5c-0x58=0x4, so field_0x04
        iVar4 = piVar5[-0x58];
        *piVar5 = 0;
        piVar1 = g_pSlotList;
        while (g_pSlotList = piVar1, iVar4 != 0) {
            *(char*)(piVar5[piVar5[-0x58] + -0x58] + 8) = *(char*)(piVar5[piVar5[-0x58] + -0x58] + 8) + -1;
            piVar5[piVar5[-0x58] + -0x57] = 0;
            piVar5[-0x58] = piVar5[-0x58] + -1;
            piVar1 = g_pSlotList;
            iVar4 = piVar5[-0x58];
        }
        local_4 = local_4 + 1;
        piVar5 = piVar5 + 0x5a; // Move to next slot (0x5a ints = 0x168 bytes)
    } while (local_4 < 0x10);

    if (piVar1 != (int*)0x0) {
        if (*piVar1 != 0) {
            anotherDelete(*piVar1);
        }
        operatorDelete(piVar1);
    }
    g_pSlotList = (int*)0x0;

    // Call virtual function on post-slot object
    (*(code**)(*(int*)thisObj->pPostSlotObject + 0xc))();

    // Change vtable pointer (maybe to destructor helper)
    thisObj->field_0x0c = &PTR_LAB_00e31e80;
    g_shutdownFlag = 0;
    shutdown();
    return;
}