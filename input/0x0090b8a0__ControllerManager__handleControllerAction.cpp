// FUNC_NAME: ControllerManager::handleControllerAction
void __thiscall ControllerManager::handleControllerAction(uint controllerIndex, uint actionId)
{
    int controllerSlot = findControllerForAction(actionId);
    if (controllerSlot != -1) {
        setControllerButtonState(controllerSlot, 1);
        return;
    }
    // If no controller mapped, fallback: use controllerIndex unless it's 16 (invalid), then use 0
    handleActionDirectly(-(uint)(controllerIndex != 0x10) & controllerIndex);
}