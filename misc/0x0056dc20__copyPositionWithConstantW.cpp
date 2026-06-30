// FUNC_NAME: copyPositionWithConstantW
void copyPositionWithConstantW(void* param_this, void* param_data) {
    // Call helper to resolve pointers (likely returns ECX as this, EDX as data)
    FUN_0056cef0(param_this, param_data);
    
    // Source: data +0x10 (Vector4 field)
    float srcX = *(float*)((char*)extraout_EDX + 0x10);
    float srcY = *(float*)((char*)extraout_EDX + 0x14);
    float srcZ = *(float*)((char*)extraout_EDX + 0x18);
    float srcW = *(float*)((char*)extraout_EDX + 0x1c);
    
    // Destination: this +0x30 (Vector4 position field)
    *(float*)((char*)extraout_ECX + 0x30) = srcX;
    *(float*)((char*)extraout_ECX + 0x34) = srcY;
    *(float*)((char*)extraout_ECX + 0x38) = srcZ;
    // W component initially copied, then overwritten with global constant
    *(float*)((char*)extraout_ECX + 0x3c) = srcW;
    *(float*)((char*)extraout_ECX + 0x3c) = DAT_00e2b1a4; // e.g., 1.0f
}