// FUNC_NAME: UIGodfatherOnlineController::checkAndExecutePendingAction
void __fastcall UIGodfatherOnlineController::checkAndExecutePendingAction(int *this)
{
  int actionTarget;
  
  if (this[6] != 0) {
    actionTarget = (**(code **)(*this + 0x28))(this[6]); // vtable[5] = getSelectedItem()
    if (actionTarget != 0) {
      (**(code **)(*(int *)this[5] + 0xc))(actionTarget); // call action on target
      DAT_01205a20 = 0; // clear pending action flag
    }
  }
  return;
}