// FUNC_NAME: VisualObject::setColor
// Function address: 0x00926890
// Sets RGBA color with optional clamping. If useDefault is false, sets to default white.
// Offsets: +0x3b4 = r, +0x3b8 = g, +0x3bc = b, +0x3c0 = a

extern float g_defaultColor;   // DAT_00d5ccf8
extern float g_colorMax;       // _DAT_00d5780c (likely 1.0f)

void __thiscall VisualObject::setColor(bool useDefault, float r, float g, float b, float a)
{
    float temp = g_defaultColor;
    
    if (!useDefault) {
        // Set all components to default
        *(float *)(this + 0x3b4) = g_defaultColor;
        *(float *)(this + 0x3b8) = g_defaultColor;
        *(float *)(this + 0x3bc) = g_defaultColor;
        *(float *)(this + 0x3c0) = g_defaultColor;
        return;
    }
    
    // Clamp red
    if (r > 0.0f) {
        r = (r < g_colorMax) ? r : g_colorMax;
    } else {
        r = 0.0f;
    }
    *(float *)(this + 0x3b4) = r;
    
    // Clamp green (using param_5, which is b)
    if (b > 0.0f) {
        b = (b < g_colorMax) ? b : g_colorMax;
    } else {
        b = 0.0f;
    }
    *(float *)(this + 0x3b8) = b; // Note: offset 0x3b8 stores green? Actually order: r at 0x3b4, g at 0x3b8, b at 0x3bc, a at 0x3c0. But clamping uses param_5 for green? Code: if (param_5 >0) clamp and store at 0x3b8. So param_5 corresponds to green? Wait, param order: param_3 (r), param_4 (g?), param_5 (b?), param_6 (a). But decompiled code uses param_5 for 0x3b8, param_4 for 0x3bc. That's inconsistent with typical RGBA. Possibly they swapped g and b. Let's follow decompiled logic: 
    // param_3 -> 0x3b4 (r)
    // param_5 -> 0x3b8 (g)
    // param_4 -> 0x3bc (b)
    // param_6 -> 0x3c0 (a)
    // So the callers pass r, g, b, a but the function interprets r, b, g, a? Unlikely; maybe the decompiled param_4 and param_5 are swapped due to calling convention? We'll keep as is.
    // Actually in the decompiled code: 
    //   if (param_3 >0) clamp and store to 0x3b4
    //   if (param_5 >0) clamp and store to 0x3b8
    //   if (param_4 >0) clamp and store to 0x3bc
    //   if (param_6 >0) clamp and store to 0x3c0
    // So we'll treat param_3=r, param_5=g, param_4=b, param_6=a.
    
    // Clamp blue (using param_4)
    if (g > 0.0f) {  // param_4 is actually g in our naming? Wait, we assigned g to param_5? This is messy. Let's just use the original parameter names from decompiled and rename accordingly.
        // Better to keep param order as they appear: param_3, param_4, param_5, param_6.
        // So I'll rename: r = param_3, g = param_4, b = param_5, a = param_6.
        // Then offsets: r->0x3b4, g->0x3b8, b->0x3bc, a->0x3c0.
        // But the code uses param_5 for 0x3b8 and param_4 for 0x3bc. So there is a mismatch. Possibly the decompiler reversed the order. Let's assume the caller passes (r,g,b,a) and the function stores them as (r, g, b, a) but the code actually stores (r, b, g, a) because of swapped parameters. To be safe, I'll reconstruct the exact logic from the decompiled code.
    }
    
    // Given the confusion, I'll implement exactly as decompiled:
    // r = clamp(param_3) -> offset 0x3b4
    // g = clamp(param_5) -> offset 0x3b8
    // b = clamp(param_4) -> offset 0x3bc
    // a = clamp(param_6) -> offset 0x3c0
    
    // Re-do correctly:
}

// Alternative reconstruction (precise to decompiled):
void __thiscall VisualObject::setColor(bool useDefault, float param_3, float param_4, float param_5, float param_6)
{
    float defaultVal = g_defaultColor;
    if (!useDefault) {
        *(float *)(this + 0x3b4) = defaultVal;
        *(float *)(this + 0x3b8) = defaultVal;
        *(float *)(this + 0x3bc) = defaultVal;
        *(float *)(this + 0x3c0) = defaultVal;
        return;
    }
    float max = g_colorMax;
    // Red (stored at 0x3b4)
    if (param_3 > 0.0f) {
        param_3 = (param_3 < max) ? param_3 : max;
    } else {
        param_3 = 0.0f;
    }
    *(float *)(this + 0x3b4) = param_3;
    
    // Blue? (stored at 0x3b8) -> using param_5
    if (param_5 > 0.0f) {
        param_5 = (param_5 < max) ? param_5 : max;
    } else {
        param_5 = 0.0f;
    }
    *(float *)(this + 0x3b8) = param_5;
    
    // Green? (stored at 0x3bc) -> using param_4
    if (param_4 > 0.0f) {
        param_4 = (param_4 < max) ? param_4 : max;
    } else {
        param_4 = 0.0f;
    }
    *(float *)(this + 0x3bc) = param_4;
    
    // Alpha (stored at 0x3c0) -> using param_6
    if (param_6 > 0.0f) {
        param_6 = (param_6 < max) ? param_6 : max;
    } else {
        param_6 = 0.0f;
    }
    *(float *)(this + 0x3c0) = param_6;
}