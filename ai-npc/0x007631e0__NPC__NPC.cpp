// FUNC_NAME: NPC::NPC

// Constructor for NPC class (Assumed based on object hierarchy and field offsets)
// Address: 0x007631e0
// Calls base constructor, sets up vtable pointers, initializes many fields, and possibly allocates a resource.

// Note: Some decompilation artifacts (e.g., unaff_retaddr) represent register usage that cannot be fully resolved.
// The 32-bit offsets are relative to 'this' (multiple of 4).

NPC * __thiscall NPC::NPC(NPC *this, int parentOrHandle, int extraData)
{
    // Base class constructor call (likely Entity::Entity or SimObject::SimObject)
    FUN_004ac120(parentOrHandle, extraData);

    // Vtable and field initialization
    this[0x14] = &PTR_FUN_00e32808;          // +0x50: temporary vtable or function pointer (overwritten later)
    this[0x15] = 0;                          // +0x54: some pointer, null

    this[0x00] = &PTR_LAB_00d65584;         // +0x00: main vtable for NPC class
    this[0x14] = &PTR_LAB_00d65580;         // +0x50: secondary vtable (likely for an interface)

    this[0x16] = 0;                          // +0x58: pointer, set later from virtual call
    this[0x17] = 0;                          // +0x5C
    this[0x18] = 0;                          // +0x60
    this[0x19] = 0;                          // +0x64
    this[0x1A] = 0;                          // +0x68
    this[0x1B] = 0;                          // +0x6C
    this[0x1C] = 0;                          // +0x70
    this[0x1F] = DAT_00d5ccf8;               // +0x7C: global constant (e.g., game mode setting)
    this[0x29] = _DAT_00d5780c;              // +0xA4: global constant
    this[0x2A] = DAT_00d5d70c;               // +0xA8: global constant
    this[0x31] = _DAT_00d5cf70;              // +0xC4: global constant
    this[0x1D] = 0;                          // +0x74
    this[0x35] = 0;                          // +0xD4
    this[0x3A] = 0;                          // +0xE8: field initialized to 0, then OR with 1
    this[0x3A] = this[0x3A] | 1;             // set bit0, maybe a flag

    // Access a parent pointer stored at offset +0x48 (0x12 * 4)
    int *parentPtr = this[0x12] ? (int *)(this[0x12] - 0x48) : (int *)0x0;
    int uVar3; // will hold pointer from virtual call

    // Virtual call on parent object: vtable[4] (0x10/4)
    // Hash 0x369AC561 likely identifies a method (e.g., "getResourceHandle")
    // The second argument is a dummy local (initialized to extraData, then overwritten)
    extraData = 0;
    char result = (**(code **)(parentPtr[0] + 0x10))(0x369AC561, &extraData);
    // clang-format off
    // The result controls whether uVar3 gets a value from a register (unaff_retaddr) or 0.
    // This is likely a conditional assignment based on a register set by the virtual call.
    if (result != '\0') {
        // unaff_retaddr represents a register (e.g., EAX after the call, but return is char)
        // The decompiler could not resolve the actual source; we keep as is.
        uVar3 = (uint)unaff_retaddr; // Note: unaff_retaddr is a decompiler artifact
    } else {
        uVar3 = 0;
    }
    // clang-format on

    this[0x16] = uVar3;                     // +0x58: store pointer from virtual call
    this[0x1E] = uVar3 + 0x4B0;             // +0x78: derived address

    // Set a flag at offset 0x5C4 from the pointer: OR with 8
    *(uint *)(uVar3 + 0x5C4) = *(uint *)(uVar3 + 0x5C4) | 8;

    // Initialize many fields to zero (likely AI state, health, etc.)
    this[0x22] = 0;
    this[0x21] = 0;
    this[0x20] = 0;
    this[0x25] = 0;
    this[0x24] = 0;
    this[0x23] = 0;
    this[0x30] = 0;
    this[0x2F] = 0;
    this[0x2E] = 0;
    this[0x2D] = 0;
    this[0x2C] = 0;
    this[0x2B] = 0;
    this[0x28] = 0;
    this[0x27] = 0;
    this[0x26] = 0;
    this[0x34] = 0;
    this[0x33] = 0;
    this[0x32] = 0;

    // Set field at +0xDC to 3 (e.g., encounter type or LOD)
    this[0x37] = 3;

    // Allocate or acquire a resource if the pointer at +0x58 is non-null
    int resourceHandle = 0;
    if (this[0x16] != 0) {
        resourceHandle = FUN_0043b870(DAT_01131074); // DAT_01131074 likely global resource manager
    }
    this[0x36] = resourceHandle; // +0xD8

    if (resourceHandle != 0) {
        FUN_009b4270(); // Possibly initialize resource data or register callback
    }

    // Debug/trace call with identifier 0x45 (69)
    FUN_007f63e0(0x45);

    return this;
}