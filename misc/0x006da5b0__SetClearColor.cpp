// FUNC_NAME: SetClearColor
// Address: 0x006da5b0
// Role: Sets a hardcoded clear color (dark greenish) on the renderer via a singleton's virtual method.

void SetClearColor(void* renderer) {
    // Get the singleton object that owns the vtable function pointer.
    // The function at 0x009c8f80 returns a pointer to a singleton (e.g., RendererManager).
    void** singletonVtablePtr = reinterpret_cast<void**>(GetSomeSingleton());

    // Pack the color parameters: (red=2, green=0x10, blue=0)
    // These are stored as three consecutive ints.
    struct ColorParams {
        int r; // +0x00
        int g; // +0x04
        int b; // +0x08
    } colorParams;
    colorParams.r = 2;
    colorParams.g = 0x10;
    colorParams.b = 0;

    // Call the first virtual function on the singleton (index 0) with __thiscall convention.
    // The function takes the renderer as 'this' and a pointer to the color struct.
    typedef void (__thiscall* VirtualFunc)(void* renderer, ColorParams* params);
    VirtualFunc func = reinterpret_cast<VirtualFunc>(singletonVtablePtr[0]);
    func(renderer, &colorParams);
}