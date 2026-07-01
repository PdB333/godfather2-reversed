// FUNC_NAME: createResourceFromVirtualFactory
// Function at 0x008319f0: Uses a global singleton to call a virtual factory method (first vtable entry)
// with parameters (0xa0, pointer to struct containing {2, 0x10, 0}) then creates object if successful.
// Likely part of EARS resource/factory system (e.g., creating textures, buffers, or game objects).

int createResourceFromVirtualFactory(void)
{
    // Get singleton manager (e.g., ResourceManager / GraphicsDevice / ObjectFactory)
    void** manager = reinterpret_cast<void**>(FUN_009c8f80());

    // Allocation/creation parameters: unknown meaning (maybe {type, width, height} or format flags)
    struct CreationParams {
        int field0; // +0x00: e.g., type or width (value 2)
        int field4; // +0x04: e.g., version or height (value 0x10)
        int field8; // +0x08: e.g., flags or stride (value 0)
    } params;
    params.field0 = 2;
    params.field4 = 0x10;
    params.field8 = 0;

    // Call first virtual method on the singleton (vtable[0]) with:
    //   arg1 = 0xa0 (resource type ID or size hint)
    //   arg2 = &params (creation details)
    // This is __thiscall, but the code uses a function pointer call directly (assuming C++ mangling or manual vtable dispatch)
    typedef int (__thiscall* VirtualFactoryFunc)(void* thisptr, int, void*);
    VirtualFactoryFunc factoryMethod = (VirtualFactoryFunc)(*manager); // First vtable entry
    int result = factoryMethod(manager, 0xa0, &params);

    // If allocation/creation succeeded, call a separate constructor/initializer
    if (result != 0) {
        return FUN_00831850(); // Returns handle/pointer to the new object
    }
    return 0; // Failure
}