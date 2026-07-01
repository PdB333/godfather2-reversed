// FUNC_NAME: InputManager::updateForceFeedback
void __fastcall InputManager::updateForceFeedback(InputManager *this)
{
    bool bResult;
    int *pControllerComponent;
    int iValue;
    int *pForceFeedbackData;
    int *pDataPointer;
    uint *pSlotFlags;
    int slotIndex;

    // Enable force feedback
    *(int *)((char *)this + 0x1A4) = 1;

    // Initialize force feedback system
    InputManager::initForceFeedback(this);

    slotIndex = 0;
    pSlotFlags = (uint *)((char *)this + 0xC0); // Array of slot flags (each 0x5C apart)

    do {
        if (slotIndex != 0) { // Skip slot 0? (first player is handled separately)
            // Get controller component for current slot offset
            pControllerComponent = (int *)InputManager::getControllerComponent((int *)((char *)pSlotFlags - 0x38), 0);
            if (pControllerComponent != nullptr) {
                // Resolve component by hash (0x254cce9 likely "ForceFeedbackComponent" or similar)
                pForceFeedbackData = nullptr;
                bResult = (**(code **)(*pControllerComponent + 0x10))(0x254cce9, &pForceFeedbackData);
                if (bResult && pForceFeedbackData != nullptr) {
                    // Check if force feedback is active
                    bResult = (**(code **)(*pForceFeedbackData + 0x154))();
                    if (bResult) {
                        iValue = (**(code **)(*pForceFeedbackData + 0x160))(); // Get feedback intensity
                        if (iValue != 0) {
                            // Check if both rumble motors are off
                            if (((*pSlotFlags & 1) == 0) && ((*pSlotFlags >> 1 & 1) == 0)) {
                                InputManager::setLeftMotorRumble(1); // Enable left motor
                            }
                            InputManager::setRightMotorRumble(1); // Enable right motor
                        }
                    }
                }
                // Second hash lookup (0x43c8ec5b - possibly different feedback data)
                pDataPointer = nullptr;
                bResult = (**(code **)(*pControllerComponent + 0x10))(0x43c8ec5b, &pDataPointer);
                pForceFeedbackData = pForceFeedbackData; // Reuse variable
                if (bResult && pForceFeedbackData != nullptr) {
                    bResult = (**(code **)(*pForceFeedbackData + 0x154))();
                    if (bResult) {
                        iValue = *(int *)((char *)pForceFeedbackData + 0x180); // Offset 0x180
                        if (InputManager::isFeedbackActive(iValue)) {
                            InputManager::startSpecificFeedback(iValue);
                        }
                    }
                }
            }
        }
        slotIndex++;
        pSlotFlags += 0x17; // Advance to next slot (0x5C bytes)
    } while (slotIndex < 3);
    InputManager::finalizeFeedback();
}