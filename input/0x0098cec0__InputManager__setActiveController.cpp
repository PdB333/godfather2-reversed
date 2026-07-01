//FUNC_NAME: InputManager::setActiveController
// Address: 0x0098cec0
// Checks if the given controller index is the primary or secondary controller.
// If it's the secondary, it activates it (calls setControllerActive(0)).
// Returns 1 if the controller was set or already active, 0 otherwise.

int InputManager::setActiveController(int controllerIndex) {
    int primaryController = getPrimaryControllerIndex();   // FUN_00466840
    if (controllerIndex == primaryController) {
        return 1;
    }
    int secondaryController = getSecondaryControllerIndex(); // FUN_00466860
    if (controllerIndex == secondaryController) {
        setControllerActive(0); // FUN_0098ce00(0) - activate secondary controller
        return 1;
    }
    return 0;
}