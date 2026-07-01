// FUNC_NAME: UIControl::processInputSelection
void __fastcall UIControl::processInputSelection(int this)
{
    char result;

    // Check conditions: either inputState != 0 or inputMode > 2, and inputState < 5, and selectionFlag == 0
    if ((((*(uint *)(this + 0x58) != 0) || (2 < *(uint *)(this + 0x54))) &&
        (*(uint *)(this + 0x58) < 5)) && (*(int *)(this + 0x50) == 0))
    {
        result = FUN_009244a0("$ui_ctrl_choose_input"); // Check if input chooser UI is active
        if (result != '\0')
        {
            FUN_00923590(); // Probably a static function to show/hide UI
            *(undefined4 *)(this + 0x50) = 1; // Set selectionFlag to 1
            *(undefined4 *)(this + 0x68) = DAT_01205214; // Store some constant
            *(undefined4 *)(this + 100) = _DAT_00d87274; // Store another constant (offset 0x64)
            FUN_005c0260(this + 0x10, &LAB_00924b80, 1); // Set up callback/timer with address LAB_00924b80, repeat=1
            // Prepare a local struct and call a function
            int local_c = DAT_011302e8;
            int local_8 = 0;
            char local_4 = 0;
            FUN_00408a00(&local_c, 0);
        }
    }
    return;
}