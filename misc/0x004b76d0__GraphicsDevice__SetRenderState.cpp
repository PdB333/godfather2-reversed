// FUNC_NAME: GraphicsDevice::SetRenderState
struct RenderStateParams {
    int mode;   // +0x00 (local_c)
    int value;  // +0x04 (local_8)
    int flags;  // +0x08 (local_4)
};

// Returns singleton GraphicsDevice* (FUN_009c8f80)
extern GraphicsDevice* GetGraphicsDevice(void);

void GraphicsDevice::SetRenderState(void)
{
    GraphicsDevice* device = GetGraphicsDevice(); // puVar1
    RenderStateParams params;
    params.mode  = 2;   // local_c
    params.value = 0x10; // local_8
    params.flags = 0;    // local_4

    // Call virtual function at vtable[0]: SetRenderState(0xC0, &params)
    // This sets a render state (0xC0 = 192, custom engine constant) with the given parameters
    (*(void (__thiscall**)(GraphicsDevice*, unsigned int, RenderStateParams*))(*device)->vtable[0])(device, 0xC0, &params);
}