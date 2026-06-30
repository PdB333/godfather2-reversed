// FUNC_NAME: InputDeviceManager::InputDeviceManager

// Reconstructed constructor for InputDeviceManager (address 0x00565f80)
// Sets up vtable, calls base constructor, then overrides vtable for derived class.
// Static member s_initialized is cleared.

// External base class constructor (likely EARS::Framework::Object or similar)
extern void __thiscall BaseClassConstructor(void* this);

// The vtable symbols (defined in the executable)
extern void* PTR_FUN_00e3a5d0; // Base class vtable
extern void* PTR_LAB_00e3a5d4; // Derived class vtable (InputDeviceManager)

class InputDeviceManager
{
public:
    void** vtable;                // +0x00 virtual function table pointer
    static bool s_initialized;    // +0x012234dc global static flag

    // Constructor
    InputDeviceManager();
};

// Static member definition
bool InputDeviceManager::s_initialized = false;

// Constructor implementation
__thiscall InputDeviceManager::InputDeviceManager()
{
    // Step 1: Set vtable to base class vtable (before base init)
    this->vtable = &PTR_FUN_00e3a5d0;

    // Step 2: Call base class constructor (e.g., Framework::Object::Object)
    BaseClassConstructor(this);

    // Step 3: Override vtable with the derived class table (InputDeviceManager)
    this->vtable = &PTR_LAB_00e3a5d4;

    // Step 4: Initialize static flag to false (uninitialized state)
    s_initialized = false;
}