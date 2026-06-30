// FUNC_NAME: ControllerManager::processButtonEvent
void __thiscall ControllerManager::processButtonEvent(int* this, int* buttonEvent)
{
    int globalControllerId;
    bool isMenuOpen;
    bool isInputBlocked;
    bool isGamePaused;
    int someDataPtr;

    sub_46C6A0(buttonEvent);
    globalControllerId = DAT_0112a834;

    // Check if the button ID matches either of two stored controller IDs (+0x78, +0x80)
    if ((*buttonEvent == *(int *)(this + 0x78) || *buttonEvent == *(int *)(this + 0x80)) &&
        (DAT_0112a834 != 0))
    {
        isMenuOpen = sub_481640();
        if (isMenuOpen)
        {
            isInputBlocked = sub_89C630();
            if ((isInputBlocked == false) && (buttonEvent[1] != 0))
            {
                // buttonEvent[1] points to additional data; offset -0x48 is likely a base pointer adjustment
                someDataPtr = *(int *)(buttonEvent[1] + 4);
                if (someDataPtr == 0)
                {
                    someDataPtr = 0;
                }
                else
                {
                    someDataPtr = someDataPtr - 0x48; // Adjust to get relevant structure
                }

                isGamePaused = sub_481620();
                if (isGamePaused)
                {
                    // Virtual call via vtable stored at this-0x3c; index 0x24 returns something
                    (**(code **)(*(int *)(this + -0x3c) + 0x24))(local_20);

                    if (*buttonEvent == *(int *)(this + 0x78))
                    {
                        // Play sound or execute action for first controller ID
                        sub_6CEDA0(*(undefined4 *)(someDataPtr + 0x1ef4)); // +0x1ef4 is large offset, likely a member variable
                        sub_89BDF0(*(undefined1 *)(someDataPtr + 0x1ef4), globalControllerId, uStack_1c);
                        return;
                    }
                    // For second controller ID, set state to 2 (+0x88) and broadcast with 0xFF
                    *(int *)(this + 0x88) = 2;
                    sub_89BDF0(0xff, globalControllerId, uStack_1c);
                }
            }
        }
    }
    return;
}