// FUNC_NAME: BNKStreamManager::BNKStreamManager
// Address: 0x006ea240
// Role: Constructor for BNKStreamManager, initializes vtable pointers, zeroes fields, and optionally loads a 32KB sound bank from a global.

// Forward declarations (from other modules)
void __thiscall EARSObject::EARSObject(uint32 param);       // base class constructor at 0x0046c590
void __cdecl copyMemory(void* dest, void* src, int size);   // data copy at 0x00408900

// Global constant pointer used for bank data
extern void* DAT_0120e93c;

BNKStreamManager* __thiscall BNKStreamManager::BNKStreamManager(BNKStreamManager* this, uint32 param)
{
    // Call base class constructor
    EARSObject::EARSObject(param);

    // Set virtual function table pointer (offset +0x00)
    this->vtable = (void*)0x00d5fd1c;

    // Initialize sub‑vtable pointers for inherited interfaces
    this->subVtable1 = (void*)0x00d5fd0c;   // +0x3c (offset 0xf * 4)
    this->subVtable2 = (void*)0x00d5fd08;   // +0x48 (offset 0x12 * 4)

    // Zero out all remaining data members
    this->field_0x5c = 0;   // +0x5c
    this->field_0x58 = 0;   // +0x58
    this->field_0x54 = 0;   // +0x54
    this->field_0x50 = 0;   // +0x50
    this->field_0x60 = 0;   // +0x60
    this->field_0x64 = 0;   // +0x64
    this->field_0x68 = 0;   // +0x68
    this->field_0x6c = 0;   // +0x6c
    this->field_0x70 = 0;   // +0x70

    // 16‑bit fields at odd offsets (non‑aligned)
    *(uint16*)((char*)this + 0x74) = 0;   // +0x74 (word)
    *(uint16*)((char*)this + 0x76) = 0;   // +0x76 (word)

    this->field_0x84 = 0;   // +0x84
    this->field_0x80 = 0;   // +0x80
    this->field_0x7c = 0;   // +0x7c
    this->field_0x78 = 0;   // +0x78
    this->field_0x88 = 0;   // +0x88

    // If a global bank data pointer is present, copy 32KB into the internal buffer
    if (DAT_0120e93c != 0)
    {
        copyMemory((char*)this + 0x3c, &DAT_0120e93c, 0x8000);
    }

    return this;
}