// FUNC_NAME: DebugDrawManager::drawDebugBox
void DebugDrawManager::drawDebugBox(void *renderer, void *transform, void *object, uint color, int flag)
{
    // Called with param_3 = object, param_4 = color?, param_5 = flag
    // offsets on object:
    // +0x50-0x5c: 4 floats (probably color RGBA, original)
    // +0x60, +0x64, +0x68: 3 floats (probably translation XYZ)
    // +0x5c also used
    
    // Call some initialization (e.g., get world transform from object)
    FUN_00559fe0(object);
    
    // Read original color from object (off +0x60-0x68) - actually offset 0x60,0x64,0x68 are floats
    // But there is also local_20, local_1c, local_18 which come from +0x60, +0x64, +0x68
    // Those might be the object's world position?
    Vector3 pos;
    pos.x = *(float *)(object + 0x60);
    pos.y = *(float *)(object + 0x64);
    pos.z = *(float *)(object + 0x68);
    
    // Compute inverted color? (0.0f minus original) - DAT_00e44564 likely 0.0f
    float invR = 0.0f - *(float *)(object + 0x50);
    float invG = 0.0f - *(float *)(object + 0x54);
    float invB = 0.0f - *(float *)(object + 0x58);
    float invA = 0.0f - *(float *)(object + 0x5c);
    
    // Keep original color
    Vector4 origColor;
    origColor.r = *(float *)(object + 0x50);
    origColor.g = *(float *)(object + 0x54);
    origColor.b = *(float *)(object + 0x58);
    origColor.a = *(float *)(object + 0x5c);
    
    // Build debug draw command structures on stack
    // local_e0 points to PTR_LAB_00dcf980 - likely a vtable for debug draw command
    void *vtable1 = &PTR_LAB_00dcf980;
    uint color1 = DAT_00e445dc;  // some default color?
    void *extra = color; // param_4
    
    if (flag != 0) {
        void *vtable2 = &PTR_LAB_00dcf980;
        uint color2 = DAT_00e445dc;
        Vector3 pos2;
        pos2.x = *(float *)(object + 0x50);  // reuse original color? actually offset 0x50 is color.r, so pos2 uses color values? That seems wrong.
        pos2.y = *(float *)(object + 0x54);
        pos2.z = *(float *)(object + 0x58);
        // And local_94 = local_c4 = original alpha? Actually local_94 = local_c4, which was from +0x5c.
        float alpha2 = *(float *)(object + 0x5c);
        // Pack into a second structure
        // But buffer over local_80 is used
        char buffer[80]; // local_80
        // Two command structures: &local_e0 and &local_b0
        FUN_00c09ee0(renderer, transform, buffer, &vtable1, &vtable2);
        return;
    }
    char buffer[80];
    FUN_00c09ee0(renderer, transform, buffer, &vtable1, 0);
    return;
}