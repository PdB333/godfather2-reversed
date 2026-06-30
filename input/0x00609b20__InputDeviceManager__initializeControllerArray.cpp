// FUNC_NAME: InputDeviceManager::initializeControllerArray

// Address: 0x00609b20
// Initializes the global controller array (32 slots of 12 bytes each) to zero and returns pointer to it.
// Also sets the controller count to 0.

struct ControllerSlot {
    int field_0; // +0x00
    int field_4; // +0x04
    int field_8; // +0x08
};

static ControllerSlot g_controllerSlots[32]; // located at 0x01222328
static int g_controllerCount; // located at 0x012224a8

ControllerSlot* InputDeviceManager::initializeControllerArray() {
    for (int i = 0; i < 32; ++i) {
        g_controllerSlots[i].field_0 = 0;
        g_controllerSlots[i].field_4 = 0;
        g_controllerSlots[i].field_8 = 0;
    }
    g_controllerCount = 0;
    return g_controllerSlots;
}