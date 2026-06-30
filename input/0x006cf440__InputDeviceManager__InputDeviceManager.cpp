// FUNC_NAME: InputDeviceManager::InputDeviceManager
// Address: 0x006cf440
// Constructor for InputDeviceManager. Sets vtable pointer, stores a static data pointer,
// checks debug build flag, logs level 7 message if debug, then calls initialization.

void __fastcall InputDeviceManager::InputDeviceManager(InputDeviceManager *this)
{
    // Set vtable pointer (+0x00)
    *this = &INPUTDEVICEMANAGER_VTABLE;

    // Store pointer to static data (likely a string or base class offset) (+0x08)
    *(int *)((char *)this + 8) = (int)&INPUTDEVICEMANAGER_STATIC_DATA;

    // Check if debug build is active
    if (isDebugBuild())
    {
        // Log a message with severity 7 (e.g., debug message or error)
        logMessage(7);
    }

    // Perform additional initialization (global or base class init)
    inputDeviceManagerInit();
}