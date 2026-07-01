// FUNC_NAME: MenuScreen::handleInput
undefined4 __thiscall MenuScreen::handleInput(int *this, int inputAction)
{
  code *vtableEntry;
  int actionId;
  
  actionId = FUN_00466840(); // likely getActionId_Select()
  if (inputAction == actionId) {
    FUN_005a04a0("Select",0,&DAT_00d90d34,0); // play sound
    vtableEntry = *(code **)(*this + 0x2c); // +0x2c: onSelect callback
    *(undefined1 *)(this + 0x1a) = 1; // +0x1a: selected flag
    (*vtableEntry)();
    return 0;
  }
  actionId = FUN_00466860(); // likely getActionId_Back()
  if (inputAction == actionId) {
    vtableEntry = *(code **)(*this + 0x2c);
    *(undefined1 *)(this + 0x1a) = 0; // +0x1a: deselected flag
    (*vtableEntry)();
    return 0;
  }
  if (inputAction == 6) {
    FUN_005a04a0("MoveLeft",0,&DAT_00d90d34,0); // play sound
  }
  else if (inputAction == 7) {
    FUN_005a04a0("MoveRight",0,&DAT_00d90d34,0); // play sound
    return 0;
  }
  return 0;
}