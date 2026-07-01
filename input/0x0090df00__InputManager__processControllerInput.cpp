// FUNC_NAME: InputManager::processControllerInput
void InputManager::processControllerInput(void)
{
    undefined4 local_8;
    undefined4 local_4;
    
    // Check if controller slot 0 is connected (active flag at +0x48)
    if (*(char *)(DAT_01129c4c + 0x48) != '\0') {
        // Read controller 0 input state
        FUN_0090de60(0, &local_8, &local_4);
        // Process input for controller 0 (likely player 1)
        FUN_009394b0(local_8, local_4);
    }
    // Check if controller slot 1 is connected (active flag at +0x48)
    if (*(char *)(DAT_0112b9b8 + 0x48) != '\0') {
        // Read controller 1 input state
        FUN_0090de60(1, &local_8, &local_4);
        // Process input for controller 1 (likely player 2)
        FUN_0094e2b0(local_8);
    }
    return;
}