// FUNC_NAME: StringBuffer::prependChar
// Address: 0x004d4150
// Reconstructed C++ method for prepending a character to a dynamic string buffer.
// The buffer structure (4 fields):
//   +0x00: char* buffer
//   +0x04: int length
//   +0x08: int capacity
//   +0x0C: void (*deallocator)(void*)

class StringBuffer {
public:
    char* buffer;          // +0x00
    int length;            // +0x04
    int capacity;          // +0x08
    void (*deallocator)(void*); // +0x0C

    // Prepend a character at the front of the string.
    void __thiscall prependChar(char ch);
};

// External functions (from the game's allocator)
extern void* __cdecl allocateMemory(size_t size); // FUN_009c8e50
extern void __cdecl freeMemory(void* ptr);        // thunk_FUN_009c8eb0
extern void __thiscall setSingleChar(StringBuffer* self, char ch); // FUN_004d3f90

void __thiscall StringBuffer::prependChar(char ch) {
    if (length == 0) {
        // If empty, just set the string to the single character.
        setSingleChar(this, ch);
        return;
    }

    if (length + 1 < capacity) {
        // There is room: shift existing content right by one byte.
        memmove(buffer + 1, buffer, length);
        buffer[0] = ch;
        length++;
        buffer[length] = '\0';
        return;
    }

    // Need to reallocate: allocate new buffer of size length+2.
    char* newBuffer = (char*)allocateMemory(length + 2);
    // Copy old string into new buffer starting at offset 1.
    char* src = buffer;
    char* dst = newBuffer + 1;
    do {
        *dst = *src;
        dst++;
        src++;
    } while (*src != '\0');
    // Place the new character at the front.
    newBuffer[0] = ch;

    // Free old buffer using the stored deallocator.
    if (buffer != nullptr) {
        deallocator(buffer);
    }

    // Update fields.
    length++;
    buffer = newBuffer;
    capacity = length + 1; // Note: original code sets capacity = _Size + 1, where _Size was old length.
    deallocator = freeMemory; // Set deallocator to the standard free function.
}