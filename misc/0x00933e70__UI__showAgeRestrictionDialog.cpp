// FUNC_NAME: UI::showAgeRestrictionDialog
// 0x00933e70 - Creates and displays a modal error dialog for age-restricted content (too young), with a "Continue without online" option.

void UI::showAgeRestrictionDialog(void)
{
    int iVar1;
    
    // Initialize common UI/dialog subsystem
    FUN_00566b70();
    
    // Mark that the error dialog is active
    g_dialogFlags |= 0x40;
    
    // Allocate dialog structure (size 0xF0 = 240 bytes)
    iVar1 = FUN_009c8e50(0xf0);
    if (iVar1 == 0) {
        iVar1 = 0;
    }
    else {
        iVar1 = FUN_00982280(0);   // Construct/initialize dialog (returns pointer)
    }
    
    // Set dialog type to 11 (kDialogType_Error or similar)
    *(int *)(iVar1 + 0xc) = 0xb;
    
    // Set primary error text
    FUN_00981eb0("$ui_pro_error_too_young ");
    
    // Add button with text and behavior (Button ID 1, param 0)
    FUN_00981e70("$mp_continue_wo_online", 1, 0);
    
    // Set dialog behavior flags (modal, etc.)
    FUN_00982400(1);
    
    // Set callback for button press (points to code at 0x00933a70)
    *(int **)(iVar1 + 0x14) = &LAB_00933a70;
    
    // Show the dialog on screen
    FUN_00982e10();
    
    return;
}