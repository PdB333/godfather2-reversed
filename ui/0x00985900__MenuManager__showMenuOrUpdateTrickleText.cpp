// FUNC_NAME: MenuManager::showMenuOrUpdateTrickleText
void __fastcall MenuManager::showMenuOrUpdateTrickleText(int this)
{
  char cVar1;
  undefined1 *puVar2;
  undefined1 *local_10;
  int local_c;
  undefined4 local_8;
  code *local_4;

  if ((*(byte *)(this + 0x68) & 1) == 0) { // +0x68: flags (bit 0 = menu visible?)
    FUN_005a04a0("MenuShow",0,&DAT_00d873d4,0); // likely a string/event dispatch
    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    cVar1 = FUN_0098f850(&local_10); // likely getTrickleText or similar
    if ((cVar1 == '\0') || (local_c == 0)) {
      *(undefined **)(this + 0x5c) = PTR_DAT_00e575fc; // +0x5c: currentMenuText pointer, fallback to default
    }
    else {
      puVar2 = local_10;
      if (local_10 == (undefined1 *)0x0) {
        puVar2 = &DAT_0120546e; // empty string fallback
      }
      *(undefined1 **)(this + 0x5c) = puVar2;
    }
    FUN_005a04a0("UpdateTrickleText",0,&DAT_00d873d4,0); // update trickle text display
    *(undefined **)(this + 0x5c) = PTR_DAT_00e575fc; // reset to default menu text
    if (local_10 != (undefined1 *)0x0) {
      (*local_4)(local_10); // free allocated string
    }
  }
  return;
}