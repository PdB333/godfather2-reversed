// FUNC_NAME: SelectMenuManager::destroySelectMenu
void __fastcall SelectMenuManager::destroySelectMenu(int this)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_c = DAT_01130218;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  *(undefined4 *)(this + 100) = 0xffffffff; // +0x64: currentSelectionId
  FUN_005a04a0("DestroySelectMenu",0,&DAT_00d873d4,0);
  if ((*(byte *)(this + 0x68) >> 2 & 1) != 0) { // +0x68: flags, bit 2 = isActive
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) & 0xfffffffb; // clear bit 2 in some global state
    FUN_00912030(); // likely updateInputState or similar
    *(ushort *)(this + 0x68) = *(ushort *)(this + 0x68) & 0xfffb; // clear bit 2 in local flags
  }
  return;
}