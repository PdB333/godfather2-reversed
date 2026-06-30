// FUNC_NAME: InputDeviceManager::constructor
// Address: 0x006a7b40
// Constructor for the input device manager singleton.
// Initializes vtable pointers, registers device types, and zeros connection state.

// Known global singleton pointer
InputDeviceManager* g_inputDeviceManager = (InputDeviceManager*)0x01129984;

// External global for device count? (likely number of available slots)
int g_deviceCount = *(int*)0x00d5c454;

// Vtable symbols (from Ghidra labels)
extern void* vtable_InputDeviceManager_00d5d868;  // Main vtable for InputDeviceManager
extern void* vtable_InputDeviceManager_base_00d5d85c;  // Base class vtable
extern void* vtable_InputDeviceManager_derived_00d5d864; // Derived class vtable (overrides base at offset 2)

// Forward declarations of callees
void __thiscall BaseClass_constructor(void* this); // FUN_0049c610
void __thiscall registerDeviceType(int deviceType, int count); // FUN_006a79f0
void __thiscall registerSingleton(void* address, int flags); // FUN_0049c6e0 (passes &DAT_00d5d860 and 1)

// The device enum object passed in (param_2) - assumed interface
class DeviceEnumInterface {
public:
    virtual void startEnumeration(); // vtable+8
};

InputDeviceManager* __thiscall InputDeviceManager_constructor(InputDeviceManager* this, DeviceEnumInterface* deviceEnum) {
    // Call base class constructor (likely memory initialization)
    BaseClass_constructor(this);

    // Store device enumeration interface pointer
    this->deviceEnum = deviceEnum; // offset 0x0c (param_1[3])

    // Set vtable pointers (typical multiple inheritance pattern)
    this->vtable1 = &vtable_InputDeviceManager_00d5d868; // offset 0x00 (first vtable)
    this->vtable2 = &vtable_InputDeviceManager_base_00d5d85c; // offset 0x08 (base class vtable)
    this->vtable2 = &vtable_InputDeviceManager_derived_00d5d864; // override with derived vtable

    // Register device type 6 with the count from global
    registerDeviceType(6, g_deviceCount);

    // Start enumeration via the interface
    deviceEnum->startEnumeration(); // vtable entry at offset 8

    // Initialize connection state arrays
    // +0x434 (param_1[0x10d]) : currentActiveControllers (number of currently connected devices)
    this->currentActiveControllers = 0;
    // +0x438 (param_1[0x10e]) : maxControllers (total slots)
    this->maxControllers = 0;
    // +0x28 (param_1[0xa]) : controllerStateFlags (bitfield)
    this->controllerStateFlags = 0;
    // +0x2c (param_1[0xb]) : controllerActiveMask
    this->controllerActiveMask = 0;

    // Register this instance as the global singleton
    registerSingleton(&g_inputDeviceManager, 1); // actually &DAT_00d5d860, but likely the global pointer

    return this;
}