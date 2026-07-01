// FUNC_NAME: ControllerManager::ControllerManager (tentative, based on input system context)
// Address: 0x007d1940
// Reconstructed constructor for ControllerManager class

ControllerManager * __thiscall ControllerManager::ControllerManager(ControllerManager *this, int arg2, int arg3)
{
    float value;
    int temp;

    // Call base class initializer? (arg2, arg3 may be parent/creation params)
    FUN_007ab5e0(arg2, arg3);

    // Set vtable pointer
    this->vtable = &PTR_LAB_00d6edcc; // ControllerManager vtable

    // Retrieve a virtual function at offset 0x1c0 from some sub-object (e.g., input system)
    // param_1[0x16] is offset +0x58 from 'this'
    value = (**(float (__thiscall **)(void *))(*(int *)this->field_58 + 0x1c0))(this->field_58);

    // Store the float value at offset +0x7c (param_1[0x1f])
    this->field_7c = value;

    // Initialize two boolean-like fields
    this->field_80 = 0;  // param_1[0x20]
    this->field_84 = 0;  // param_1[0x21]

    // If value is less than some global threshold, set field_84 true
    if (value < (float)_DAT_00e53018) {
        this->field_84 = 1;
    }

    // Retrieve what appears to be a singleton/manager instance (e.g., analog input)
    temp = FUN_007ab130();  // likely InputDeviceManager::getAnalogManager
    this->field_74 = *(int *)(temp + 4);  // store some field from it
    // Call a virtual function on that instance with argument 0x3f (63 = analog deadzone?)
    (**(code **)*temp)(0x3f);

    // Similar for second singleton (e.g., digital input)
    temp = FUN_007ab140();  // likely InputDeviceManager::getDigitalManager
    this->field_78 = *(int *)(temp + 4);
    (**(code **)*temp)(0x3ff);  // 1023 = digital range?

    // Call some global setup/init function
    FUN_0045f2a0(0);

    // Set a flag in the sub-object at offset 0x24a0 (bit 26: 0x4000000)
    *(uint *)(this->field_58 + 0x24a0) |= 0x4000000;

    return this;
}