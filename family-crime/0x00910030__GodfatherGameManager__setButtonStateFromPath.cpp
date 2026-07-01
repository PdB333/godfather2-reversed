// FUNC_NAME: GodfatherGameManager::setButtonStateFromPath
bool __thiscall GodfatherGameManager::setButtonStateFromPath(int this, char *path)
{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  
  iVar1 = 0x1e;
  bVar4 = true;
  pcVar2 = "/appm/buttons/button_4/button";
  pcVar3 = path;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pcVar2 == *pcVar3;
    pcVar2 = pcVar2 + 1;
    pcVar3 = pcVar3 + 1;
  } while (bVar4);
  if (bVar4) {
    // Set button 4 state to active (1) at offset +0x2f8
    *(undefined1 *)(this + 0x2f8) = 1;
    return true;
  }
  iVar1 = 0x1e;
  bVar4 = true;
  pcVar2 = "/appm/buttons/button_5/button";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pcVar2 == *path;
    pcVar2 = pcVar2 + 1;
    path = path + 1;
  } while (bVar4);
  if (bVar4) {
    // Set button 5 state to active (1) at offset +0x2f9
    *(undefined1 *)(this + 0x2f9) = 1;
  }
  return bVar4;
}