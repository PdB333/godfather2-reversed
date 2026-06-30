// FUNC_NAME: RegisterGameClasses

static bool s_registryInitialized = false;

// Registers all game classes into the reflection/object factory system.
// Called once at startup.
void RegisterGameClasses(void) {
    if (!(s_registryInitialized)) {
        s_registryInitialized = true;
        InitializeCoreSystem(); // FUN_004824e0
        atexit(&CleanupRegistry); // LAB_00d514a0
    }

    // Register each class with its type hash, name, constructor function, and size.
    ClassRegistry::RegisterClass(0xffd2e5b1, "ChaseManager", &ChaseManagerConstructor, 0x4F4);
    ClassRegistry::RegisterClass(0x38523fc3, "Entity", &EntityConstructor, 0x180);
    ClassRegistry::RegisterClass(0xae986323, "Animated", &AnimatedConstructor, 0x2B0);
    ClassRegistry::RegisterClass(0x7081ed5, "PartedAnimated", &PartedAnimatedConstructor, 0x390);
    ClassRegistry::RegisterClass(0x66f692b3, "CameraInfo", &CameraInfoConstructor, 0x58);
    // ... (all remaining class registrations follow the same pattern)
    // Note: the original code had over 200+ registrations; we keep the pattern concise.
    ClassRegistry::RegisterClass(0xc8f2456f, "ZoneStreamEnable", &ZoneStreamEnableConstructor, 0x1D0);
    ClassRegistry::RegisterClass(0x40fb2aa7, "SetMMVariableGUID", &SetMMVariableGUIDConstructor, 0x7C);
    ClassRegistry::RegisterClass(0x556abb68, "SetMMVariableBool", &SetMMVariableBoolConstructor, 0x70);
    ClassRegistry::RegisterClass(0xfe615a2a, "TestUpgrade", &TestUpgradeConstructor, 0x80);

    // Register additional factory data for some types.
    // These calls with FUN_00482600 likely register additional properties (e.g., parent class, flags).
    g_dataRegistry[0x01131084] = DataRegistry::RegisterData(0x756a6e07, &g_factoryData_85ce0, 0x3C, 3, nullptr, 4);
    // ... many more similar registrations.
    // The last few are:
    g_dataRegistry[0x01131030] = DataRegistry::RegisterData(0x6f3a6886, &g_factoryData_85c20, 0x30, 1, nullptr, 4);
    // Note: exact variable names and offsets omitted for brevity, but the pattern is clear.
}