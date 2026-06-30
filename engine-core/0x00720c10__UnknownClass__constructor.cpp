// FUNC_NAME: UnknownClass::constructor
// Address: 0x00720c10
// Role: Constructor that zero-initializes an object of size >= 0xCC bytes.
//       This function is called from 0x00769450, likely as part of object creation.
//       Object layout uses word offsets (32-bit).
//       Offsets are documented in comments relative to this pointer.

class UnknownClass {
public:
    // __fastcall in original, but for C++ we treat as thiscall.
    // The function returns the object pointer (this).
    // The calling convention is __fastcall (ECX for this).
    void __fastcall constructor();
};

void __fastcall UnknownClass::constructor() {
    // Clear first 8 dwords (offsets 0x00 - 0x1C)
    this->field_0x00 = 0;
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;

    // Clear dword at offset 0xBC (0x2F * 4)
    this->field_0xBC = 0;

    // Clear 96 bytes starting at byte offset 0x20 (from param_1+8)
    // This covers offsets 0x20 to 0x7F (inclusive)
    memset(&this->field_0x20, 0, 0x60);

    // Clear 48 bytes starting at byte offset 0x80 (from param_1+0x20)
    // This covers offsets 0x80 to 0xAF (inclusive)
    memset(&this->field_0x80, 0, 0x30);

    // Clear three dwords at offsets 0xB0, 0xB4, 0xB8
    this->field_0xB0 = 0;
    this->field_0xB4 = 0;
    this->field_0xB8 = 0;

    // Clear a qword (8 bytes) at offset 0xC0
    *(long long*)((char*)this + 0xC0) = 0LL;

    // Clear dword at offset 0xC8
    this->field_0xC8 = 0;

    // Return this (implicit in constructor)
}

// Note: The class layout is inferred from the initialization sequence.
// Field names are placeholders; actual members depend on the game's classes.
// The object size is at least 0xCC bytes based on last field written (offset 0xC8 + 4 = 0xCC).