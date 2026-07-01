// FUNC_NAME: UIControlSetupDialog::onConfirm
void __fastcall UIControlSetupDialog::onConfirm(int *this)
{
  int allocatedObject;
  
  if (this[0x1f] != 0) {            // this +0x7c: bConfirmClicked or bSettingsConfirmed
    allocatedObject = FUN_009c8e50(0xf0);   // Allocate object of size 0xf0 (UI element?)
    if (allocatedObject == 0) {
      allocatedObject = 0;
    }
    else {
      allocatedObject = FUN_00982280(0);    // Possibly construct or initialize
    }
    *(int *)(allocatedObject + 0xc) = 2;    // +0x0c: type or ID = 2
    FUN_00981eb0("$ui_controlsetup_settings_confirm");  // Set text/string resource
    *(int *)(allocatedObject + 0x20) = 0x11997e8d;       // +0x20: unknown param
    *(int *)(allocatedObject + 0x1c) = 0xf29858bb;       // +0x1c: unknown param
    *(void **)(allocatedObject + 0x14) = &LAB_009247d0;  // +0x14: callback function pointer
    FUN_00982e10();                     // Show/push dialog or UI state
    this[0x14] = 3;                     // this +0x50: state/status = 3
    return;
  }
  // Default behavior: virtual call to parent/other handler
  (*(void (**)(void))(*this + 0x2c))();   // vtable[0x2c] -> default method
}