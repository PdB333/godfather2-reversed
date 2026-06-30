// FUNC_NAME: EARSBaseObject::constructor
// Source: 0x004dabb0
// Initializes an object with a placeholder GUID ({BADBADBA-BEEF-BEEF-555A-C1EA11091091}) and calls base initializers.
// Returns the this pointer.

#include <cstring>

class EARSBaseObject {
public:
    // vtable pointer (offset 0x00) is set to 1 (likely an index or reference count)
    // GUID string is stored at byte offset 0x04 (39 bytes: 38 chars + null terminator)
    // Byte at offset 0x2C set to 1
    // DWORD at offset 0x4C set to 0

    EARSBaseObject* __thiscall initialize(uint32_t thisPtr);
};

// External functions
void __cdecl FUN_004d9d60(uint32_t eax);  // base class constructor (uses EAX)
void __cdecl FUN_004d9ff0(void);          // base class initializer
void __cdecl FUN_004da530(void);          // destructor for partial cleanup
void __cdecl FUN_009c8eb0(uint32_t ptr);  // free memory (operator delete)

EARSBaseObject* __thiscall EARSBaseObject::constructor() {
    uint32_t* self = reinterpret_cast<uint32_t*>(this);
    char* selfBytes = reinterpret_cast<char*>(this);

    // Constant GUID string (38 characters + null terminator = 39 bytes)
    const char* guidStr = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";

    // Copy GUID string into object at byte offset 0x04 (beginning of char array)
    // Loop unrolled manually: copy 9 DWORDs (36 bytes) + one WORD (2 bytes) + one byte
    char* dest = selfBytes + 4;
    uint32_t* dest32 = reinterpret_cast<uint32_t*>(dest);
    for (int i = 0; i < 9; ++i) {
        dest32[i] = *reinterpret_cast<const uint32_t*>(guidStr + i * 4);
    }
    // After loop, dest32 now points to offset 4 + 36 = 40 (0x28)
    *reinterpret_cast<uint16_t*>(dest + 36) = *reinterpret_cast<const uint16_t*>(guidStr + 36);
    *reinterpret_cast<char*>(dest + 38) = guidStr[38]; // null terminator at index 38

    // Set byte at offset 0x2C (44) to 1
    selfBytes[0x2C] = 1;

    // Set DWORD at offset 0x4C to 0 (scaled pointer arithmetic: self + 0x13)
    self[0x13] = 0;

    // Set DWORD at offset 0x00 to 1 (possibly a vtable index or reference count)
    self[0x00] = 1;

    // Call base class constructor (passes this in EAX)
    FUN_004d9d60(reinterpret_cast<uint32_t>(this));

    // Call another initializer
    FUN_004d9ff0();

    // Exception handling / cleanup (local_4 is uninitialized, indicates a possible error path)
    int local_4; // uninitialized, left as decompiler artifact
    if (local_4 != 0) {
        FUN_004da530();     // partial destructor
        FUN_009c8eb0(local_4); // free memory
    }

    return this;
}