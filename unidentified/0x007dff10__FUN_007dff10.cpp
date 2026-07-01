// FUNC_NAME: SomeClass::closeInterfaceOrMenu
void __fastcall closeInterfaceOrMenu(int this)
{
  if ((*(char *)(this + 0x7c) != '\0') && (*(int *)(*(int *)(this + 0x58) + 0x24f8) != 0)) {
    FUN_0045f2a0(0); // likely closes/hides some UI element or menu
    *(undefined1 *)(this + 0x7c) = 0; // +0x7c: flag indicating interface/menu is open
  }
  return;
}