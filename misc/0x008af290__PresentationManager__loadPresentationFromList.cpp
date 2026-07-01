// FUNC_NAME: PresentationManager::loadPresentationFromList
// Function address: 0x008af290
// Role: Iterates an internal list of presentation source data (likely from resource files) and creates a Presentation object. Supports loading a specific presentation by ID or all (if ID == -1). Copies data into a temporary array, allocates a new Presentation (0x50 bytes), and registers it.

#include <cstdint>

// External function pointers for list iteration
extern uint32_t* PTR_FUN_00e35c28; // returns pointer to current element data
extern void (*_UNK_00e35c2c)(); // advances iterator to next element

// Global state
extern int32_t DAT_01205a20; // global flag

// Forward declarations of helper functions
int32_t FUN_00481610(); // checks some subsystem readiness
void FUN_004bca00(int32_t newCapacity); // reallocate/grow temporary array
void FUN_00498500(uint32_t* src); // copies string/resource handle (size? )
int32_t FUN_009c8e50(int32_t size); // allocate memory (returns pointer)
int32_t FUN_008aef70(int32_t managerPtr); // Presentation constructor (this is manager)
void FUN_008accf0(int32_t* arrayPtr); // destroy temporary array
void FUN_0064ef60(int32_t presentationPtr); // register presentation (add to active list)
void FUN_004bc280(); // finalize or commit

void __thiscall PresentationManager::loadPresentationFromList(int32_t thisPtr, int32_t presentationId) {
    int32_t iVar1;
    int32_t iVar2;
    uint32_t* currentElem;
    int32_t capacity;
    uint32_t* dest;
    uint32_t resultHandle;
    int8_t loadSuccess; // 0 = success? actually set to 1 on failure
    int32_t countdown; // initial 0x39 (57)
    int32_t listHead; // from this+0x60
    int32_t tempArray; // pointer to growing array of elements (size 0x34 each)
    int32_t elementCount; // number of elements copied
    int32_t tempCapacity; // capacity of tempArray

    iVar1 = FUN_00481610();
    if (iVar1 != 0) {
        iVar1 = 0;
        if ((DAT_01205a20 != 0) && (listHead = *(int32_t*)(thisPtr + 0x60), listHead != 0)) {
            capacity = 0;
            loadSuccess = 0;
            tempArray = 0;
            elementCount = 0;
            tempCapacity = 0;
            countdown = 0x39; // 57, max elements to process

            // If first node has no data at offset 8, treat as empty
            if (*(int32_t*)(listHead + 8) == 0) {
                listHead = 0;
            }

            if (presentationId == -1) {
                // Load all presentations
                goto copyLoop;
            }

            // Search for specific requested ID
            while (listHead != 0) {
                iVar2 = (*(code *)PTR_FUN_00e35c28)();
                if (*(int32_t*)(iVar2 + 8) == presentationId) {
                    goto copyLoop;
                }
                (*_UNK_00e35c2c)();
            }

            // Not found - go to finalize with failure
            goto finalize;

            // Copy elements from iterator into tempArray
            do {
                if (listHead == 0) goto finalize;
                if (countdown == 0) {
                    // Still some elements but count limit reached – take last element's handle and exit
                    if (listHead != 0) {
                        iVar1 = (*(code *)PTR_FUN_00e35c28)();
                        resultHandle = *(uint32_t*)(iVar1 + 8);
                        goto createPresentation;
                    }
                    goto finalize;
                }

                currentElem = (uint32_t*)(*(code *)PTR_FUN_00e35c28)();

                // Grow tempArray if needed
                if (capacity == iVar1) {
                    capacity = iVar1 * 2;
                    if (iVar1 == 0) {
                        capacity = 1;
                    }
                    FUN_004bca00(capacity); // reallocate with new capacity
                    iVar1 = tempCapacity; // update iVar1 to current capacity (maybe from realloc)
                    capacity = elementCount;
                }

                dest = (uint32_t*)(capacity * 0x34 + tempArray);
                capacity = capacity + 1;
                elementCount = capacity;

                if (dest != nullptr) {
                    // Copy first three dwords (likely header/metadata)
                    *dest = *currentElem;
                    dest[1] = currentElem[1];
                    dest[2] = currentElem[2];
                    // Copy three resource/handle slots (strings? objects?) at offsets +3, +6, +9
                    FUN_00498500(currentElem + 3);
                    FUN_00498500(currentElem + 6);
                    FUN_00498500(currentElem + 9);
                    dest[0xc] = currentElem[0xc];
                }
                (*_UNK_00e35c2c)(); // advance iterator
                countdown = countdown - 1;
            } while (true);

finalize:
            loadSuccess = 1;
            resultHandle = 0xFFFFFFFF; // invalid handle

createPresentation:
            // Allocate new Presentation object (size 0x50)
            iVar1 = FUN_009c8e50(0x50);
            if (iVar1 == 0) {
                iVar1 = 0;
            } else {
                iVar1 = FUN_008aef70(thisPtr); // Initialize with manager
            }
            *(uint32_t*)(iVar1 + 0x38) = resultHandle; // +0x38: presentation ID/handle
            *(int8_t*)(iVar1 + 0x3c) = loadSuccess;   // +0x3c: load status flag
            FUN_008accf0(&tempArray); // free temporary array
            FUN_0064ef60(iVar1);      // register the new presentation
            FUN_004bc280();           // finalize/commit batch
        }
    }
    return;
}