// FUNC_NAME: InputDeviceManager::initActionMapping

void __thiscall InputDeviceManager::initActionMapping(uint32_t* actionData)
{
    // Initialize action name-to-ID mapping for controller inputs
    // Each pair: [string pointer (name), action ID (enum value)] at consecutive 4-byte slots
    actionData[0] = (uint32_t)"Pad.RightDPad.Left";
    actionData[1] = 6;
    actionData[2] = (uint32_t)"Pad.RightDPad.Down";
    actionData[3] = 5;
    actionData[4] = (uint32_t)"Pad.RightDPad.Right";
    actionData[5] = 7;
    actionData[6] = (uint32_t)"Pad.RightDPad.Up";
    actionData[7] = 4;
    actionData[8] = (uint32_t)"Pad.Trigger.LeftTop";
    actionData[9] = 9;
    actionData[10] = (uint32_t)"Pad.Trigger.LeftBottom";
    actionData[11] = 8;
    actionData[12] = (uint32_t)"Pad.Trigger.RightTop";
    actionData[13] = 11;
    actionData[14] = (uint32_t)"Pad.Trigger.RightBottom";
    actionData[15] = 10;
    actionData[16] = (uint32_t)"Pad.Start";
    actionData[17] = 12;
    actionData[18] = (uint32_t)"Pad.Back";
    actionData[19] = 13;
    actionData[20] = (uint32_t)"Pad.LeftStick.Click";
    actionData[21] = 14;
    actionData[22] = (uint32_t)"Pad.RightStick.Click";
    actionData[23] = 15;

    // Duplicate button IDs for an alternative lookup section (indices 24–27)
    actionData[0x18] = 12; // Pad.Start
    actionData[0x1b] = 13; // Pad.Back
    actionData[0x19] = 14; // Pad.LeftStick.Click
    actionData[0x1a] = 15; // Pad.RightStick.Click

    // Map analog stick axes (indices 28–35)
    actionData[0x1c] = (uint32_t)"Pad.LeftStick.X";
    actionData[0x1d] = 16;
    actionData[0x1e] = (uint32_t)"Pad.LeftStick.Y";
    actionData[0x1f] = 17;
    actionData[0x20] = (uint32_t)"Pad.RightStick.X";
    actionData[0x21] = 18;
    actionData[0x22] = (uint32_t)"Pad.RightStick.Y";
    actionData[0x23] = 19;
}