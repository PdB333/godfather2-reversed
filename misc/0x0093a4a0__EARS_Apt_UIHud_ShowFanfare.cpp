// Xbox PDB: EARS_Apt_UIHud_ShowFanfare
// FUNC_NAME: FanfareManager::showFanfare
void __thiscall FanfareManager::showFanfare(int this, undefined4 *params)
{
  undefined4 *puVar1;
  undefined1 *puVar2;
  char *pcVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  puVar1 = params + 1;
  *(undefined4 *)(this + 0x84) = *params; // +0x84: fanfareType
  FUN_004d3e20(puVar1); // string copy/init
  *(undefined4 *)(this + 0x98) = params[5]; // +0x98: titleString
  FUN_004d3e20(params + 6); // string copy/init
  *(undefined4 *)(this + 0xac) = params[10]; // +0xac: showTooltip
  *(undefined4 *)(this + 0xb0) = params[0xb]; // +0xb0: tooltipX
  *(undefined4 *)(this + 0xb4) = params[0xc]; // +0xb4: tooltipY
  if (*(int *)(this + 0x98) != 0) {
    FUN_00603330(params[5], puVar1); // copy title string
  }
  puVar2 = (undefined1 *)*puVar1;
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // empty string
  }
  FUN_005c4660(*(undefined4 *)(this + 0xb8), puVar2, 0x100, 0); // copy title to buffer
  puVar2 = (undefined1 *)params[6];
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // empty string
  }
  FUN_005c4660(*(undefined4 *)(this + 0xbc), puVar2, 0x80, 0); // copy subtitle to buffer
  if (*(int *)(this + 0xac) == 0) {
    pcVar3 = "";
  }
  else {
    pcVar3 = "$fanfair_start_tooltip"; // fanfare tooltip string
  }
  FUN_005a04a0("ShowFanfare", 0, &DAT_00d8a64c, 1, pcVar3); // show fanfare UI
  local_c = DAT_01130350;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0); // play fanfare sound
  *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 1; // +0x5c: flags, set bit 0
  return;
}