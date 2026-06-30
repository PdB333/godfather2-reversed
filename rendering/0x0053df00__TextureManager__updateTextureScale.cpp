// FUNC_NAME: TextureManager::updateTextureScale
void TextureManager::updateTextureScale(void)
{
    undefined1 *puVar1;
    uint unaff_ESI;
    undefined4 local_20; // +0x00: x
    undefined4 local_1c; // +0x04: y
    float local_18;      // +0x08: scaleX
    float local_14;      // +0x0c: scaleY
    
    // Check if texture reload is needed (DAT_01198ecc / DAT_0121bf30 * 0x1b)
    if ((&DAT_01198ecc)[DAT_0121bf30 * 0x1b] != 0) {
        FUN_006063b0(); // reloadTextureResources()
    }
    
    // If texture size info is available (DAT_01198ee4 at same offset)
    if ((&DAT_01198ee4)[DAT_0121bf30 * 0x1b] != 0) {
        local_20 = 0; // reset destination coords
        local_1c = 0;
        
        // Get texture info entry (0x38 byte struct per texture, max 4096 entries)
        if (unaff_ESI < 0x1000) {
            puVar1 = &DAT_011a0f28 + unaff_ESI * 0x38;
        }
        else {
            puVar1 = (undefined1 *)0x0;
        }
        
        // Calculate scale: base resolution / texture width
        local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 2); // +0x02: width
        
        if (unaff_ESI < 0x1000) {
            puVar1 = &DAT_011a0f28 + unaff_ESI * 0x38;
        }
        else {
            puVar1 = (undefined1 *)0x0;
        }
        
        // Calculate scale: base resolution / texture height
        local_14 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 4); // +0x04: height
        
        // Update texture scale in renderer
        FUN_0060add0(DAT_0121be9c, (&DAT_01198ee4)[DAT_0121bf30 * 0x1b], &local_20);
    }
    return;
}