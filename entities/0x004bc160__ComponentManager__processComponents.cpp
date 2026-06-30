// FUNC_NAME: ComponentManager::processComponents
#include <cstddef>

// Structure for an array descriptor used in the game (size 8 bytes)
// +0x00: elements - pointer to the start of the array
// +0x04: count    - number of elements in the array
struct ComponentArrayDescriptor {
    void* elements;  // int* in original, but used as byte pointer for stride
    int count;
};

// Forward declarations of called functions
void __cdecl preProcessArray(int size, void* descriptorPtr);  // FUN_0064b810 – likely memory/validation setup
void __thiscall processElement(void* thisPtr, void* element); // FUN_004bb7d0 – per-element handler

void __thiscall ComponentManager::processComponents(ComponentArrayDescriptor* desc) {
    int* elemPtr = (int*)desc->elements;  // reinterpreted as int pointer for original arithmetic
    int count = desc->count;

    // Preprocess: unknown initialization/caching with element size 0x20 and descriptor address
    preProcessArray(0x20, &desc);

    if (count != 0) {
        int i = 0;
        do {
            // Calculate address of each element (stride 0x20 = 32 bytes)
            int elementAddr = (int)elemPtr + i;  // *piVar1 + iVar2; i is byte offset
            processElement(this, (void*)elementAddr);
            i += 0x20;
            count--;
        } while (count != 0);
    }
}