// FUNC_NAME: UIInputConfigMenu::ShowConfirmationDialog

void __thiscall UIInputConfigMenu::ShowConfirmationDialog(int thisPtr, int actionId)
{
  // Allocate a confirmation dialog structure (0xF0 bytes)
  ConfirmationDialog* dialog = (ConfirmationDialog*)operatorNew(0xF0);
  if (dialog != nullptr) {
    // Construct/initialize dialog with parameter 0
    constructConfirmationDialog(dialog, 0);
  }

  switch (actionId) {
  case 0: // Clear conflicts confirmation
    dialog->type = 2; // Confirmation dialog type
    setDialogText(dialog, "$ui_ctrl_conflicts_clear_confirm");
    dialog->responseHandler = &onClearConfirm; // LAB_009245c0
    break;

  case 1:
  case 2: // Unable to assign error
    dialog->type = 3; // Error dialog type
    setDialogText(dialog, "$ui_ctrl_unable_to_assign");
    dialog->responseHandler = &onUnableToAssign; // LAB_00924640
    setDialogErrorFlag(dialog, 1); // Enable error UI element
    break;

  case 3: // Settings confirmation
    dialog->type = 2;
    setDialogText(dialog, "$ui_controlsetup_settings_confirm");
    dialog->responseHandler = &onSettingsConfirm; // LAB_009247d0
    // Additional context IDs for settings
    dialog->contextId1 = 0xF29858BB;
    dialog->contextId2 = 0x11997E8D;
    break;

  case 4: // Reset confirmation
    dialog->type = 2;
    setDialogText(dialog, "$ui_controlsetup_reset_confirm");
    dialog->responseHandler = &onResetConfirm; // LAB_00924810
    // Additional context IDs for reset
    dialog->contextId1 = 0xF29858BB;
    dialog->contextId2 = 0x11997E8D;
    break;

  default:
    // Fall through to show dialog — other actions not handled
    break;
  }

  // Show the dialog (update UI)
  showDialog(dialog);

  // Set the owner's state to 3 (dialog displayed / awaiting response)
  *(int*)(thisPtr + 0x50) = 3;
}