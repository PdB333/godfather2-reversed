// FUNC_NAME: StringBuffer::initFromObjectString
void __fastcall StringBuffer::initFromObjectString(void* src) {
    // This function initializes a StringBuffer structure (pointed by ESI)
    // by reading a string from the source object at src.
    // The StringBuffer layout (offsets in bytes from this):
    // +0x00: allocatedBuffer (dword) - set to 0 initially
    // +0x04: stringLength (dword)
    // +0x08: someFlag (byte) - set to 0
    // +0x0C: sourcePointer (char*) - temporary pointer to source string
    // +0x10: counter (dword) - used for length calculation
    // +0x14: allocatedMemory (dword) - pointer to newly allocated memory
    // +0x18: unknownField1 (dword) - set to 0
    // +0x1C: unknownField2 (dword) - set to 0

    // Get string pointer from src; prefer at +0x88, fallback to +0x7C
    char* strPtr = *(char**)((char*)src + 0x88);
    if (strPtr == 0) {
        strPtr = *(char**)((char*)src + 0x7C);
    }

    // Clear initial fields
    *(int*)this = 0;                    // allocatedBuffer = 0
    *(char*)((char*)this + 8) = 0;      // someFlag = 0

    // Store source pointer and count characters
    *(char**)((char*)this + 0x0C) = strPtr; // sourcePointer = strPtr
    *(int*)((char*)this + 0x10) = 0;        // counter = 0

    char c = *strPtr;
    while (c != '\0') {
        (*(int*)((char*)this + 0x10))++;
        c = *(char*)(*(char**)((char*)this + 0x0C) + *(int*)((char*)this + 0x10));
    }

    // Store computed length
    *(int*)((char*)this + 0x04) = *(int*)((char*)this + 0x10); // stringLength = counter

    // Local structure for allocation call (size: 12 bytes, all zero)
    struct AllocInfo {
        int field0;
        int field4;
        int field8;
    } allocInfo = {0, 0, 0};

    // Allocate memory via a function pointer from a global table
    // The table is at DAT_012234ec, offset +4 gives the allocator function
    // The allocator takes (size, &allocInfo) and returns a pointer
    void* (*allocator)(int, void*) = *(void* (__fastcall**)(int, void*))((*(int*)DAT_012234ec) + 4);
    void* mem = allocator(*(int*)((char*)this + 0x10) + 1, &allocInfo);

    // Store allocated buffer and clear remaining fields
    *(void**)((char*)this + 0x14) = mem; // allocatedMemory
    *(int*)((char*)this + 0x18) = 0;     // unknownField1
    *(int*)((char*)this + 0x1C) = 0;     // unknownField2
}