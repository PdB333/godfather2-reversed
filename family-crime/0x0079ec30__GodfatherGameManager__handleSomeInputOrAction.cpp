// FUNC_NAME: GodfatherGameManager::handleSomeInputOrAction
uint __thiscall GodfatherGameManager::handleSomeInputOrAction(int this, undefined4 param_2)
{
  uint uVar1;
  
  uVar1 = *(uint *)(this + 0x249c) >> 1;
  if ((uVar1 & 1) != 0) {
    uVar1 = FUN_00481620(); // likely some input/state check
    if ((char)uVar1 != '\0') {
      uVar1 = FUN_00466040(*(undefined1 *)(this + 0x2498),param_2); // process action with param
      return uVar1;
    }
  }
  return uVar1 & 0xffffff00;
}