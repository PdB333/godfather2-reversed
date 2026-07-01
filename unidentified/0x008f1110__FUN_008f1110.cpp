// FUNC_NAME: SomeClass::updateContextOrState
void FUN_008f1110(int param_1, int param_2)

{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (param_1 == 0) {
    FUN_00907960(); // likely scene/context initialization
  }
  if (param_2 != 0) {
    local_c = *(undefined4 *)(param_2 + 0x58); // +0x58: likely some state/flag field
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // probably timer/event scheduler
  }
  FUN_009119e0(); // generic update/tick
  return;
}