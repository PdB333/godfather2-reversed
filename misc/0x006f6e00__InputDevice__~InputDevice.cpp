// FUNC_NAME: InputDevice::~InputDevice
void __fastcall InputDevice::~InputDevice(InputDevice* this)
{
    // Set vtables for destruction sequence
    this->vtable = &VTable_Normal;       // +0x00
    this->vtable2 = &VTable_Derived1;    // +0x3C
    this->vtable3 = &VTable_Derived2;    // +0x48
    this->vtable4 = &VTable_Destroying;  // +0x90

    // If device type is active and has a valid handle, release from manager
    if ((this->flags & 3) != 0)          // +0x8C (byte)
    {
        int handle = 0;
        if (this->deviceType == 1)       // +0xE4, e.g., EControllerType
        {
            handle = this->controllerHandle; // +0x7C
        }
        else if (this->deviceType == 2)  // e.g., EKeyboardType
        {
            handle = this->keyboardHandle;   // +0x84
        }
        else
        {
            goto free_name;
        }

        if (handle != 0 && handle != 0x48)   // 0x48 may be invalid/unused
        {
            InputDeviceManager* mgr = InputDeviceManager::instance(); // FUN_0043b870(DAT_0112a9fc)
            if (mgr != nullptr)
            {
                mgr->removeDevice(handle);   // vtable+0x1c
            }
        }
    }

free_name:
    if (this->nameString != nullptr)     // +0xB4
    {
        operator delete(this->nameString); // FUN_004daf90
    }

    // Switch to fully destroyed vtable state
    this->vtable4 = &VTable_Destroyed;   // +0x90, PTR_LAB_00d60740
    g_InputDeviceDestroyFlag = 0;        // DAT_0112aa10
    InputManager::onDeviceDestroyed();   // FUN_006f2ee0
}