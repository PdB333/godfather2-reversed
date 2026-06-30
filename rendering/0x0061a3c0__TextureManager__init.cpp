// FUNC_NAME: TextureManager::init
void TextureManager::init(void)
{
    // Register string identifiers for texture attributes
    DAT_011f41fc = FUN_00ab8560(0, "format", 6);           // +0x0: format string ID
    DAT_011f4200 = FUN_00ab8560(0, &DAT_00e40ec8, 4);      // +0x4: unknown attribute (string at 0xe40ec8)
    DAT_011f4204 = FUN_00ab8560(0, "mipmap", 6);           // +0x8: mipmap string ID
    DAT_011f4208 = FUN_00ab8560(0, "big_endian", 10);      // +0xc: big_endian string ID
    DAT_011f420c = FUN_00ab8560(0, "tiled", 5);            // +0x10: tiled string ID
    DAT_011f4210 = FUN_00ab8560(0, "filter", 6);           // +0x14: filter string ID
    DAT_011f4214 = FUN_00ab8560(0, &DAT_00e40ef4, 4);      // +0x18: unknown attribute (string at 0xe40ef4)
    DAT_011f4218 = FUN_00ab8560(0, "vertex_texture", 14);  // +0x1c: vertex_texture string ID
    DAT_011f421c = FUN_00ab8560(0, "color_space", 11);     // +0x20: color_space string ID

    // Allocate texture parameter manager structure (0x2C bytes)
    TextureParameterManager* paramMgr = (TextureParameterManager*)FUN_009c8e50(0x2C);
    if (paramMgr != NULL)
    {
        // Initialize structure
        paramMgr->field_0x04 = 0;                           // +0x04: unused?
        paramMgr->field_0x10 = 0;                           // +0x10: some counter/state
        paramMgr->vtbl = &PTR_FUN_00e40f18;                 // +0x08: virtual function table (overwritten)
        paramMgr->refCount = 1;                             // +0x0c: reference count
        paramMgr->field_0x14 = &PTR_LAB_00e40f38;           // +0x14: some pointer (overwritten)
        paramMgr->field_0x00 = &PTR_FUN_00e40f18;          // +0x00: vtable pointer (first field)
        paramMgr->vtbl = &PTR_LAB_00e40f24;                // +0x08: overwrite vtbl
        paramMgr->field_0x14 = &PTR_LAB_00e40f34;          // +0x14: overwrite
        paramMgr->field_0x20 = 0;                           // +0x20: zero
        paramMgr->field_0x24 = 0;                           // +0x24: zero
        paramMgr->field_0x28 = 0;                           // +0x28: zero

        _DAT_01223558 = paramMgr;                           // Store globally
    }

    FUN_00619c20(); // Continue initialization
}