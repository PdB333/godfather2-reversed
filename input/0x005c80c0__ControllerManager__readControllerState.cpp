// FUNC_NAME: ControllerManager::readControllerState
void __thiscall ControllerManager::readControllerState(void* this, void* controllerData)
{
    byte outputBuffer1[4];
    byte outputBuffer2[4];
    byte outputBuffer3[4];

    // Initialize controller state (likely resets internal flags)
    FUN_005c5320(this);

    // Read raw controller data into output buffers; last argument is address of controllerData pointer
    FUN_005c50c0(controllerData, outputBuffer1, outputBuffer2, outputBuffer3, &controllerData);

    // Process the read data (e.g., map to game actions)
    FUN_005c4e30();

    // Apply processed input to the game state
    FUN_005c4f80();
}