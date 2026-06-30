// FUNC_NAME: DebugRenderer::drawDebugMarker
void DebugRenderer::drawDebugMarker(void* renderer, void* device, int object, int param4, int param5)
{
    // object is a pointer to some game object with position/rotation data
    // Offsets: +0x50 = position.x, +0x54 = position.y, +0x58 = position.z, +0x5c = position.w (or rotation)
    // +0x60 = some vector component, +0x68 = another, +0x64 = another
    // Global DAT_00e44564 is likely camera position offset (worldToScreen)
    // Global DAT_00e445dc is likely debug color (e.g., 0xFFFFFFFF white)
    // PTR_LAB_00dcf980 is a vtable or function table for debug rendering

    setupDebugMarker(object); // FUN_00559fe0

    // Extract original position and other data from object
    float posX = *(float*)(object + 0x50);
    float posY = *(float*)(object + 0x54);
    float posZ = *(float*)(object + 0x58);
    float posW = *(float*)(object + 0x5c);
    float extra0 = *(float*)(object + 0x60);
    float extra1 = *(float*)(object + 0x68);
    float extra2 = *(float*)(object + 0x64); // 100 decimal

    // Compute camera-relative positions
    float relX = DAT_00e44564 - posX;
    float relY = DAT_00e44564 - posY;
    float relZ = DAT_00e44564 - posZ;
    float relW = DAT_00e44564 - posW;

    // Build first parameter structure (local_e0)
    struct DebugDrawParams1 {
        void** vtable; // PTR_LAB_00dcf980
        uint32_t color; // DAT_00e445dc
        float posX;
        float posY;
        float posZ;
        float posW;
        uint32_t param4; // passed in
    } params1;
    params1.vtable = &PTR_LAB_00dcf980;
    params1.color = DAT_00e445dc;
    params1.posX = posX;
    params1.posY = posY;
    params1.posZ = posZ;
    params1.posW = posW;
    params1.param4 = param4;

    // Build second parameter structure (local_b0) only if param5 != 0
    struct DebugDrawParams2 {
        void** vtable; // PTR_LAB_00dcf980
        uint32_t color; // DAT_00e445dc
        float posX;
        float posY;
        float posZ;
        float posW;
        int param5; // passed in
    } params2;
    if (param5 != 0) {
        params2.vtable = &PTR_LAB_00dcf980;
        params2.color = DAT_00e445dc;
        params2.posX = posX;
        params2.posY = posY;
        params2.posZ = posZ;
        params2.posW = posW;
        params2.param5 = param5;
        FUN_00c09ee0(device, renderer, local_80, &params1, &params2);
    } else {
        FUN_00c09ee0(device, renderer, local_80, &params1, 0);
    }
}