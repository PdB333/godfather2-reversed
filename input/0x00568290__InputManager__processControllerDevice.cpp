// FUNC_NAME: InputManager::processControllerDevice
void __fastcall InputManager::processControllerDevice(int this)
{
    // Get device interface pointer from this+0x34
    IDevice* device = *(IDevice**)(this + 0x34);
    
    // Store device handle/ID at this+0xc
    *(int*)(this + 0xc) = device->getHandle(); // vtable+0x24
    
    // If device has changed state (vtable+0x3c), reinitialize
    if (device->hasChanged()) { // vtable+0x3c
        FUN_005683c0(); // Reinitialize or handle change
    }
}