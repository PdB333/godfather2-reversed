// FUNC_NAME: MenuManager::hideMenu
void __fastcall MenuManager::hideMenu(int *this)
{
  *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) | 1; // +0x1a: flags, set bit 0 (menu hidden flag)
  (**(code **)(*this + 0xc))(); // vtable+0xc: virtual method (likely onHide or cleanup)
  *(ushort *)(this + 0x1a) = *(ushort *)(this + 0x1a) | 2; // +0x1a: flags, set bit 1 (menu hidden flag 2)
  FUN_005a04a0("MenuHide", 0, &DAT_00d873d4, 0); // send event "MenuHide" with some data
  (**(code **)(*DAT_01129828 + 0x14))(&LAB_00985a90, 0, 0); // call some global singleton method (likely InputManager or PresentationManager)
}