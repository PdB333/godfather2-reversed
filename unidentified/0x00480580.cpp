// FUN_00480580: EARSObject::EARSObject

#include <cstdint>

// Forward declarations for subcomponent initialization
void InitializeSubComponent(void* address);  // FUN_004086d0
void FinalizeSubComponent(void* address);    // FUN_00408310
void GlobalInit();                           // FUN_0046c640

// Global memory manager (pointer at 0x01223410, +0x2d4 is its vtable)
class MemoryManager {
public:
    void deleteObject(void* obj, int flag);  // second vtable entry (offset 4)
};
extern MemoryManager* gMemoryManager;

// Vtable pointers defined elsewhere
extern void* EARSObject_vtable;   // PTR_FUN_00e333b8
extern void* EARSObject_vtable2;  // PTR_LAB_00e333d4 (offset 0x3C)
extern void* EARSObject_vtable3;  // PTR_LAB_00e333e4 (offset 0x48)

class EARSObject {
public:
    EARSObject(uint8_t deleteAndFreeFlag);

    // Unknown member at +0x14 (size 0x50? - only subobject at +0x50)
    // Virtual tables assumed at offsets 0, 0x3C, 0x48
};

EARSObject::EARSObject(uint8_t deleteAndFreeFlag) {
    // Set up vtable pointers (multiple inheritance? or additional vtable offsets)
    this->vtable = &EARSObject_vtable;     // [0]
    this->vtable2 = &EARSObject_vtable2;   // +0x3C
    this->vtable3 = &EARSObject_vtable3;   // +0x48

    // Initialize subcomponent at offset 0x50 (size? likely a nested object)
    InitializeSubComponent(reinterpret_cast<uint8_t*>(this) + 0x50);
    FinalizeSubComponent(reinterpret_cast<uint8_t*>(this) + 0x50);

    // Perform global one-time initialization (e.g., engine state)
    GlobalInit();

    // If flag bit 0 is set, deallocate this object via the memory manager
    if (deleteAndFreeFlag & 1) {
        gMemoryManager->deleteObject(this, 0);
    }
}