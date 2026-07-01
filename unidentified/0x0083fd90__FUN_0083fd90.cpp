// FUNC_NAME: SomeComponent::Constructor (reconstructed)
// Address: 0x0083fd90
// This is a constructor for a class derived from an unknown base.
// It sets the vtable pointer and two additional function pointers at offsets 0x3C and 0x48.
// The base constructor (FUN_0083f920) is called first.
// If param_2 & 1 is set, a deallocation function (likely operator delete) is called
// with size 0x5C, suggesting this constructor can be used for both stack and heap allocation.

#include <cstdint>

class SomeComponent {
public:
    // Vtable pointer (0x00)
    void* vtable; // set to PTR_FUN_00d744f8

    // Other members (offsets relative to this)
    // +0x3C: pointer to function table or callback
    void* m_pFunc1; // set to PTR_LAB_00d744e8
    // +0x48: pointer to function table or callback
    void* m_pFunc2; // set to PTR_LAB_00d744e4

    // Base class data (inferred from call to 0x0083f920)
    // ...

    SomeComponent(uint8_t param_2);
};

// External function declarations (inferred)
extern void BaseConstructor(); // FUN_0083f920
extern void DeallocateObject(void* obj, uint32_t size); // FUN_0043b960 (operator delete?)

// Constructor implementation
SomeComponent::SomeComponent(uint8_t param_2) {
    // Set vtable
    vtable = (void*)0x00d744f8;

    // Set additional function pointers at offsets 0x3C and 0x48
    // Note: These are stored directly in the object, not in vtable.
    m_pFunc1 = (void*)0x00d744e8;
    m_pFunc2 = (void*)0x00d744e4;

    // Call base class constructor
    BaseConstructor();

    // If param_2 & 1 is set, deallocate this object (likely for stack-allocated case?)
    if (param_2 & 1) {
        DeallocateObject(this, 0x5C);
    }
}