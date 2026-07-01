// FUNC_NAME: PlayerActionableTargetSM::PlayerActionableTargetSM (constructor)
// Address: 0x0083fdd0
// Role: Initializes a PlayerActionableTargetSM (state machine) object with multiple inheritance.
// Sets up three vtable pointers: main vtable at +0x0, interface vtable at +0x3C (offset 0xf),
// and another interface vtable at +0x48 (offset 0x12). Then calls an initialization function with 0xd (13).

void __thiscall PlayerActionableTargetSM::PlayerActionableTargetSM(
    void* this,
    int baseParam        // Passed to base class constructor (likely a resource or type ID)
)
{
    // Call base class constructor
    baseClassConstructor(baseParam); // FUN_0083f8e0

    // Set main vtable for this class
    *(void**)this = &PTR_FUN_00d7452c; // Main vtable

    // Set vtable pointer for first inherited interface at offset +0x3C (0xf * 4)
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d7451c;

    // Set vtable pointer for second inherited interface at offset +0x48 (0x12 * 4)
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d74518;

    // Initialize some internal state (possibly a sub-object or static resource)
    initializeSubsystem(0xd); // FUN_0083f970
}