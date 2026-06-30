// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Address: 0x0074d510
// Role: Destructor for GodfatherGameManager (or similar complex manager class)
// Cleans up sub-objects, vtable pointers, and releases memory.

#include <cstdint>

// Forward declarations for called functions
void __fastcall FUN_0074d200(void* this);        // Base class destructor?
void __fastcall FUN_007f6420(uint32_t size);     // Deallocation (operator delete with size?)
void __fastcall FUN_007165c0();                  // Additional cleanup
void __fastcall FUN_004daf90(void* ptr);         // Memory deallocation
void __fastcall FUN_006e6430(uint32_t arg1, void* ptr); // Some manager function
void __fastcall FUN_0072cb10(uint32_t arg1);     // Another cleanup
void __fastcall FUN_0074d280();                  // Base class destructor?
void __fastcall FUN_0074d1c0();                  // Static cleanup
void __fastcall FUN_0080ea60();                  // Static cleanup

class GodfatherGameManager {
public:
    // Destructor
    void __fastcall destroy();

    // Vtable pointers (multi-inheritance)
    void* vtable;        // +0x00
    uint32_t unknown0x58; // +0x58
    uint32_t unknown0x5C; // +0x5C

    // Bit flags at offset 0xE4
    uint32_t flags;      // +0xE4

    // Pointer at +0x8C
    uint32_t somePtr;    // +0x8C

    // Pointer at +0x88 (ID or handle)
    uint32_t idPtr;      // +0x88

    // Pointer at +0x94
    uint32_t anotherPtr; // +0x94

    // Pointer at +0xD8
    uint32_t subObject;  // +0xD8

    // Vtable pointer at +0xB4
    void* vtable2;       // +0xB4

    // Pointers at +0xC4, +0xB8, +0xA4
    uint32_t ptr1;       // +0xC4
    uint32_t ptr2;       // +0xB8
    uint32_t ptr3;       // +0xA4
};

void __fastcall GodfatherGameManager::destroy() {
    uint32_t* piVar1;
    uint32_t iVar2;
    uint32_t uVar3;

    // Set main vtable
    this->vtable = (void*)0x00d6473c;
    // Set secondary vtable pointers
    *(uint32_t*)((uint8_t*)this + 0x58) = (uint32_t)0x00d64738;
    *(uint32_t*)((uint8_t*)this + 0x5C) = (uint32_t)0x00d64734;

    // Call base class destructor
    FUN_0074d200();

    // Release memory of size 0x34 (some embedded object)
    FUN_007f6420(0x34);

    // Check bit 1 of flags (offset 0xE4)
    if (((this->flags >> 1) & 1) == 0) {
        uVar3 = 0x59;
    } else {
        uVar3 = 0x47;
        // Additional cleanup if flag set
        FUN_007165c0();
    }
    FUN_007f6420(uVar3);

    // Handle pointer at +0x8C
    piVar1 = &this->somePtr;
    if ((this->somePtr != 0) && (this->somePtr != 0x48)) {
        // Convert pointer to index or base
        if (this->somePtr == 0) {
            iVar2 = 0;
        } else {
            iVar2 = this->somePtr - 0x48;
        }
        // Dereference +0x98 from the base
        uint32_t* ptrAt98 = (uint32_t*)(iVar2 + 0x98);
        if (*ptrAt98 != 0) {
            FUN_004daf90((void*)*ptrAt98);
            *ptrAt98 = 0;
        }
        // Decrement reference count at +0xA8
        *(uint8_t*)(iVar2 + 0xA8) -= 1;
    }

    // If anotherPtr (offset 0x94) is set, cleanup
    if (this->anotherPtr != 0) {
        FUN_006e6430(0, (void*)this->idPtr); // offset 0x88
    }

    // If idPtr (offset 0x88) is set and its byte at +0x1B8C == 4
    if ((this->idPtr != 0) && (*(uint8_t*)(this->idPtr + 0x1B8C) == 0x04)) {
        FUN_0072cb10(0);
    }

    // Free sub-object at offset 0xD8
    if (this->subObject != 0) {
        FUN_004daf90(&this->subObject);
    }

    // Set vtable2 to another function table
    this->vtable2 = (void*)0x00d64720;

    // Free ptr1 and ptr2 (offsets 0xC4, 0xB8)
    if (this->ptr1 != 0) {
        FUN_004daf90(&this->ptr1);
    }
    if (this->ptr2 != 0) {
        FUN_004daf90(&this->ptr2);
    }

    // Change vtable2 to a different table
    this->vtable2 = (void*)0x00d64708;

    // Free ptr3 and anotherPtr again
    if (this->ptr3 != 0) {
        FUN_004daf90(&this->ptr3);
    }
    if (this->anotherPtr != 0) {
        FUN_004daf90(&this->anotherPtr);
    }

    // Free the main pointer at +0x8C
    if (*piVar1 != 0) {
        FUN_004daf90(piVar1);
    }

    // Final static cleanup functions
    FUN_0074d280();
    FUN_0074d1c0();
    FUN_0080ea60();
}