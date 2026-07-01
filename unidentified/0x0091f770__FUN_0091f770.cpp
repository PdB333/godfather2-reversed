// FUNC_NAME: SomeClass::SomeClass(bool allocateSubObject)

// 0x0091f770: Constructor for a game object that may allocate a large sub-object (0x2e50 bytes).
// Calls base class constructor at 0x0091f490. If the boolean flag is set, it retrieves an allocator
// and calls its second virtual method to perform allocation on this object.

#include <cstddef>

class SomeClass {
public:
    // Base class constructor (0x0091f490)
    void baseConstructor();

    // Allocator object retrieved from FUN_009c8f80 (likely a memory pool manager)
    class Allocator {
    public:
        virtual void allocate(void* ptr, size_t size) = 0; // offset 4 in vtable
    };

    // Constructor
    bool __thiscall constructor(bool allocateSubObject) {
        // Call base class constructor
        baseConstructor();

        if (allocateSubObject) {
            // Retrieve allocator (singleton or context-specific)
            Allocator* allocator = reinterpret_cast<Allocator*>(FUN_009c8f80());

            // Call the allocator's virtual function at vtable+4: allocate(this, 0x2e50)
            allocator->allocate(this, 0x2e50);
        }

        return this; // return value is this (constructor pattern)
    }

    // Stub for the actual allocation function
    static void* FUN_009c8f80();
};

// Note: The actual base constructor at 0x0091f490 is called but not shown here.