// FUNC_NAME: InputDeviceManager::InputDeviceManager
void __fastcall InputDeviceManager::InputDeviceManager(InputDeviceManager *this)
{
    // Set vtable pointer at offset 0x00
    this->vtable = (int*)&PTR_FUN_00d8f668;
    // Set secondary function table at offset 0x10
    this->funcTable1 = (int*)&PTR_LAB_00d8f640;
    // Set member at offset 0x4C - overwritten below; may be a union or initialization in two steps
    this->field_0x4C = (int*)&PTR_LAB_00d8f63c;
    // Overwrite same offset with a different pointer
    this->field_0x4C = (int*)&PTR_LAB_00d8f638;
    // Global flag indicating initialization status
    g_inputDeviceManagerInitialized = 0;
    // Call internal initialization routine
    InputDeviceManager::initInternal();
}