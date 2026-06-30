// FUNC_NAME: InputManager::receiveControllerInput
void __fastcall InputManager::receiveControllerInput(int *inputData) // inputData is a pointer to 64-byte controller state
{
    // Global input state buffer at 0x1219b50 (64 bytes, 16 ints)
    gInputState[0] = inputData[0];
    gInputState[1] = inputData[1];
    gInputState[2] = inputData[2];
    gInputState[3] = inputData[3];
    gInputState[4] = inputData[4];
    gInputState[5] = inputData[5];
    gInputState[6] = inputData[6];
    gInputState[7] = inputData[7];
    gInputState[8] = inputData[8];
    gInputState[9] = inputData[9];
    gInputState[10] = inputData[10];
    gInputState[11] = inputData[11];
    gInputState[12] = inputData[12];
    gInputState[13] = inputData[13];
    gInputState[14] = inputData[14];
    gInputState[15] = inputData[15];

    // Check if the active slot should process this input
    // gActiveSlotPointer (0x12058e8) points to the currently active slot structure (0x1219a70)
    if ((gActiveSlotPointer == &gActiveSlot) && (gPlayerSlotArray[gActiveSlotIndex * 0x30] != 0))
    {
        // Forward the raw input to the slot's input processor
        // gPlayerSlotArray at 0x1219cb0, stride 0x30
        // gGlobalInputForwarder at 0x1219a80 is used as a pointer to global state
        FUN_0060b020(gGlobalInputForwarder, &gPlayerSlotArray[gActiveSlotIndex * 0x30], inputData);
    }
}