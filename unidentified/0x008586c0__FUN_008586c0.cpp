// FUNC_NAME: UnknownClass::UnknownClass (constructor)
// Address: 0x008586c0
// Role: Base class constructor with optional internal memory allocation

#include <cstddef>

// Forward declaration of vtable
extern void* VTable_00d753a0; // PTR_FUN_00d753a0

// External functions
extern void BaseClassInit();                 // FUN_0099c940
extern int* GetAllocatorInstance();          // FUN_009c8f80 – returns an allocator object

class UnknownClass {
public:
    void* vtable; // +0x00

    // Constructor
    // param_2: flag, bit 0 indicates whether to allocate internal buffer
    UnknownClass(byte flag);

private:
    // Size for internal buffer allocation
    static const size_t INTERNAL_SIZE = 0x70;
};

UnknownClass::UnknownClass(byte flag)
{
    // Set virtual table pointer
    this->vtable = &VTable_00d753a0;

    // Call base class initialization / common constructor
    BaseClassInit();

    // If object was dynamically allocated (e.g., via operator new)
    if (flag & 1) {
        // Obtain allocator instance
        int* allocator = GetAllocatorInstance();

        // Allocate internal buffer of size 0x70 using allocator's virtual method at offset 4
        // (**(code **)(*allocator + 4))(this, INTERNAL_SIZE)
        reinterpret_cast<void (*)(UnknownClass*, size_t)>(allocator[1])(this, INTERNAL_SIZE);
    }
}