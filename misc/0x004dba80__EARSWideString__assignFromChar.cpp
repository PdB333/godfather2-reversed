// FUNC_NAME: EARSWideString::assignFromChar
// Function: Constructs a wide string from a C string with explicit length.
// Allocates a buffer for wide characters, copies and null-terminates.
// Address: 0x004dba80
void __thiscall EARSWideString::assignFromChar(EARSWideString* this, const char* src, unsigned int length)
{
    // Structure layout (all offsets in bytes):
    // +0x00: wchar_t* buffer   (pointer to wide char data)
    // +0x04: unsigned int length (number of wide characters, not including null)
    // +0x08: unsigned int capacity (allocated size in bytes)
    // +0x0C: void* allocator (vtable pointer for deallocation)

    if (length == 0)
    {
        // Empty string: null buffer, zero length and capacity, no allocator set
        this->buffer = nullptr;
        this->length = 0;
        this->capacity = 0;
        return;
    }

    // Set length and capacity (capacity in bytes, enough for 'length' wide chars)
    this->capacity = length * 2;                // each wchar_t is 2 bytes
    this->length = length;

    // Allocate memory: (length + 1) * 2 bytes to include null terminator
    // Allocator call math: (length & 0x7FFFFFFF) + 1, then * 2
    unsigned int allocSize = ((length & 0x7FFFFFFF) + 1) * 2;
    // The actual allocation function (likely malloc or custom allocator)
    this->buffer = (wchar_t*)FUN_009c8e50(allocSize);   // FUN_009c8e50 is allocation function

    // Copy each character as wide char (sign-extended)
    for (unsigned int i = 0; i < length; i++)
    {
        this->buffer[i] = (wchar_t)(signed char)src[i];
    }

    // Null-terminate the wide string
    this->buffer[length] = L'\0';

    // Set deallocation function for this buffer (vtable for custom allocator)
    this->allocator = (void*)thunk_FUN_009c8eb0;   // thunk to a deallocation function
}