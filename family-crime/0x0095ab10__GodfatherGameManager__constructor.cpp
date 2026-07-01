// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x0095ab10
// Role: Singleton game manager constructor; allocates and initializes multiple string buffers and state fields.

// This function is the constructor for GodfatherGameManager (likely a global singleton).
// It calls the base class constructor, sets vtable pointers, allocates 10 buffers (sizes 0x80 or 0x20),
// zero-initializes them, and initializes several integer/byte fields to sentinel values.

// Note: The base constructor is at 0x00957ed0, allocation helper at 0x009c8e80 (likely operator new or array new).
// Offsets are relative to this pointer (4-byte aligned).

__thiscall GodfatherGameManager * __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
    // Call base class constructor (likely some EARS base)
    FUN_00957ed0();

    // Set up vtable/interface pointers
    // The vtable entries are overwritten twice; this is typical of multiple inheritance setup.
    this->field_0x50 = &PTR_LAB_00d8ca90;   // +0x50
    DAT_0113003c = this;                     // Global singleton pointer
    this->field_0x54 = &PTR_LAB_00d84f98;   // +0x54
    this->vtable = &PTR_FUN_00d8cad8;       // +0x00 (main vtable)

    // Overwrite with secondary vtable entries
    this->field_0x50 = &PTR_LAB_00d8caac;   // +0x50
    this->field_0x54 = &PTR_LAB_00d8ca94;   // +0x54

    // Initialize integer fields to 0 or -1
    this->field_0x58 = 0;                   // +0x58
    this->field_0x5c = 0;                   // +0x5c
    this->field_0x60 = 0;                   // +0x60
    this->field_0x64 = 0;                   // +0x64
    this->field_0x68 = 0;                   // +0x68
    this->field_0x6c = 0;                   // +0x6c
    this->field_0x74 = 0;                   // +0x74
    this->field_0x78 = -1;                  // +0x78 (sentinel)
    this->field_0x8c = -1;                  // +0x8c
    this->field_0x90 = 0;                   // +0x90
    this->field_0x94 = -1;                  // +0x94
    *(byte *)((uint)&this->field_0xb0) = 0; // +0xb0 byte (cast to byte pointer)
    this->field_0xb4 = 0;                   // +0xb4
    this->field_0xb8 = 0;                   // +0xb8
    this->field_0xc0 = -1;                  // +0xc0
    *(byte *)((uint)&this->field_0xc4) = 0; // +0xc4 byte

    // Allocate buffers: 0x80 = 128 bytes, 0x20 = 32 bytes
    this->buffer_0x7c = (char *)FUN_009c8e80(0x80);  // +0x7c
    this->buffer_0x80 = (char *)FUN_009c8e80(0x80);  // +0x80
    this->buffer_0x84 = (char *)FUN_009c8e80(0x20);  // +0x84
    this->buffer_0x88 = (char *)FUN_009c8e80(0x80);  // +0x88
    this->buffer_0x98 = (char *)FUN_009c8e80(0x80);  // +0x98
    this->buffer_0x9c = (char *)FUN_009c8e80(0x20);  // +0x9c
    this->buffer_0xa0 = (char *)FUN_009c8e80(0x20);  // +0xa0
    this->buffer_0xa4 = (char *)FUN_009c8e80(0x20);  // +0xa4
    this->buffer_0xa8 = (char *)FUN_009c8e80(0x20);  // +0xa8
    this->buffer_0xac = (char *)FUN_009c8e80(0x80);  // +0xac

    // Zero-initialize the first byte of each buffer
    this->buffer_0xac[0] = 0;
    this->buffer_0xa8[0] = 0;
    this->buffer_0xa4[0] = 0;
    this->buffer_0xa0[0] = 0;
    this->buffer_0x9c[0] = 0;
    this->buffer_0x98[0] = 0;
    this->buffer_0x88[0] = 0;
    this->buffer_0x84[0] = 0;
    this->buffer_0x80[0] = 0;
    this->buffer_0x7c[0] = 0;

    // Zero additional byte fields at offsets 0xbf, 0xbe, 0xbd, and 0xbc (pointer field? cast as byte)
    *(byte *)((uint)this + 0xbf) = 0;
    *(byte *)((uint)this + 0xbe) = 0;
    *(byte *)((uint)this + 0xbd) = 0;
    this->field_0xbc = 0;   // +0xbc (was set to 0 as pointer? but decompiler cast to undefined1*)

    return this;
}