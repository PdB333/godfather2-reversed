// FUNC_NAME: TextureAttributeManager::registerAttributeStrings
void TextureAttributeManager::registerAttributeStrings(void)
{
    // Register string identifiers for texture attributes.
    // These are used to map attribute names to internal IDs via FUN_00ab8560.
    // The strings correspond to D3D or platform-specific texture format properties.
    gFormatStringId = FUN_00ab8560(0, "format", 6);           // +0x011f41fc
    gDxtStringId = FUN_00ab8560(0, &DAT_00e40ec8, 4);        // likely "dxt1" (4 bytes) +0x011f4200
    gMipmapStringId = FUN_00ab8560(0, "mipmap", 6);          // +0x011f4204
    gBigEndianStringId = FUN_00ab8560(0, "big_endian", 10);  // +0x011f4208
    gTiledStringId = FUN_00ab8560(0, "tiled", 5);            // +0x011f420c
    gFilterStringId = FUN_00ab8560(0, "filter", 6);          // +0x011f4210
    gCubeMapStringId = FUN_00ab8560(0, &DAT_00e40ef4, 4);    // likely "cube" (4 bytes) +0x011f4214
    gVertexTextureStringId = FUN_00ab8560(0, "vertex_texture", 14); // +0x011f4218
    gColorSpaceStringId = FUN_00ab8560(0, "color_space", 11); // +0x011f421c

    // Allocate a descriptor object (size 0x2C = 44 bytes) to hold attribute data.
    TextureAttributeRecord* record = (TextureAttributeRecord*)FUN_009c8e50(0x2C);
    if (record != nullptr)
    {
        // Initialize record fields (offsets relative to struct base)
        record->field_04 = 0;                    // +0x04
        record->field_10 = 0;                    // +0x10
        record->vtablePtr = &PTR_FUN_00e2f19c;   // +0x08, initially set
        record->field_0C = 1;                    // +0x0C
        record->dataPtr = &PTR_LAB_00e40f38;     // +0x14
        record->baseVtable = &PTR_FUN_00e40f18;  // +0x00
        record->vtablePtr = &PTR_LAB_00e40f24;   // +0x08 (overwritten)
        record->dataPtr = &PTR_LAB_00e40f34;     // +0x14 (overwritten)
        record->field_20 = 0;                    // +0x20
        record->field_24 = 0;                    // +0x24
        record->field_28 = 0;                    // +0x28

        gTextureAttributeRecord = record;        // _DAT_01223558
    }

    // Complete initialization (likely sets up additional internal state).
    FUN_00619c20();
    return;
}