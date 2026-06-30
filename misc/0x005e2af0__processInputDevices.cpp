// FUNC_NAME: processInputDevices
// Address: 0x005e2af0
// Role: Wrapper that fetches the global input device manager singleton and calls its update function.

extern void updateInputDeviceManager(InputDeviceManager* pManager); // from 0x005e20f0
extern InputDeviceManager* g_inputDeviceManager; // DAT_0122350c

void processInputDevices(void)
{
    updateInputDeviceManager(g_inputDeviceManager);
}