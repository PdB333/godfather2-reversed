// FUNC_NAME: GodfatherGameManager::updateSomeState
void __fastcall GodfatherGameManager::updateSomeState(int thisPtr)
{
  char cVar1;
  int uVar2;
  
  uVar2 = 1;
  if (*(char *)(DAT_0112af90 + 0x48) != '\0') {
    cVar1 = FUN_005c1ba0(); // likely some condition check
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
  }
  FUN_00815d60(thisPtr + 0x24, uVar2, 0); // update state at offset +0x24
  return;
}