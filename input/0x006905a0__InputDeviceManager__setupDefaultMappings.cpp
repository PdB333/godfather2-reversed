// FUNC_NAME: InputDeviceManager::setupDefaultMappings
void InputDeviceManager::setupDefaultMappings()
{
    // If this object is valid, set up four action commands (likely movement/action bindings)
    if (this) {
        // Each block: get action name string, assign to a command slot, log event with hash
        undefined8 actionName = Input::getActionName(0); // FUN_0049a640(0)
        this->setActionMapping(0x11, actionName);        // vtable+4: setActionMapping(int cmd, const char* name)
        Input::logAnalytics(0x8c036aab, this, 0x11);    // event hash, object, command ID

        actionName = Input::getActionName(0);
        this->setActionMapping(0x13, actionName);
        Input::logAnalytics(0x46e7afe1, this, 0x13);

        actionName = Input::getActionName(0);
        this->setActionMapping(0x10, actionName);
        Input::logAnalytics(0x1a271621, this, 0x10);

        actionName = Input::getActionName(0);
        this->setActionMapping(0x12, actionName);
        Input::logAnalytics(0xd7d6fc22, this, 0x12);
    }

    // Set up device types for two controller slots (0 and 1)
    undefined4 deviceType0 = Input::getDefaultDeviceType(0); // FUN_0049a850()
    this->setDeviceType(0, deviceType0);                     // vtable+0x18: setDeviceType(int slot, int type)

    undefined4 deviceType1 = Input::getDefaultDeviceType(1); // FUN_0049a860()
    this->setDeviceType(1, deviceType1);
}