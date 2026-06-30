// FUNC_NAME: InputDeviceManager::setControllerAction
void __thiscall InputDeviceManager::setControllerAction(InputDeviceManager* this, ControllerState* controller, byte actionValue)
{
    // Check if controller is valid and the index field (at +0x1ad) is within array bounds (max 0x23 = 35)
    if ((controller != nullptr) && (*(byte*)((uintptr_t)controller + 0x1ad) < 0x23))
    {
        // Store the action byte into the controller's action array at this+0x118, indexed by the byte at controller+0x1ad
        uint index = *(byte*)((uintptr_t)controller + 0x1ad);
        *(byte*)((uintptr_t)this + 0x118 + index) = actionValue;
    }
}