// FUNC_NAME: InputManager::updateControllerSlot
void InputManager::updateControllerSlot(int slotIndex)
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004c4a10(in_EAX);
  slotIndex = slotIndex * 0x20;
  if (*(int *)(*(int *)(unaff_ESI + 0x10) + slotIndex) != iVar1) {
    if (*(char *)(unaff_ESI + 0x3c) != '\0') {
      FUN_004c4870(unaff_ESI,0);
      *(int *)(slotIndex + *(int *)(unaff_ESI + 0x10)) = iVar1;
      iVar1 = *(int *)(unaff_ESI + 0x10);
      iVar2 = FUN_004c4610(*(undefined4 *)(iVar1 + slotIndex),unaff_ESI + 0x24);
      iVar1 = FUN_004c4610(*(undefined4 *)(iVar1 + slotIndex + 4),iVar2 + 0xc);
      FUN_004c4730(unaff_ESI,iVar1 + 0xc);
      *(undefined1 *)(unaff_ESI + 0x18) = 0;
      return;
    }
    *(int *)(*(int *)(unaff_ESI + 0x10) + slotIndex) = iVar1;
  }
  return;
}