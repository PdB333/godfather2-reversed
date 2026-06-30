// FUNC_NAME: InputManager::UpdateCombinedInput
void InputManager::UpdateCombinedInput(InputManager* thisPtr) {
    int leftAxisVal = InputManager::GetAxisValue(1);   // +0x00: horizontal axis
    int rightAxisVal = InputManager::GetAxisValue(2);  // +0x04: vertical axis
    InputManager::SetCombinedValue(thisPtr, leftAxisVal + rightAxisVal); // stores sum, e.g., magnitude
}