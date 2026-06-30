// FUNC_NAME: Renderer::applyShaderConstants
// Function address: 0x0055d970
// Role: Applies shader constants (lighting/color) and triggers cinematic effect if a scene flag is set.
// Uses ESI as this (Renderer*), EDI as scene pointer (Scene*).
// Reads color from this+0x30 (Vec3f) and global ambient color, prepares a 60-byte transform and 16-byte output.

void Renderer::applyShaderConstants(Scene* scene) __thiscall {
    // Stack allocations
    struct TransformData {
        float data[15]; // 60 bytes (e.g., view-projection matrix + camera pos?)
    } transform; // local_40 (60 bytes)
    
    struct Color {
        float r, g, b, a; // 16 bytes
    } color; // local_50 (16 bytes)
    
    // Extract RGB from this object (maybe material color?)
    Vec3f materialColor = *(Vec3f*)(this + 0x30); // +0x30: r, g, b (3 floats)
    float alpha = *(float*)(this + 0x38);          // +0x38: fourth component? Actually local_58 = this+0x38, but assigns to local_58 which is part of local_60 struct. So local_60,5c,58 are three floats (r,g,b?) and local_54 is a global. Let's restructure.

    // Actually local_60 = this+0x30 (r), local_5c = this+0x34 (g), local_58 = this+0x38 (b?), local_54 = DAT_00e2b1a4 (alpha or specular?)
    // But wait, local_60 is declared as undefined4, so that's 4 bytes. So we have:
    Color inputColor;
    inputColor.r = *(float*)(this + 0x30);
    inputColor.g = *(float*)(this + 0x34);
    inputColor.b = *(float*)(this + 0x38);
    inputColor.a = *(float*)(&DAT_00e2b1a4); // global constant (e.g., ambient intensity)
    
    // First call: push matrix stack or something
    maybePushMatrix(); // FUN_004b59d0
    
    // Second call: retrieve a transform (e.g., view-projection matrix) into transform (60 bytes)
    getSceneTransform(&transform); // FUN_00aa3930
    
    // Check scene flag at scene+0x18 then +0xD8 for value 0x07 (e.g., cinematic enabled)
    if (*(char*)(*(int*)(scene + 0x18) + 0xD8) == 0x07) {
        setRenderState(1, 1, 0); // FUN_009f4240 — maybe enable some post-processing
    }
    
    // Write the color constant to a shader parameter (address of inputColor as source, color buffer as output)
    setShaderConstant(&inputColor, &color); // FUN_009f4ca0 — copies 16 bytes?
    
    return;
}