// FUNC_NAME: UIManager::setupSprite
void UIManager::setupSprite(uint index, float scaleX, float scaleY, float scaleZ, float scaleW)
{
    // Lookup a value from a table of ushorts (likely sprite sheet coordinates or size)
    ushort tableValue = *(ushort *)(&DAT_011f38f4 + index * 2);
    // This call might set up texture/UV or load something
    FUN_006066e0(tableValue);

    // Global array of 0x18-byte sprite structures (offset +0x00 = x, +0x04 = y, +0x08 = z, +0x0c = w, +0x10 = unused, +0x14 = color/alpha)
    int spriteIndex = DAT_012058b0 * 0x18; // Each sprite struct is 24 bytes
    int *spriteArray = (int *)&DAT_011f3918;

    // Set sprite position/scaling (x and z use the raw index, y and w use tableValue)
    spriteArray[spriteIndex / 4 + 0] = (int)((float)(index & 0xffff) * scaleX);       // +0x00
    spriteArray[spriteIndex / 4 + 1] = (int)((float)tableValue * scaleY);              // +0x04
    spriteArray[spriteIndex / 4 + 2] = (int)((float)(index & 0xffff) * scaleZ);        // +0x08
    spriteArray[spriteIndex / 4 + 3] = (int)((float)tableValue * scaleW);              // +0x0c
    spriteArray[spriteIndex / 4 + 4] = 0;                                              // +0x10 (unused/cleared)
    spriteArray[spriteIndex / 4 + 5] = DAT_00e2b1a4;                                   // +0x14 (constant color or alpha)

    // Set color/alpha for the sprite (perhaps set to opaque white)
    FUN_00609500((int)((float)tableValue * scaleW), 0x3f800000); // 1.0f, i.e., fully opaque
}