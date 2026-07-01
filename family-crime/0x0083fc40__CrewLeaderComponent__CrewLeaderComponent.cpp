// FUNC_NAME: CrewLeaderComponent::CrewLeaderComponent

#include <cstdint>

// This class inherits from multiple base classes, as evidenced by the setting of 
// vtable pointers at offsets 0x00, 0x3C, and 0x48 within the object.
// The constructor takes a boolean flag indicating whether the object was heap-allocated.
// If heap-allocated and an error occurs, it calls a memory deallocation function.

class CrewLeaderComponent {
public:
    // Constructor: heapAllocated indicates if the object was allocated via operator new
    CrewLeaderComponent(uint8_t heapAllocated) {
        // Set primary vtable pointer (offset 0x00)
        *(void**)this = (void*)0x00d744c4; // vtable for primary base class

        // Set secondary vtable pointers for additional base classes
        // +0x3C (index 15) and +0x48 (index 18)
        *(void**)((uint8_t*)this + 0x3C) = (void*)0x00d744b4; // vtable for base class 2
        *(void**)((uint8_t*)this + 0x48) = (void*)0x00d744b0; // vtable for base class 3

        // Call the base class constructor (likely sets up other members)
        // Address: 0x0046c640
        ((void (*)(void*))0x0046c640)(this);

        // If the object was heap-allocated (bit 0 set), fail-safe deallocation
        if (heapAllocated & 1) {
            // Memory deallocation function with object size 0x50 (80 bytes)
            // Address: 0x0043b960
            ((void (*)(void*, uint32_t))0x0043b960)(this, 0x50);
        }
    }
};