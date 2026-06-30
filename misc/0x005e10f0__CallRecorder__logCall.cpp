// FUNC_NAME: CallRecorder::logCall
// Function at 0x005e10f0
// This function is part of a call recording/event logging system.
// It allocates a 24-byte block (size 0x18) and fills it with:
// - a value from a local variable (possibly a previous link or flag),
// - the return address (to identify the caller),
// - the second parameter passed to this function,
// - two DWORDs from the object pointed to by the ESI register (implicitly passed by caller),
// - two zero bytes at offsets 0x14 and 0x15 (end of structure).

#include <cstdint>

void __thiscall CallRecorder::logCall(uint32_t param_2) {
    // this+0x04: pointer to allocator function (size_t, void* oldBuffer -> void* newBlock)
    // this+0x08: pointer to free list head (or NULL if empty)
    // ESI: assumed to hold pointer to some object (e.g., a game entity) when this function is called

    // Retrieve allocator function and free list pointer
    void* allocFunc = *(void**)((uint8_t*)this + 4);
    void*& freeHead = *(void**)((uint8_t*)this + 8);

    // Temporary stack buffer (used only when free list is empty)
    uint32_t tempBuffer[3] = {0, 0, 0};
    void* oldBuffer = (freeHead != nullptr) ? freeHead : tempBuffer;

    // Allocate a 24-byte block using the stored allocator
    uint32_t* newBlock = (uint32_t*)((void* (__stdcall*)(uint32_t, void*))allocFunc)(0x18, oldBuffer);

    if (newBlock != nullptr) {
        // Fill record with data from caller context
        // tempBuffer[2] is the third local (local_4); if freeHead was null it is 0,
        // otherwise it contains undefined data (the compiler did not initialize it).
        newBlock[0] = tempBuffer[2];               // offset 0x00: some value (e.g., previous block pointer?)
        newBlock[1] = (uint32_t)_ReturnAddress();   // offset 0x04: return address (caller's instruction)
        newBlock[2] = param_2;                      // offset 0x08: second parameter
        newBlock[3] = *(uint32_t*)__readesi();      // offset 0x0C: first DWORD of object pointed by ESI
        newBlock[4] = *(((uint32_t*)__readesi()) + 1); // offset 0x10: second DWORD of that object

        // Zero two bytes at the end (reason unknown, possibly flags or terminator)
        ((uint8_t*)newBlock)[0x14] = 0;
        ((uint8_t*)newBlock)[0x15] = 0;
    }
}