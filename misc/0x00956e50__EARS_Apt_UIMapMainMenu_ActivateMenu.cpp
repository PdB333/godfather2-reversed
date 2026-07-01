// Xbox PDB: EARS_Apt_UIMapMainMenu_ActivateMenu
// FUNC_NAME: UIButton::handleFirstActivation
// Function address: 0x00956e50
// Role: Performs one-time activation initialization for a UI button.
// Checks flag at +0x50; if zero, sets it, plays sound, sends script commands,
// registers callbacks, increments reference count (+0x78), and resets active state (+0x7c).

void __thiscall UIButton::handleFirstActivation(UIButton* this)
{
    if (this->flag50 == 0) {
        this->flag50 = 1; // Mark as first activation done

        // Play activation sound/effect using resource handle at +0x6C
        playActivationSound(*(uint32_t*)((uint8_t*)this + 0x6C));

        // Send "Activate" script command
        sendScriptCommand("Activate", 0, g_scriptContext, 0);

        // Setup UI state
        setupUI();

        // Register a callback function (LAB_005bfc10)
        pushCallback((uint8_t*)this + 0x14, callbackFunc1, 0);

        // Pop/remove a callback (LAB_005bfbe0)
        popCallback();

        // Register another callback
        pushCallback((uint8_t*)this + 0x14, callbackFunc2, 0);

        // Update reference count (maybe UI element usage)
        updateReferenceCount();

        // Local data structure (two uint32s + one byte) cleared
        uint32_t localData[2]; // 8 bytes
        localData[0] = g_globalValue; // DAT_01130320
        localData[1] = 0;
        uint8_t localByte = 0;
        clearLocalData(&localData, 0);

        // Send "ActivateButton" command with button index '1' (0x31)
        uint8_t buttonIndex1 = 0x31;
        uint8_t nullByte = 0;
        sendScriptCommand("ActivateButton", 0, g_scriptContext, 1, &buttonIndex1, &nullByte);

        // Send "DeactivateButton" command with button index from global pointer
        sendScriptCommand("DeactivateButton", 0, g_scriptContext, 1, g_buttonIndexDefault);

        // Increment usage counter at +0x78
        *(int32_t*)((uint8_t*)this + 0x78) = *(int32_t*)((uint8_t*)this + 0x78) + 1;

        // Reset active/inactive byte at +0x7C
        *(uint8_t*)((uint8_t*)this + 0x7C) = 0;

        // Send "DeactivateButton" command with button index '0' (0x30)
        uint8_t buttonIndex0 = 0x30;
        sendScriptCommand("DeactivateButton", 0, g_scriptContext, 1, &buttonIndex0);
    }
}