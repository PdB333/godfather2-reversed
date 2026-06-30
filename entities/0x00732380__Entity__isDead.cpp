// FUNC_NAME: Entity::isDead
int __fastcall Entity::isDead(int entity)
{
    // Access a global pointer to an array of structures (likely per-type data, each 0x1F30 bytes)
    uint* pTypeArray = *(uint**)(DAT_012233a0 + 4);
    uint typeIndex = (pTypeArray != 0) ? *pTypeArray : 0;

    uint typeFlags = typeIndex;
    if (pTypeArray == 0 || (typeFlags = typeIndex - 0x1F30, typeFlags == 0))
    {
        // If null or first type, clear lower byte
        typeFlags = typeFlags & 0xFFFFFF00;
    }
    else
    {
        // Read flags from type-specific data at offset 0x574
        uint rawFlags = *(uint*)(typeIndex + 0x574);
        typeFlags = (rawFlags >> 8) & 0xFFFFFF01;
    }

    uint highPart = typeFlags >> 8;  // Upper 24 bits (flags for other state)
    float health = *(float*)(entity + 0x2190);  // Health of this entity

    // Check death condition: health negative or health + threshold <= global death threshold
    bool isDead = (health < 0.0f) || (health + DAT_00d62b58 <= DAT_01205228);

    // Only return dead if the low byte of typeFlags is clear (meaning not already processed)
    if (isDead && (char)typeFlags == 0)
    {
        // Return value with low byte = 1 (dead flag set)
        return (highPart << 8) | 1;
    }
    else
    {
        // Return value with low byte = 0
        return highPart << 8;
    }
}