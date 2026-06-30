// FUNC_NAME: SimNpc::SimNpc
// ADDRESS: 0x00724a30
// Role: Constructor for SimNpc (or similar game entity) with multiple inheritance
// Initializes vtable pointers for itself and two base classes, then calls base constructor.
// If allocFlag & 1 is set, calls additional initialization (likely placement allocation helper).

// External vtable symbols referenced from Ghidra
extern void* PTR_FUN_00d62348;  // Main vtable for SimNpc
extern void* PTR_LAB_00d62338;  // Vtable for first base interface (at +0x3C)
extern void* PTR_LAB_00d62334;  // Vtable for second base interface (at +0x48)

// Forward declaration of base class constructor (unknown exactly which one)
extern void SimObject_constructor(SimNpc* thisPtr);

// Forward declaration of memory/placement handler
extern void HandleAllocation(void* ptr, unsigned int size);

SimNpc* __thiscall SimNpc::SimNpc(byte allocFlag) {
    // Set the main vtable pointer (offset 0)
    this->vfptr = &PTR_FUN_00d62348;
    // Set additional vtable pointers for multiple inheritance
    // Offset 0x0F * 4 = 0x3C: first interface vtable
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d62338;
    // Offset 0x12 * 4 = 0x48: second interface vtable
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d62334;

    // Call base class constructor (likely SimObject or similar)
    SimObject_constructor(this);

    // If allocFlag indicates heap-allocated, call additional initialization (size 0xC4).
    if (allocFlag & 1) {
        HandleAllocation(this, 0xC4); // 196 bytes
    }

    return this;
}