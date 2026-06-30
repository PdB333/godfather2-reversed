// FUNC_NAME: BoxLightEffect::initializeShaderHandles
void __thiscall BoxLightEffect::initializeShaderHandles()
{
    // Store self pointer at offset 0x1C0 (likely used by derived classes or inline assembly)
    *(uint32_t*)(this + 0x1C0) = (uint32_t)this;

    // Get the shader effect handle from a global singleton (e.g., ShaderEffectManager)
    // FUN_0060a2e0 likely returns a handle to the "box light" effect
    uint32_t effectHandle = ShaderEffectManager::getEffectHandle(&PTR_DAT_0110a10c);
    *(uint32_t*)(this + 0x14) = effectHandle;

    // Call base class initialization or global setup (FUN_004907a0)
    ShaderEffect::baseInitialize();

    // Acquire shader constant handles by name for the box light effect
    // Offsets with comments:
    // +0x1C4: g_boxLightInvMtx constant handle (inverse matrix)
    // +0x210: g_boxLightFBScale constant handle (framebuffer scale)
    // +0x230: g_boxLightFBOffset constant handle (framebuffer offset)
    *(uint32_t*)(this + 0x1C4) = ShaderEffect::getConstantHandle(effectHandle, "g_boxLightInvMtx");
    *(uint32_t*)(this + 0x210) = ShaderEffect::getConstantHandle(effectHandle, "g_boxLightFBScale");
    *(uint32_t*)(this + 0x230) = ShaderEffect::getConstantHandle(effectHandle, "g_boxLightFBOffset");
}