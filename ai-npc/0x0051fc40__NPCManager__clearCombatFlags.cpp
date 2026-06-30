// FUNC_NAME: NPCManager::clearCombatFlags
void NPCManager::clearCombatFlags(void)
{
  int iVar1;
  byte bVar2;
  int unaff_ESI;
  
  iVar1 = *(int *)(unaff_ESI + 0x14); // +0x14: first NPC in list
  if (iVar1 != *(int *)(unaff_ESI + 0x1c)) { // +0x1c: end of list sentinel
    do {
      bVar2 = (byte)*(undefined2 *)(iVar1 + 0x460); // +0x460: NPC flags (ushort)
      if (((bVar2 >> 2 & 1) != 0) && ((bVar2 >> 1 & 1) == 0)) { // bit 2 set, bit 1 clear
        *(ushort *)(iVar1 + 0x460) = *(ushort *)(iVar1 + 0x460) & 0xfffb; // clear bit 2
        *(undefined1 *)(iVar1 + 0x450) = 0; // +0x450: combat state/timer
      }
      iVar1 = *(int *)(iVar1 + 0x40); // +0x40: next NPC in linked list
    } while (iVar1 != *(int *)(unaff_ESI + 0x1c));
  }
  return;
}