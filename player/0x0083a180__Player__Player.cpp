// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(undefined4 *this, undefined4 initData) {
    // Call base class constructor (likely Entity::Entity or SimNpc::SimNpc)
    FUN_008ba220(initData);
    
    // Set vtable pointers for multiple inheritance:
    // +0x00: Primary vtable (PTR_FUN_00d73e98)
    *this = &PTR_FUN_00d73e98;
    // +0x3C: Secondary vtable (interface A)
    this[0xf] = &PTR_LAB_00d73e88;
    // +0x48: Secondary vtable (interface B)
    this[0x12] = &PTR_LAB_00d73e84;
    // +0x50: Secondary vtable (interface C)
    this[0x14] = &PTR_LAB_00d73e80;
    // +0x54: Secondary vtable (interface D)
    this[0x15] = &PTR_LAB_00d73e20;
    // +0x58: Secondary vtable (interface E)
    this[0x16] = &PTR_LAB_00d73db8;
    // +0x180: Another vtable (likely for net reflection or action handling)
    this[0x60] = &PTR_LAB_00d73da4;
    
    // Initialize three groups of (int, short, short) at offsets 0x290-0x2A7.
    // Likely an array of 3 items, each with an ID and two 16-bit values (e.g., ammo, status).
    // Group 0: +0x290 (int), +0x294 (short), +0x296 (short)
    this[0xa4] = 0;                                   // int field at +0x290
    *(undefined2 *)((int)this + 0x294) = 0;           // short field at +0x294
    *(undefined2 *)((int)this + 0x296) = 0;           // short field at +0x296
    
    // Group 1: +0x298 (int), +0x29C (short), +0x29E (short)
    this[0xa6] = 0;                                   // int field at +0x298
    *(undefined2 *)((int)this + 0x29c) = 0;           // short field at +0x29C
    *(undefined2 *)((int)this + 0x29e) = 0;           // short field at +0x29E
    
    // Group 2: +0x2A0 (int), +0x2A4 (short), +0x2A6 (short)
    this[0xa8] = 0;                                   // int field at +0x2A0
    *(undefined2 *)((int)this + 0x2a4) = 0;           // short field at +0x2A4
    *(undefined2 *)((int)this + 0x2a6) = 0;           // short field at +0x2A6
    
    return this;
}