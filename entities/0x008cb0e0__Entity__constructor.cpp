// FUNC_NAME: Entity::constructor
undefined4* __thiscall Entity::constructor(undefined4* this, undefined4 entityManager, undefined4 entityId)
{
    undefined4 vtableResult;
    undefined1 local_20[12];
    undefined4 local_14;

    // Call base class constructor
    FUN_008cc220(entityManager, entityId);

    // Set vtable pointers for this class
    this[0x14] = &PTR_LAB_00d7c15c;  // +0x50: vtable for derived interface
    *(byte*)(this + 0x17) = *(byte*)(this + 0x17) & 0xfc;  // +0x5C: clear lower 2 bits (flags)
    this[0] = &PTR_FUN_00d7c240;     // +0x00: primary vtable
    this[3] = &PTR_LAB_00d7c230;     // +0x0C: secondary vtable
    this[0xB] = &PTR_FUN_00d7c21c;   // +0x2C: third vtable
    this[0x14] = &PTR_LAB_00d7c210;  // +0x50: final vtable override
    this[0x16] = 0;                  // +0x58: clear result field

    // Initialize global buffer (e.g., memory pool)
    FUN_004086b0(&DAT_012069d4, 0x1000);

    // Retrieve entity-specific data (e.g., handle from manager)
    FUN_008cae00(entityManager, entityId, local_20);
    this[0x15] = local_14;           // +0x54: store entity handle

    // Call virtual function on internal object (offset 0x08 from this[2]) at vtable slot 0x1c
    vtableResult = (**(code**)(**(int**)(this[2] + 8) + 0x1c))();
    this[0x16] = vtableResult;       // +0x58: store result (e.g., resource handle)

    return this;
}