//FUNC_NAME: StreamManager::constructor
// Function address: 0x006b7aa0
// This appears to be a constructor for a class that manages a stream buffer.
// It initializes vtable pointers, sets fields from globals, and clears a buffer of size 0x7fff.

class StreamManager {
public:
    void* vtable;               // +0x00
    // +0x3C (offset 0xf * 4)
    void* field_0x3C;           // +0x3C
    // +0x48 (offset 0x12 * 4)
    void* field_0x48;           // +0x48
    // +0x5C (offset 0x17 * 4)
    void* field_0x5C;           // +0x5C
    // +0x60 (offset 0x18 * 4)
    int field_0x60;             // +0x60
    // +0x64 (offset 0x19 * 4, but stored as byte)
    char field_0x64;            // +0x64
};

StreamManager* __thiscall StreamManager::constructor(StreamManager* this, int unknownParam) {
    // Call base class or initializer with the parameter
    FUN_0046c590(unknownParam);

    // Set the primary vtable pointer
    this->vtable = &PTR_FUN_00d5e588;

    // Set secondary vtable-like pointers
    this->field_0x3C = &PTR_LAB_00d5e578;
    this->field_0x48 = &PTR_LAB_00d5e574;

    // Store a global pointer (likely a singleton or manager)
    this->field_0x5C = DAT_00e448f0;

    // Zero out fields
    this->field_0x60 = 0;
    this->field_0x64 = 0;

    // Initialize a global buffer of size 0x7fff (32767 bytes)
    // This is likely a stream buffer or audio data buffer
    FUN_004086b0(&DAT_0120e93c, 0x7fff);

    return this;
}