// FUNC_NAME: PlayerInputHandler::updateInputState
void __fastcall PlayerInputHandler::updateInputState(int this)
{
    char cVar1;
    
    cVar1 = isGamePaused();
    if (cVar1 == '\0') {
        (**(code **)(*DAT_0112af90 + 0x2c))();  // Process mouse input (vtable +0x2c)
    }
    if (*(int *)(DAT_01223484 + 0xc) != 0) {    // Check if gamepad is connected
        cVar1 = isGamePaused();
        if (cVar1 != '\0') {
            (**(code **)(*DAT_0112a87c + 0x2c))();  // Process gamepad input when paused (vtable +0x2c)
        }
        (**(code **)(*DAT_0112b9b8 + 0x2c))();  // Process gamepad input normally (vtable +0x2c)
    }
    if ((*(uint *)(this + 0x5c) >> 0xc & 1) != 0) {  // Check bit 12 of input flags (+0x5c)
        FUN_005c02f0(this + 0x10, &LAB_0093bd50, 1);  // Some timed action/cooldown
    }
    if ((*(uint *)(this + 0x5c) >> 0xe & 1) != 0) {  // Check bit 14 of input flags (+0x5c)
        FUN_00939ba0(0);  // Clear specific input state
    }
    *(undefined4 *)(this + 0x5c) = 0;  // Reset input flags
    return;
}