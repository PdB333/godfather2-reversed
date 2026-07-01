// FUNC_NAME: Presentation::onBackPressed
void __fastcall Presentation::onBackPressed(int *this)
{
  switch(this[0x2e]) {
  case 0:
    FUN_00402050(&DAT_01130310,0);
    break;
  case 1:
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
    // These states transition to the "exit" state (10)
    FUN_00402050(&DAT_01130310,0);
    this[0x37] = 0;    // +0xDC - some state flag/transition counter
    this[0x2e] = 10;   // +0xB8 - state = 10 (exit/overlay closing)
    this[0x30] = 0;    // +0xC0 - reset sub-state
    this[0x2d] = 0;    // +0xB4 - reset animation progress or timer
    FUN_00986240(0);
    FUN_005a04a0("ShowOverall",0,&DAT_00d8510c,0);
    break;
  default:
    goto switchD_00919749_caseD_2;
  }
  (**(code **)(*this + 0x2c))(); // vtable call at offset 0x2c (some update/transition method)
switchD_00919749_caseD_2:
  FUN_005a04a0("PopHistory",0,&DAT_00d8510c,0);
  FUN_00916ec0();
  return;
}