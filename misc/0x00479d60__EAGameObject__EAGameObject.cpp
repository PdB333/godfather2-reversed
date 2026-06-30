// FUNC_NAME: EAGameObject::EAGameObject
// Function address: 0x00479d60
// Role: Constructor for EAGameObject base class (EA EARS engine). Initializes vtable, two interface tables (at offsets 0x3C and 0x48), calls base constructor (FUN_00479690), and optionally registers with global allocator manager if heap-allocated (bit 0 of constructorFlags set).

#include <cstdint>

class EAGameObject {
public:
    // Vtable pointer at offset 0x00
    // Interface table 1 at offset 0x3C (0xF * 4)
    // Interface table 2 at offset 0x48 (0x12 * 4)
    // Other members unknown

    EAGameObject(uint8_t constructorFlags);
    // Base constructor called internally: void baseConstruct();
    // Global manager at DAT_01223410 + 0x2D4 provides deallocation function.
};

// Global reference to game manager or allocator system
extern uintptr_t DAT_01223410;

typedef void (*DeallocFunc)(EAGameObject*, int);

void EAGameObject::baseConstruct(); // Forward declaration of base constructor at 0x00479690

EAGameObject::EAGameObject(uint8_t constructorFlags) {
    // Set vtable and interface tables
    this->vtable = &PTR_FUN_00e33018;            // +0x00
    this->interfaceTable1 = &PTR_LAB_00e33034;   // +0x3C
    this->interfaceTable2 = &PTR_LAB_00e33044;   // +0x48

    // Call base class constructor
    baseConstruct();

    // If the object is heap-allocated (flag bit 0 set), register deallocation with global manager
    if (constructorFlags & 1) {
        // Retrieve function pointer from global manager structure at offset 0x2D4
        uint8_t* globalManager = *(uint8_t**)(DAT_01223410 + 0x2D4);
        // The function is at offset 4 from the retrieved pointer (likely a vtable)
        DeallocFunc dealloc = *(DeallocFunc*)globalManager + 4;
        dealloc(this, 0);
    }
}