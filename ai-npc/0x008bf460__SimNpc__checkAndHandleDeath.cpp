// FUNC_NAME: SimNpc::checkAndHandleDeath
byte __fastcall SimNpc::checkAndHandleDeath(int this)
{
  byte bResult;
  int iVar2;
  byte bVar3;
  uint uIndex;
  
  uIndex = 0;
  bResult = 0;
  bVar3 = 0;
  if (*(int *)(this + 0x1a8) != 0) { // +0x1A8: numComponents (count of components)
    do {
      iVar2 = *(int *)(*(int *)(this + 0x1a4) + uIndex * 4); // +0x1A4: components array (array of pointers)
      bVar3 = 0;
      if ((iVar2 != 0) && (*(int *)(iVar2 + 4) == 6)) { // +0x04: componentType (6 = DeathComponent)
        bVar3 = 1;
        FUN_008c80d0(0); // likely DeathComponent::triggerDeath or similar
        FUN_008c8a20(1,0); // likely SimNpc::setDead or similar
      }
      bResult = bResult | bVar3;
      uIndex = uIndex + 1;
      bVar3 = bResult;
    } while (uIndex < *(uint *)(this + 0x1a8));
  }
  return bResult;
}