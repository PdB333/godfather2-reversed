// FUNC_NAME: UIMenuManager::handleMoveInput
void __fastcall UIMenuManager::handleMoveInput(int this)
{
  int vtablePtr;
  int result;
  uint temp;
  int *listBase;
  undefined4 local_c;
  int local_8;
  uint local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = local_4 & 0xffffff00;
  FUN_00408a00(&local_c, 0);
  
  switch(*(undefined4 *)(this + 0xdc)) {
  case 1: // MenuState = 1 (main menu or top-level navigation)
    listBase = (int *)(this + 0x2ec);
    break;
  case 2: // MenuState = 2 (submenu, e.g. options)
  case 3: // MenuState = 3 (another submenu)
    vtablePtr = *(int *)(this + 0x508);
    result = FUN_00962e40();
    (**(code **)(vtablePtr + 0x68))((int *)(this + 0xd4), *(undefined4 *)(this + 0xc4), 10, result);
    FUN_0095e7d0(*(int *)(this + 0xc4) + *(int *)(this + 0xd4));
    return;
  case 4: // MenuState = 4 (weapon selection or item list)
    if (*(char *)(this + 0x220) == '\0') {
      return;
    }
    vtablePtr = *(int *)(this + 0x508);
    listBase = (int *)(this + 0xd4);
    result = FUN_00962e40();
    (**(code **)(vtablePtr + 0x68))(listBase, *(undefined4 *)(this + 0xc4), 10, result);
    FUN_0095e7d0(*(int *)(this + 0xc4) + *listBase);
    result = FUN_00962eb0();
    FUN_009643f0(*(int *)(this + 0xc4) + *listBase, result);
    return;
  default: // Unknown menu state
    FUN_005a04a0("MoveDown", 0, 0, 0);
    return;
  case 6: // MenuState = 6 (another specific menu)
    listBase = (int *)(this + 0x378);
    break;
  case 8: // MenuState = 8 (e.g., phone contacts)
    vtablePtr = *(int *)(this + 0x63c);
    result = FUN_00962e40();
    result = FUN_00962e40(result);
    (**(code **)(vtablePtr + 0x68))((int *)(this + 0xd4), *(undefined4 *)(this + 0xc4), result);
    FUN_0095e7d0(*(int *)(this + 0xc4) + *(int *)(this + 0xd4));
    return;
  case 9: // MenuState = 9 (e.g., inventory or crew list)
    vtablePtr = *(int *)(this + 0x590);
    result = FUN_00962e40();
    result = FUN_00962e40(result);
    (**(code **)(vtablePtr + 0x68))((int *)(this + 0xd4), *(undefined4 *)(this + 0xc4), result);
    temp = *(int *)(this + 0xc4) + *(int *)(this + 0xd4);
    if (temp < *(uint *)(this + 0x638)) {
      FUN_0095e7d0(*(undefined4 *)(this + 0x5f8 + temp * 4));
      return;
    }
    FUN_0095e7d0(0);
    return;
  case 0xb: // MenuState = 0xB (e.g., safehouse management)
    if (*(int *)(this + 0x574) == 0) {
      // First column (business/mission tab)
      if (*(int *)(DAT_01129930 + 0x2b4) != *(int *)(this + 0x580) + -1) {
        FUN_005a04a0("MoveDown", 0);
        FUN_009676f0();
        FUN_009679c0();
        FUN_005a04a0("ShowWeaponsList", 0);
      }
    }
    else {
      // Second column (crew/income tab)
      if (*(int *)(DAT_01129930 + 0x2b8) != *(int *)(this + 0x584) + -1) {
        FUN_005a04a0("MoveDown", 0);
        FUN_00967a60();
        FUN_009676f0();
        return;
      }
    }
    return;
  }
  
  // Default list movement for cases 1 and 6
  vtablePtr = *listBase;
  result = FUN_00962e40();
  (**(code **)(vtablePtr + 0x68))(this + 0xd4, *(undefined4 *)(this + 0xc4), *(undefined4 *)(this + 0x17c), result);
  return;
}