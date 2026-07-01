// FUNC_NAME: getEntityColor

// Retrieves the color associated with an entity handle (param_2). 
// Defaults to opaque white (0xFFFFFFFF). If the entity exists, 
// its color at offset 0xF8 (likely mColor) is returned via param_1.

uint32_t* getEntityColor(uint32_t* outColor, uint32_t entityHandle)
{
    // Set default color to opaque white (ARGB)
    *((uint8_t*)outColor + 0) = 0xFF;
    *((uint8_t*)outColor + 1) = 0xFF;
    *((uint8_t*)outColor + 2) = 0xFF;
    *((uint8_t*)outColor + 3) = 0xFF;

    // Look up entity by handle (calls generic entity resolver at 0x008c7490)
    uint32_t* entity = FUN_008c7490(entityHandle);
    if (entity != nullptr)
    {
        // Entity exists, overwrite with its stored color at offset 0xF8
        *outColor = *(entity + 0x3E); // 0xF8 / 4 = 0x3E (assuming 4-byte words)
        // But note: the original code uses byte pointer arithmetic, so offset 0xF8 from base.
    }

    return outColor;
}