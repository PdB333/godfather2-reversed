// FUNC_NAME: Engine::initialize
Engine* Engine::initialize() {
    // Call base initialization (likely memory allocation or parent constructor)
    FUN_00492030();
    // Set vtable pointer (offset 0x0) to static vtable at 0x00e34510
    s_instance.vfptr = reinterpret_cast<void**>(0x00e34510);
    // Initialize field at offset 0x4 to 0 (e.g., ref count, flag)
    s_instance.field_0x4 = 0;
    // Return pointer to the static singleton instance
    return &s_instance;
}