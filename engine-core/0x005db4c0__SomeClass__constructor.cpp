// FUNC_NAME: SomeClass::constructor
// Address: 0x005db4c0
// Role: Constructor for an EARS framework object. Initializes vtable pointer and zeros member fields, then calls a helper with an index derived from the object's address modulo a pool size.

void __thiscall SomeClass::constructor(void *this)
{
    uint32_t *obj = (uint32_t *)this;

    // Set vtable pointer at offset 0x00
    obj[0] = (uint32_t)&g_vtable_00e3f0b4; // vtable for SomeClass

    // Zero out member fields at offsets 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24
    obj[1] = 0; // offset +0x04
    obj[2] = 0; // offset +0x08
    obj[3] = 0; // offset +0x0C
    obj[4] = 0; // offset +0x10
    obj[5] = 0; // offset +0x14
    obj[6] = 0; // offset +0x18
    obj[7] = 0; // offset +0x1C
    obj[8] = 0; // offset +0x20
    obj[9] = 0; // offset +0x24

    // Call initialization helper with output references and a modulo-based index
    // DAT_01223398 is a global structure pointer; +0x04 gives a pool manager, then +0x08 gives the pool size
    uint32_t poolSize = *(uint32_t *)(*(uint32_t *)(DAT_01223398 + 0x04) + 0x08);
    uint32_t index = (uint32_t)this % poolSize;
    SomeHelper::initialize(&stackTemp1, &stackTemp2, index);
}