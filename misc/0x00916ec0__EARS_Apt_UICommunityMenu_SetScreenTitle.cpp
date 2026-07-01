// Xbox PDB: EARS_Apt_UICommunityMenu_SetScreenTitle
// FUNC_NAME: OnlineMenu::updateTitleText
void __fastcall OnlineMenu::updateTitleText(int this)
{
  switch(*(int *)(this + 0xb8)) { // +0xB8: currentTabIndex
  case 0:
    FUN_005c4660(*(int *)(this + 0xe8), "$mp_online_community_upper", 0x80, 0); // +0xE8: titleTextBuffer
    break;
  case 1:
    FUN_005c4660(*(int *)(this + 0xe8), "$mp_online_buddies_upper", 0x80, 0);
    break;
  default:
    **(char **)(this + 0xe8) = 0; // Clear title text
    break;
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
    FUN_005c4660(*(int *)(this + 0xe8), "$mp_online_leaderboards_upper", 0x80, 0);
  }
  FUN_005a04a0("SetTitle", 0, &DAT_00d8510c, 0); // Set title via UI system
  return;
}