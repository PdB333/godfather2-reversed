// FUNC_NAME: ControllerDevice::activateController

// Reconstructed from 0x007cb060: Controller setup/activation function.
// Checks initialization flag, sets configuration ID, applies settings via vtable, and configures hardware state.

// Helper functions (inferred):
extern bool isDeviceConnected();       // 0x007fd640
extern void enableRumble();            // 0x007fcd60
extern void clearDeviceInputBuffers(); // 0x007f4f20
extern void resetDeviceState();        // 0x007f5000

// Struct representing the hardware sub‑object at this+0x58
struct HardwareDevice {
    // +0x0000: ...
    // +0x1BC8: pointer to DeviceState
    DeviceState* m_pState;
};

// Struct representing the state block within hardware device
struct DeviceState {
    // +0x0000: ...
    // +0x05E1: flag byte
    unsigned char flag1;
    // +0x05E2: padding?
    // +0x05E3: flag byte
    unsigned char flag2;
};

// ControllerDevice class (partial)
class ControllerDevice {
public:
    // Virtual table offset 0x2C: applyConfiguration(int id, int a, int b, int c, float scaleX, float scaleY)
    void applyConfiguration(int id, int a, int b, int c, float scaleX, float scaleY);

    void activateController(bool isPrimary);
private:
    // Offsets relative to this:
    // +0x0000: vtable pointer
    // +0x0016: HardwareDevice* m_pHardware  (param_1[0x16])
    // +0x0073: int configurationId          (param_1[0x73])
    // +0x0074: unsigned int flags           (param_1[0x74])  bit 7 = already activated
    int m_vtable; // placeholder
    HardwareDevice* m_pHardware; // +0x58 (0x16 * 4)
    int configurationId;        // +0x1CC (0x73 * 4)
    unsigned int flags;         // +0x1D0 (0x74 * 4)
};

void ControllerDevice::activateController(bool isPrimary) {
    // Skip if already activated (bit 7 of flags)
    if (((flags >> 7) & 1) != 0) {
        return;
    }

    // If device is connected, enable rumble support
    if (isDeviceConnected()) {
        enableRumble();
    }

    // Choose configuration ID based on primary/secondary role
    configurationId = isPrimary ? 0x88117a : 0x81DC3F5F; // Two distinct preset IDs

    // Apply the configuration via virtual function
    applyConfiguration(configurationId, 1, 1, 0, 1.0f, 1.0f);

    // Access hardware device state and set two flags
    DeviceState* state = m_pHardware->m_pState; // via offset +0x1BC8
    state->flag1 = 1; // offset +0x5E1
    state->flag2 = 1; // offset +0x5E3

    // Reset input buffers and device state
    clearDeviceInputBuffers();
    resetDeviceState();
}