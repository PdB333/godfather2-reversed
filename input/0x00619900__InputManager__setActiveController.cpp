// FUNC_NAME: InputManager::setActiveController
void InputManager::setActiveController(void)

{
  undefined4 in_EAX;
  
  _DAT_01127804 = in_EAX;
  if (((DAT_012058e8 == &PTR_PTR_01127760) && (DAT_01127774 == DAT_01127874)) && (DAT_01127844 != 0)
     ) {
    FUN_006063b0();
  }
  return;
}