// FUNC_NAME: ShaderEffect::cacheShaderConstantHandles
// Address: 0x005d8a30
// This function caches handles for two commonly used vertex shader constants.
// The 'this' pointer points to a ShaderEffect object embedded at offset 0xA0 within a container.
// The container's base holds a pointer to a shader manager (used for name-to-handle lookup).
void __fastcall ShaderEffect::cacheShaderConstantHandles(int thisPtr) {
    // shaderManager is at container base: container = thisPtr - 0xA0, then dereference the pointer stored at container+0x00
    void* shaderManager = *(void**)(thisPtr - 0xA0);

    // Store handle for "inColor" at thisPtr + 0x60 (relative to container: container + 0x100)
    *(int*)(thisPtr + 0x60) = getShaderConstantHandle(shaderManager, "inColor");

    // Store handle for "ModelViewProj" at thisPtr - 0x60 (relative to container: container + 0x40)
    *(int*)(thisPtr - 0x60) = getShaderConstantHandle(shaderManager, "ModelViewProj");
}