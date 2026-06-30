// FUNC_NAME: unknownObjectInit
// Function at 0x006d9ee0: Constructor/initializer for an unknown game object
// Likely a base class constructor called from multiple derived constructors.

void __thiscall unknownObjectInit(void *this)
{
    // +0x00: vtable pointer
    *(void**)this = (void*)&PTR_FUN_00d5f5b0;
    // +0x04: unknown int, zeroed
    *(int*)((uint)this + 0x04) = 0;
    // +0x08: byte, set to 0
    *(byte*)((uint)this + 0x08) = 0;
    // +0x0C: some ID or flag, set to 0xFF
    *(int*)((uint)this + 0x0C) = 0xFF;
    // +0x10, +0x14: zeroed
    *(int*)((uint)this + 0x10) = 0;
    *(int*)((uint)this + 0x14) = 0;
    // +0x20: pointer to a global singleton (likely InputManager or similar)
    *(int*)((uint)this + 0x20) = DAT_00d5e288;
    // Cache global pointers for repeated assignments
    int gPtr1 = _DAT_00d5780c;      // e.g., AudioManager
    int gPtr2 = _DAT_00d5cf70;      // e.g., some other manager
    // +0x24, +0x28, +0x2C: store pointers
    *(int*)((uint)this + 0x24) = gPtr1;
    *(int*)((uint)this + 0x28) = gPtr2;
    *(int*)((uint)this + 0x2C) = gPtr2;
    // +0x30 through +0x3C: zeroed (four ints)
    *(int*)((uint)this + 0x30) = 0;
    *(int*)((uint)this + 0x34) = 0;
    *(int*)((uint)this + 0x38) = 0;
    *(int*)((uint)this + 0x3C) = 0;
    // +0x40: zeroed
    *(int*)((uint)this + 0x40) = 0;
    // +0x50, +0x54: duplicate of gPtr1
    *(int*)((uint)this + 0x50) = gPtr1;
    *(int*)((uint)this + 0x54) = gPtr1;
    // +0x58: zeroed
    *(int*)((uint)this + 0x58) = 0;
}