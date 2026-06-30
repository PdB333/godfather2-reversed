// FUNC_NAME: DebugMenu::handleAction
int __fastcall DebugMenu::handleAction(int this)
{
  int menu;
  int result;
  
  menu = DebugMenu::getCurrentMenu();
  result = menu;
  if (menu != 0) {
    result = *(int *)(this + 0x6c) + -1; // +0x6c: actionId
    switch(result) {
    case 0:
      result = DebugMenu::action0(*(undefined4 *)(this + 0x70)); // +0x70: actionParam
      return result;
    case 1:
      result = DebugMenu::action1();
      return result;
    case 2:
      result = DebugMenu::action2(*(undefined4 *)(this + 0x70));
      return result;
    case 3:
      result = DebugMenu::action3();
      return result;
    case 4:
      result = DebugMenu::action4();
      return result;
    case 5:
      result = DebugMenu::action5();
      return result;
    case 6:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) & 0xffffffbf; // +0x34: flags, clear bit 6
      return result;
    case 7:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) | 0x40; // +0x34: flags, set bit 6
      return result;
    case 8:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) & 0xffffff7f; // +0x34: flags, clear bit 7
      return result;
    case 9:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) | 0x80; // +0x34: flags, set bit 7
      return result;
    case 10:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) & 0xfffff7ff; // +0x34: flags, clear bit 11
      return result;
    case 0xb:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) | 0x800; // +0x34: flags, set bit 11
      return result;
    case 0xc:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) | 8; // +0x34: flags, set bit 3
      return result;
    case 0xd:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) & 0xfffffff7; // +0x34: flags, clear bit 3
      return result;
    case 0xe:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) & 0xffffefff; // +0x34: flags, clear bit 12
      return result;
    case 0xf:
      *(uint *)(menu + 0x34) = *(uint *)(menu + 0x34) | 0x1000; // +0x34: flags, set bit 12
      return result;
    case 0x10:
      result = DebugMenu::action16(1);
      return result;
    case 0x11:
      result = DebugMenu::action16(0);
      return result;
    case 0x12:
      if (*(int *)(menu + 0x16c) != 1) { // +0x16c: some state
        result = DebugMenu::action18();
        return result;
      }
      DebugMenu::action18Sub(0,0);
      return 1;
    case 0x13:
      result = DebugMenu::action19(1);
      return result;
    case 0x14:
      result = DebugMenu::action19(0);
    }
  }
  return result;
}