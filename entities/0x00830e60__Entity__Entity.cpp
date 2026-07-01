// FUNC_NAME: Entity::Entity
// Address: 0x00830e60
// Role: Constructor for Entity base class (or derived) with optional allocation flag.
// This constructor sets vtable pointers, calls base constructors, and optionally allocates memory via a memory manager.

// Known EA EARS classes: Entity, SimObject, BaseObject, etc.
// The class likely inherits from at least two base classes (vtable at +0x00 and +0x30).
// The parameter param_2 (byte) is an allocation flag: if bit 0 set, allocate 0x160 bytes via memory manager.

class Entity {
public:
    // Constructor: takes an allocation flag (1 = allocate, 0 = placement)
    __thiscall Entity(byte allocateFlag) {
        // Set first vtable pointer
        *reinterpret_cast<int**>(this) = &PTR_FUN_00d737fc;

        // Call base class constructor (likely Base or SimObject)
        FUN_0082aea0(); // Base::Base()

        // Set secondary vtable pointer at offset 0x30 (0xC * 4)
        *(reinterpret_cast<int**>(this) + 0xC) = &PTR_LAB_00e32854;

        // Call initialization routine (likely Entity::init)
        FUN_00821f60(); // Entity::init()

        // If allocation flag is set, allocate memory for possibly a derived type
        if ((allocateFlag & 1) != 0) {
            // Call memory manager (returns a pointer to an allocator or memory block)
            int* allocator = reinterpret_cast<int*>(FUN_009c8f80()); // MemoryManager::allocateResource?

            // Call virtual function at offset +4 on the allocator, passing this and size 0x160
            (*(code**)(*allocator + 4))(this, 0x160);
        }

        return;
    }
};