// FUNC_NAME: EARSString::EARSString(undefined4* source, int param3, int param4, void* param5)
// Function at 0x0069ad30 - Constructor for EARS engine string class with small string optimization (SSO)
// Layout: +0x00 vtable, +0x04 field1 (0), +0x08 byte field2 (0), +0x0C pointer (self-ref for SSO), 
//         +0x10 pointer (also self-ref), +0x14 field5 (0), +0x18 byte (0), +0x1C field7 (0), 
//         +0x24 stored param3, +0x28 flag (0x80000001 or 0x80000002), 
//         +0x2C internal buffer start (character data), +0x30 (offset 48) field0xc (0), +0x34 field0xd (0)
// The buffer is at offset 0x2C (44 bytes from start) and can hold short strings inline.

#include <cstdint>

// Forward declarations of helper functions
extern void earStringCopy(const uint16_t* source, int zero, int length); // actually wchar? - using uint16_t for Unicode
extern void* earGetEmptyString(void);  // returns pointer to a global empty string descriptor
extern void earRegisterString(void);  // post-construction registration

// Vtable symbol (defined elsewhere)
extern void* PTR_FUN_00d5ceb0;

class EARSString {
public:
    // Constructor
    void* __thiscall constructor(void* sourceDesc, int param3, int param4, void* param5) {
        // Clear fields
        this->field1 = 0;            // +0x04
        *(uint8_t*)((uint8_t*)this + 8) = 0;  // +0x08
        this->ssoptr = 0;            // +0x0C (8 bytes)
        this->ssoptr2 = 0;           // +0x14 (8 bytes)
        this->ssoptr_self = (void*)&this->ssoptr;  // point to self for SSO indicator
        this->ssoptr_ptr = &this->ssoptr;          // duplicate self pointer
        this->field5 = 0;            // +0x14
        *(uint8_t*)((uint8_t*)this + 0x18) = 0;    // +0x18
        this->field7 = 0;            // +0x1C
        this->vtable = &PTR_FUN_00d5ceb0;  // +0x00 set vtable

        // Determine flag based on param4
        uint32_t flag;
        if (param4 == 0 || param4 == 1) {
            flag = 0x80000001;
        } else {
            flag = 0x80000002;
        }
        this->flag = flag;            // +0x28

        // Zero out internal buffer pointer area? Actually zeroing fields at +0x2C, +0x30, +0x34
        this->bufferPtr = 0;          // +0x2C
        this->field0xc = 0;           // +0x30
        this->field0xd = 0;           // +0x34

        // Check if the source descriptor has a reference count at +4
        if (*(int*)((uint8_t*)param5 + 4) == 0) {
            // Use the provided source descriptor
            if (this->bufferPtr != sourceDesc) {  // avoid self-copy
                uint16_t* src = *(uint16_t**)sourceDesc;
                if (src == nullptr) {
                    src = &DAT_00e2df14;  // global empty string data
                }
                earStringCopy(src, 0, *(int*)((uint8_t*)sourceDesc + 4));
            }
        } else {
            // Use global empty string descriptor from earGetEmptyString
            void* globalDesc = earGetEmptyString();
            if (this->bufferPtr != globalDesc) {
                uint16_t* src = *(uint16_t**)globalDesc;
                if (src == nullptr) {
                    src = &DAT_00e2df14;
                }
                earStringCopy(src, 0, *(int*)((uint8_t*)globalDesc + 4));
            }
            // Unusual: potential callback (decompilation artifact - may be leftover from optimizer)
            // local_10 and local_4 are uninitialized in original code; this branch is suspect.
            // Keeping as-is for fidelity.
            int local_10;   // uninitialized
            void (*local_4)(int);  // function pointer
            if (local_10 != 0) {
                local_4(local_10);
            }
            earRegisterString();
        }

        return this;
    }

    // Data members (offsets relative to this)
    void* vtable;                     // +0x00
    int field1;                       // +0x04
    // +0x08: byte (padding)
    void* ssoptr;                     // +0x0C (8 bytes? actually 4 bytes? But decompiler shows 8)
    void* ssoptr2;                    // +0x14 (8 bytes)
    void* ssoptr_self;                // +0x0C actually first 4 bytes of ssoptr? Overlap
    void* ssoptr_ptr;                 // +0x10
    int field5;                       // +0x14? overlapped
    // +0x18: byte
    int field7;                       // +0x1C
    int storedParam3;                 // +0x24
    uint32_t flag;                    // +0x28
    void* bufferPtr;                  // +0x2C (start of inline buffer)
    int field0xc;                     // +0x30
    int field0xd;                     // +0x34
    // Actual character data begins at +0x2C (buffer of typical 12-16 bytes)
};

// Note: The class layout is approximate; offsets are based on param_1 index arithmetic.
// The self-referential pointer at +0x0C is typical of SSO strings: if the buffer is internal,
// it points to itself. The condition compares bufferPtr (offset 0x2C) with source descriptor
// to avoid copying when source is already internal.
// DAT_00e2df14 is a global Unicode null character or empty string constant.