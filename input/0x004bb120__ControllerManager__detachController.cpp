// FUNC_NAME: ControllerManager::detachController

void ControllerManager::detachController()
{
    // Structure used to register/unregister controller with engine subsystems
    struct RegistrationData {
        void* systemPtr;    // +0x00: pointer to global system object
        void* controller;   // +0x04: pointer to this controller instance
        char padding;       // +0x08: padding (unused)
    };

    // Unregister from first subsystem (e.g., input dispatcher)
    RegistrationData reg1;
    reg1.systemPtr = reinterpret_cast<void*>(DAT_01218048); // Global system pointer
    reg1.controller = this;
    reg1.padding = 0;
    FUN_00408a00(&reg1, 0); // Unregister callback (0 means remove)

    // Cleanup controller-specific resources (e.g., release XInput slot)
    FUN_004bafc0(this, 0, 0);

    // Unregister from second subsystem (e.g., event handler)
    RegistrationData reg2;
    reg2.systemPtr = reinterpret_cast<void*>(DAT_01218040); // Another global system pointer
    reg2.controller = this;
    reg2.padding = 0;
    FUN_00408a00(&reg2, 0); // Unregister callback
}