// FUNC_NAME: setGraphicsDeviceConfig

// Function address: 0x0044b8b0
// Role: Calls a singleton graphics device's virtual dispatch method with a configuration command (0xa0) and a 3-integer structure.

struct DisplayConfig {
    int field_0; // +0x00: value 2 (likely x offset or mode flag)
    int field_4; // +0x04: value 16 (likely y offset or width)
    int field_8; // +0x08: value 0 (likely z offset or height)
};

class GraphicsDevice {
public:
    // vtable offset 0: dispatches a command; __thiscall assumed
    virtual void dispatchCommand(int commandID, DisplayConfig* config) = 0;
};

// Returns a singleton GraphicsDevice pointer (from FUN_009c8f80)
GraphicsDevice* getGraphicsDevice();

void setGraphicsDeviceConfig() {
    GraphicsDevice* device = getGraphicsDevice();
    if (device != nullptr) {
        DisplayConfig config;
        config.field_0 = 2;
        config.field_4 = 16;
        config.field_8 = 0;

        // Command 0xa0 likely indicates "set display config"
        device->dispatchCommand(0xa0, &config);
    }
}