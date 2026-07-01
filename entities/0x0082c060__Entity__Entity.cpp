// FUNC_NAME: Entity::Entity
// Address: 0x0082c060
// This appears to be a constructor for the Entity class, which likely derives from at least two base classes.
// The byte parameter param_2 controls whether memory is allocated via a custom allocator (bit 0 set = allocate).

#include <cstdint>

class Entity {
public:
    // Virtual function table pointer at offset 0x00
    void** vtable;

    // Various members (offsets not fully known)
    // +0x00: vtable (first base class vtable)
    // +0x04..+0x2C: other base class data (from first constructor)
    // +0x30: pointer to second interface/vtable (set after first base ctor)
    // ... members up to size 0xA0 (allocated if param_2 bit 0 set)

    // Constructor
    // param_2: if bit 0 set, allocates memory for this object (size 0xA0) via custom allocator
    __thiscall Entity(uint8_t param_2) {
        // Set first vtable pointer (likely from first base class)
        this->vtable = reinterpret_cast<void**>(0x00d73868);

        // Call first base constructor (likely Entity's first base class)
        // Address: 0x0082b7a0
        this->firstBaseConstructor();

        // Set second vtable/interface pointer at offset 0x30
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + 0x30) = reinterpret_cast<void*>(0x00e32854);

        // Call second base constructor (likely second base class)
        // Address: 0x00821f60
        this->secondBaseConstructor();

        // If param_2 bit 0 is set, allocate memory for the object (e.g., placement new via manager)
        if (param_2 & 1) {
            // Get allocator interface (returns a pointer to an allocator object)
            // Address: 0x009c8f80
            void** allocator = reinterpret_cast<void**(__thiscall*)(void)>(
                reinterpret_cast<void*>(0x009c8f80)
            )();

            // Call allocate method (offset 4 in vtable) on allocator with this pointer and size 0xA0
            // This likely allocates memory and constructs the object there.
            void (*allocate)(void*, uint32_t) = reinterpret_cast<void(*)(void*, uint32_t)>(
                allocator[1]  // offset 4
            );
            allocate(this, 0xA0);
        }
    }

private:
    // Stubs for base constructors (not intended to be called directly)
    void __thiscall firstBaseConstructor() {
        // Address: 0x0082b7a0
        // Calls base constructor which sets up vtable and members.
    }

    void __thiscall secondBaseConstructor() {
        // Address: 0x00821f60
        // Calls second base constructor.
    }
};