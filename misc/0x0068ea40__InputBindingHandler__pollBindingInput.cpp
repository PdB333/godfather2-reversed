// FUNC_NAME: InputBindingHandler::pollBindingInput
void __fastcall InputBindingHandler::pollBindingInput(InputBindingHandler* this)
{
    // +0x04: mCurrentState (0=idle, 1=waiting, 2=done)
    // +0x08: mFlags (bit 0: active, other bits maybe)
    // +0x0C: mUserData (some ID or device index)
    // +0x10: mHasNewInput (byte)
    // +0x14: mBindSlotIndex (-1 means all slots)
    
    int* pData = reinterpret_cast<int*>(this);
    byte* pFlags = reinterpret_cast<byte*>(&pData[2]); // +0x08
    int* pState = &pData[1]; // +0x04
    int* pUserData = &pData[3]; // +0x0C
    int* pBindSlot = &pData[5]; // +0x14
    byte* pHasNew = reinterpret_cast<byte*>(&pData[4]); // +0x10

    if (!((*pFlags & 1) != 0 && *pState < 2))
        return;

    // Get an input device or manager from user data
    int devicePtr = FUN_004973e0(*pUserData);
    if (devicePtr == 0)
        return;

    int inputDataBase = *(int*)(devicePtr + 8); // probably base of input slots
    int inputDataSize = *(int*)(devicePtr + 12); // size of slot data
    unsigned int slot = 0;
    while (true)
    {
        // If we have a specific bind slot and we've passed it, abort
        if (*pBindSlot != -1 && *pBindSlot <= (int)slot)
            goto handleDefault;
        if (slot > 1) // only check first two slots (mouse/anim)
            goto handleDefault;

        int pressedButton = FUN_00496610(inputDataBase, inputDataSize, slot);
        if (pressedButton != 0xFF) // 0xFF means no press
            break;
        slot++;
    }

    *pBindSlot = slot;   // remember which slot had the input

    switch (pressedButton)
    {
    case 0: // MouseButton1
        displayBindingString("[b=MouseButton1]");
        break;
    case 1: // MouseButton2
        displayBindingString("[b=MouseButton2]");
        break;
    case 2: // MouseButton3
        displayBindingString("[b=MouseButton3]");
        break;

    case 3: // keyboard key?
    case 4: // keyboard key?
        {
            char* keyName = nullptr;
            int local4 = 0;
            int local8 = 0;
            void* funcPtr = nullptr;
            bool success = FUN_0069c550(pressedButton, &keyName);
            if (!success)
            {
                if (*pState == 0)
                    FUN_0068b910(0x33371f37); // reset/clear binding to default?
            }
            else
            {
                const char* str = keyName ? keyName : "<unknown>";
                FUN_0068e9c0(str); // set the binding string
                if ((*pFlags & 1) != 0 && *pState < 2)
                    *pState = 1; // mark as waiting for second input? or done?
            }
            if (keyName)
                reinterpret_cast<void(*)(const char*)>(funcPtr)(keyName); // presumably free?
            return; // early exit for keyboard keys
        }

    case 5: // AnimMouseUp
        displayBindingString("[b=AnimMouseUp]");
        break;
    case 6: // AnimMouseDown
        displayBindingString("[b=AnimMouseDown]");
        break;
    case 7: // AnimMouseRight
        displayBindingString("[b=AnimMouseRight]");
        break;
    case 8: // AnimMouseLeft
        displayBindingString("[b=AnimMouseLeft]");
        break;

    default:
handleDefault:
        if (*pState != 0)
            return; // already bound, ignore default
        const char* def = (const char*)FUN_0068b910(0x33371f37);
        if (def)
            displayBindingString(def);
        break;
    }

    // Common path: mark as having new input and update state
    *pHasNew = 1;
    if ((*pFlags & 1) != 0 && *pState < 2)
        *pState = 1;
}