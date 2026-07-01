// FUNC_NAME: Entity::Entity
// Function address: 0x00795720
// Constructor for base Entity class. Initializes vtable, zeroes fields, sets default values.

Entity * __thiscall Entity::Entity(Entity *this, int param2) {
    // Base class constructor
    EntityBase::EntityBase(param2); // FUN_005418b0

    // Set vtable pointer
    *this = (Entity)&PTR_FUN_00d6a2a8; // +0x00 vtable

    // Function pointers for derived behavior
    this->vtable[0x0F] = (void*)&PTR_LAB_00d6a298; // +0x3C (0x0F*4)
    this->vtable[0x12] = (void*)&PTR_LAB_00d6a294; // +0x48
    this->vtable[0x14] = (void*)&PTR_LAB_00d6a290; // +0x50
    this->vtable[0x15] = (void*)&PTR_LAB_00d6a230; // +0x54
    this->vtable[0x16] = (void*)&PTR_LAB_00d6a1c8; // +0x58

    // Zero out pairs of shorts that form 32-bit fields (offsets: 0x278, 0x27A; 0x280, 0x282; etc.)
    *(short *)((int)this + 0x278) = 0;
    *(short *)((int)this + 0x27A) = 0;
    *(short *)((int)this + 0x280) = 0;
    *(short *)((int)this + 0x282) = 0;
    *(short *)((int)this + 0x288) = 0; // inferred from 0xa2*4
    *(short *)((int)this + 0x28A) = 0;
    *(short *)((int)this + 0x290) = 0;
    *(short *)((int)this + 0x292) = 0;
    *(short *)((int)this + 0x298) = 0;
    *(short *)((int)this + 0x29A) = 0;
    *(short *)((int)this + 0x2A0) = 0;
    *(short *)((int)this + 0x2A2) = 0;

    // Set default global values
    int g1 = DAT_00d5ccf8;   // global int
    int g2 = _DAT_00d5780c;  // global short? actually int
    this->field_0x2AC = g1;  // +0x2AC
    this->field_0x2A4 = 0;   // +0x2A4
    this->field_0x2A8 = 0;   // +0x2A8
    this->field_0x2B0 = 0;   // +0x2B0
    this->field_0x2B4 = 0;   // +0x2B4
    this->field_0x2B8 = 2;   // +0x2B8 (some default)
    this->field_0x2BC = 0;   // +0x2BC
    this->field_0x30C = g2;  // +0x30C (0xC3*4)
    this->field_0x2DC = 0;   // +0x2DC
    this->field_0x2EC = 0;   // +0x2EC
    this->field_0x2FC = 0;   // +0x2FC
    int g3 = DAT_00d5eff8;
    this->field_0x314 = g3;  // +0x314 (0xC5*4)
    this->field_0x318 = _DAT_00d5cf70; // +0x318
    this->field_0x31C = _DAT_00d5cf70; // +0x31C? Actually param_1[199] = uVar1; 199*4=0x31C
    int g4 = DAT_00d5eeec;
    this->field_0x310 = g3;  // +0x310 (0xC4*4)
    this->field_0x320 = 0;   // +0x320 (200*4)
    this->field_0x324 = g4;  // +0x324 (0xC9*4)
    this->field_0x328 = g4;  // +0x328
    this->field_0x32C = 0;
    this->field_0x330 = 0;
    this->field_0x334 = 0;
    this->field_0x348 = 0;
    this->field_0x34C = 0;
    this->field_0x390 = 0;
    this->field_0x394 = 0;
    this->field_0x39C = 1;   // +0x39C (0xE7*4)
    this->field_0x3A0 = 0;   // +0x3A0
    this->field_0x398 = &PTR_FUN_00d6a414; // +0x398 function pointer
    this->field_0x3A4 = 0;
    this->field_0x3A8 = 0;
    this->field_0x3AC = 0;
    this->field_0x3B0 = 0;
    this->field_0x3B4 = 0;
    this->field_0x3B8 = 0;
    this->field_0x3BC = 0;
    this->field_0x3C0 = 0;
    this->field_0x3C4 = 0;
    this->field_0x3C8 = 0;
    // More zeroing of 32-bit fields (from 0x9C to 0x10A)
    for (int i = 0x9C; i <= 0x10A; i++) {
        *(uint *)((int)this + i*4) = 0; // Actually many are set individually, but simplified
    }
    // Remaining individual zero assignments from the original
    this->field_0x270 = 0;   // 0x9C*4
    this->field_0x274 = 0;   // 0x9D*4
    this->field_0x27C = 0;   // 0x9F*4
    this->field_0x284 = 0;   // 0xA1*4
    this->field_0x28C = 0;   // 0xA3*4
    this->field_0x294 = 0;   // 0xA5*4
    this->field_0x29C = 0;   // 0xA7*4
    this->field_0x2BC = 0;   // 0xAF*4
    this->field_0x344 = 0;   // 0xD1*4
    this->field_0x340 = 0;   // 0xD0*4
    this->field_0x33C = 0;   // 0xCF*4
    this->field_0x338 = 0;   // 0xCE*4
    this->field_0x418 = 0;   // 0x106*4
    this->field_0x414 = 0;   // 0x105*4
    this->field_0x410 = 0;   // 0x104*4
    this->field_0x40C = 0;   // 0x103*4
    this->field_0x408 = 0;   // 0x102*4
    this->field_0x404 = 0;   // 0x101*4
    this->field_0x400 = 0;   // 0x100*4
    this->field_byte_0x428 = 0; // *(undefined1 *)(param_1 + 0x10a) = 0; at byte offset 0x428? Actually 0x10A*4=0x428
    // Another group of 32-bit zeroing (0xD4 to 0xE3)
    this->field_0x35C = 0;   // 0xD7*4
    this->field_0x358 = 0;   // 0xD6*4
    this->field_0x354 = 0;   // 0xD5*4
    this->field_0x350 = 0;   // 0xD4*4
    this->field_0x36C = 0;   // 0xDB*4
    this->field_0x368 = 0;   // 0xDA*4
    this->field_0x364 = 0;   // 0xD9*4
    this->field_0x360 = 0;   // 0xD8*4
    this->field_0x37C = 0;   // 0xDF*4
    this->field_0x378 = 0;   // 0xDE*4
    this->field_0x374 = 0;   // 0xDD*4
    this->field_0x370 = 0;   // 0xDC*4
    this->field_0x38C = 0;   // 0xE3*4
    this->field_0x388 = 0;   // 0xE2*4
    this->field_0x384 = 0;   // 0xE1*4
    this->field_0x380 = 0;   // 0xE0*4

    return this;
}