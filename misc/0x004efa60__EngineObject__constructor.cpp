// FUNC_NAME: EngineObject::constructor
// Address: 0x004efa60
// Role: Constructor for an EA EARS engine object with vtable, three parameters, and optional 32-byte data copy from source.
// This function initializes an object instance (this in ESI) with vtable at offset 0, stores three parameters at offsets 4,8,12,
// sets a flag or pointer at offset 0x30 (48), queries a global manager via FUN_00426af0, stores result at offset 0x34 (52),
// and conditionally copies 32 bytes from EDI to offsets 0x10-0x28 (16-40).

struct EngineObject {
    void** vtable;          // +0x00
    uint32_t param1;        // +0x04
    uint32_t param2;        // +0x08
    uint32_t param3;        // +0x0C
    uint8_t pad_10[4];      // +0x10 (part of optional data block)
    uint8_t optionalData[32]; // +0x10 (actually starts at +0x10, but copied as 2-uint64 chunks at offsets 0x10,0x18,0x20,0x28)
    uint32_t unk_30;        // +0x30 (set to 0)
    uint32_t somePointer;   // +0x34 (from in_EAX, likely this or owner)
    uint32_t managerResult; // +0x38 (result of FUN_00426af0)
};

// Global: DAT_012233e4 (some singleton or manager handle)
extern uint32_t DAT_012233e4;

// External function: likely retrieves a manager or allocates memory
extern int __fastcall FUN_00426af0(uint32_t managerHandle); // returns 0 or pointer to something

// Vtable for this class
extern void* PTR_FUN_00e373a4;

void __thiscall EngineObject::constructor(uint32_t param1, uint32_t param2, uint32_t param3, uint8_t* sourceData /* in EDI */, uint32_t owner /* in EAX */)
{
    // Store parameters
    this->param1 = param1;
    this->param2 = param2;
    this->param3 = param3;
    
    // Set vtable
    this->vtable = &PTR_FUN_00e373a4;
    
    // Clear offset 0x30
    this->unk_30 = 0;
    
    // Store owner (passed in EAX)
    this->somePointer = owner;
    
    // Query global manager
    int managerObject = FUN_00426af0(DAT_012233e4);
    this->managerResult = managerObject;
    
    // If manager query succeeded, copy 32 bytes from source data (EDI) to offsets 0x10,0x18,0x20,0x28
    if (managerObject != 0) {
        uint64_t* dest = reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 0x10);
        uint64_t* src = reinterpret_cast<uint64_t*>(sourceData);
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3];
    }
    
    return;
}