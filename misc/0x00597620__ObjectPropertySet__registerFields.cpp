// FUNC_NAME: ObjectPropertySet::registerFields
// Role: Registers fields for a property set of size 0x38 bytes. Called during static initialization.
// Address: 0x00597620
#include <cstdint>

// Assume a global property system pointer
extern PropertySystem* gPropertySystem;

// Reconstructed C++ for the function
int ObjectPropertySet::registerFields() {
    // Stack frame simulation for clarity, but using meaningful variables
    uint32_t flags = 0x200;          // 0x200
    uint32_t structSize = 0x38;      // 56 bytes
    uint32_t fieldIndex = 0;

    // Allocate a field descriptor block (size 0x38)
    // The first call to vtable+0x10 initializes the property set metadata
    // Parameters: flags (0x200), size (0x38), and possibly a pointer to a return address/debug info
    gPropertySystem->registerPropertySet(flags, structSize, (void*)0x59764b);

    // Register a short field at offset 2 (size 2)
    gPropertySystem->registerField(2, 2, (void*)0x597663);
    // Register an int field at offset 4 (size 4)
    gPropertySystem->registerField(4, 4, (void*)0x59767b);
    // Register another int field at offset 8 (size 4), initializing to 0
    gPropertySystem->registerField(8, 4, (void*)0x59769c);
    
    // Use the 0x24 vtable entry to set a default string value for the field at offset 0
    gPropertySystem->setDefaultString("default", (void*)0x5976b5);

    // Register a pointer field at offset 0xC (size 4)
    gPropertySystem->registerField(0xC, 4, (void*)0x5976d0);
    // Register a field at offset 0x2C (size 4) using stack variable
    gPropertySystem->registerField(0x2C, 4, (void*)&fieldIndex);
    // Register a pointer field at offset 0x30, size 4
    gPropertySystem->registerField(0x30, 4, (void*)&fieldIndex);
    // Register a pointer field at offset 0x34, size 4, initializing to null
    gPropertySystem->registerField(0x34, 4, nullptr);

    // Return the full size of the property set
    return structSize; // 0x38
}