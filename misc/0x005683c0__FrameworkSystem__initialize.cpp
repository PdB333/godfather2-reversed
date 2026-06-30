// FUNC_NAME: FrameworkSystem::initialize
void FrameworkSystem::initialize(void)
{
    // +0x34: pointer to a factory/manager object (e.g., DeviceFactory)
    // +0x8: pointer to a device (e.g., GraphicsDevice)
    // +0x30: pointer to a renderer or secondary device
    // +0xc: pointer to a subsystem manager (e.g., AudioManager)
    int* factory = *(int**)(this + 0x34);
    // Call virtual function at vtable offset 0x3c (factory method) to create a device
    int device = (**(code**)(*factory + 0x3c))();
    *(int*)(this + 0x8) = device;

    // Helper initialization (likely sets up internal state)
    FUN_005684b0();

    // Call virtual function at index 100 (0x64) on the device (e.g., initialize)
    (**(code**)(**(int**)(this + 0x8) + 100))();

    // Call virtual function at index 144 (0x90) on the device (e.g., getRenderer)
    int renderer = (**(code**)(**(int**)(this + 0x8) + 0x90))();
    *(int*)(this + 0x30) = renderer;

    // Call virtual function at vtable offset 0x24 on the factory to get a subsystem manager
    int* manager = (int*)(**(code**)(*factory + 0x24))();
    *(int**)(this + 0xc) = manager;

    // Call virtual function at index 116 (0x74) on the manager with argument 1 (e.g., setActive)
    (**(code**)(*manager + 0x74))(1);

    return;
}