// FUNC_NAME: NetReflectable::registerFields
// Address: 0x00959ac0
// Role: Registers all reflected fields for this object instance, binding them to global descriptors for networking/serialization.

void __thiscall NetReflectable::registerFields(void)
{
    // Register base class fields (likely from parent NetReflectable or similar)
    registerBaseClass();

    // Bind each field to its global descriptor
    // Offsets are relative to 'this' pointer
    bindField(&g_fieldDesc_0x50, this + 0x50, 4, 0, 0, 1);   // int field at +0x50
    bindField(&g_fieldDesc_0x54, this + 0x54, 4, 0, 0, 1);   // int field at +0x54
    bindField(&g_fieldDesc_0x58, this + 0x58, 4, 0, 0, 1);   // int field at +0x58
    bindField(&g_fieldDesc_0x5C, this + 0x5C, 4, 0, 0, 1);   // int field at +0x5C
    bindField(&g_fieldDesc_0x70, this + 0x70, 4, 0, 0, 0);   // int field at +0x70 (not networked?)
    bindField(&g_fieldDesc_0x70, this + 0x70, 4, 0, 0, 0);   // duplicate? Possibly a bug or intentional
    bindField(&g_fieldDesc_0x78, this + 0x78, 4, 0, 0, 0);   // int field at +0x78
    bindField(&g_fieldDesc_0x294, this + 0x294, 1, 0, 0, 0); // byte field at +0x294
    bindField(&g_fieldDesc_0x29C, this + 0x29C, 4, 0, 0, 0); // int field at +0x29C
    bindField(&g_fieldDesc_0x2A0, this + 0x2A0, 4, 0, 0, 0); // int field at +0x2A0
    bindField(&g_fieldDesc_0x2A4, this + 0x2A4, 4, 0, 0, 0); // int field at +0x2A4
    bindField(&g_fieldDesc_0x2A8, this + 0x2A8, 4, 0, 0, 0); // int field at +0x2A8
    bindField(&g_fieldDesc_0x210, this + 0x210, 5, 0, 0, 0); // 5-byte field at +0x210 (e.g., char[5] or struct)
    bindField(&g_fieldDesc_0x84, this + 0x84, 5, 0, 0, 0);   // 5-byte field at +0x84
    bindField(&g_fieldDesc_0x108, this + 0x108, 5, 0, 0, 0); // 5-byte field at +0x108
    bindField(&g_fieldDesc_0x18C, this + 0x18C, 5, &callback_0x959a90, 0, 0); // 5-byte field with callback
    bindField(&g_fieldDesc_0x2AC, this + 0x2AC, 2, 0, 0, 0); // short field at +0x2AC
    bindField(&g_fieldDesc_0x298, this + 0x298, 1, 0, 0, 0); // byte field at +0x298
    bindField(&g_fieldDesc_0x2C4, this + 0x2C4, 1, &callback_0x958580, 0, 0); // byte field with callback
}