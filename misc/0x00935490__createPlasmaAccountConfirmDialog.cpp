// FUNC_NAME: createPlasmaAccountConfirmDialog
void createPlasmaAccountConfirmDialog(void)
{
    // Global pointer to a UI/manager object (e.g., UIManager singleton)
    int* uiManager = DAT_01129890;

    // Pre-initialization of some underlying system
    FUN_0098e4f0();

    // Set the screen title using localized string "$ui_pro_screen_name"
    FUN_004d3d90("$ui_pro_screen_name");

    // Configure screen elements: text, color references (likely alpha/color values)
    // &DAT_00e2f044 appears three times – possibly diffuse, background, shadow colors
    // 2 = some layout flag or element count, 0x10 = padding/behaviour option
    FUN_0098e690("$ui_pro_screen_name ", &DAT_00e2f044, &DAT_00e2f044, &DAT_00e2f044, 2, 0x10);

    // Set confirmation prompt text from localization
    FUN_0098e7b0("$mp_online_plasma_create_account_option_confirm");

    // Retrieve vtable-like function pointer at offset 0x28 from the manager object
    // This is likely a "show" or "run" method for the dialog
    code* showFn = *(code**)(*uiManager + 0x28);

    // Set two callback function pointers in the UI object (assumed at offsets +0x8C and +0x90)
    // These correspond to confirm (accept) and cancel (reject) actions
    uiManager[0x23] = (int)&LAB_00933d90; // e.g., onConfirm
    uiManager[0x24] = (int)&LAB_00933ba0; // e.g., onCancel

    // Indirect call to display/activate the dialog
    (*showFn)();

    return;
}