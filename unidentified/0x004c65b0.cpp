// FUN_004c65b0: Material::assignShadowSamplers

void __thiscall Material::assignShadowSamplers(void *this, void *renderDevice)
{
    // Global array of 5 shadow sampler descriptors (offset from this pointer computed as &g_shadowSamplers[0] - this)
    extern void* g_shadowSamplers[5]; // Originally PTR_s_g_shadowSampler_011286b4

    // Iterate over 5 shadow sampler slots, storing handles into consecutive fields (offsets 0x00, 0x04, 0x08, 0x0C, 0x10)
    for (int i = 0; i < 5; ++i)
    {
        // Acquire a sampler object from the render device using the global descriptor
        void* samplerHandle = FUN_0060a580(renderDevice, g_shadowSamplers[i]);
        // Store the handle into the material's sampler slot
        *(int*)((char*)this + i * 4) = (int)samplerHandle;
    }
}