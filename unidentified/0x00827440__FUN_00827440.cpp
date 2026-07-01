// FUNC_NAME: SomeComponent::SomeComponent
// Address: 0x00827440
// Constructor for a component/sub-system. Takes an owner object pointer (param_2).
// Calls base class constructor, sets vtable, initializes sub-component pointers.
// Conditionally initializes a sub-component and calls a virtual on it if a global flag is set.

#include <cstdint>

// Forward declarations
struct SomeBaseClass { // offset 0x00: vtable
    // ...
};

struct SubComponent { // stored at offset 0x50
    // vtable at +0
    // virtual function at +4 is called with owner parameter
    // ...
};

// Global flag indicating some system is active (e.g., debug mode)
extern int32_t g_someFlag; // DAT_0112db84

// External functions
extern void SomeBaseClass::SomeBaseClass(void* owner); // FUN_0046c590
extern int32_t SomeComponent::InitializeSubComponent(); // FUN_008357a0, returns pointer or sets offset 0x50

// Vtable symbols for this class
extern void* g_vtableSomeComponent; // PTR_FUN_00d73570
extern void* g_vtableSubComponentA; // PTR_LAB_00d73560 (offset 0x3C)
extern void* g_vtableSubComponentB; // PTR_LAB_00d7355c (offset 0x48)

struct SomeComponent {
    // +0x00: vtable pointer
    // +0x3C: some sub-object vtable pointer (SubComponentA)
    // +0x48: another sub-object vtable pointer (SubComponentB)
    // +0x50: sub-component pointer (SubComponent)

    SomeComponent(void* owner) {
        // Call base class constructor
        SomeBaseClass::SomeBaseClass(owner);

        // Set vtable for this object
        this->vtable = &g_vtableSomeComponent;

        // Set sub-object vtable pointers (likely embedded objects)
        this->subComponentA = &g_vtableSubComponentA; // offset 0x3C
        this->subComponentB = &g_vtableSubComponentB; // offset 0x48

        // Clear sub-component pointer
        this->subComponent = nullptr; // offset 0x50

        // If the global flag is set, attempt to initialize a sub-component
        if (g_someFlag != 0) {
            SomeComponent::InitializeSubComponent(); // sets subComponent? (call with this)

            // If subComponent was set, call its virtual function at offset 4 with owner
            if (this->subComponent != nullptr) {
                auto subVtable = *(int32_t**)this->subComponent;
                auto func = (void (__thiscall*)(SubComponent*, void*))subVtable[1]; // offset 4
                func(this->subComponent, owner);
            }
        }
    }

    // Offsets documented:
    // +0x00: void* vtable
    // +0x3C: void* subComponentA
    // +0x48: void* subComponentB
    // +0x50: SomeComponent* subComponent

    void* vtable; // offset 0x00
    /* ... other base class members up to offset 0x3C ... */
    void* subComponentA; // offset 0x3C
    void* subComponentB; // offset 0x48
    SomeComponent* subComponent; // offset 0x50
};
```