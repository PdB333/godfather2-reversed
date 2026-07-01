// FUNC_NAME: Entity::buildDebugString
void __thiscall Entity::buildDebugString(int this, undefined4 param_2)
{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  code *local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  local_20 = (undefined1 *)0x0;
  local_1c = 0;
  local_18 = 0;
  local_14 = (code *)0x0;
  local_30 = (undefined1 *)0x0;
  local_2c = 0;
  local_28 = 0;
  local_24 = (code *)0x0;
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  if ((*(byte *)(this + 0xe8) & 1) == 0) { // +0xe8: flags (bit0 = isPlayer?)
    FUN_00603d30(*(undefined4 *)(this + 0xf0),&local_20,1); // +0xf0: name string
  }
  else {
    FUN_00604000(*(undefined4 *)(this + 0xf0),&local_20,1); // +0xf0: name string
  }
  if ((*(byte *)(this + 0xe8) & 1) == 0) {
    FUN_00603d30(*(undefined4 *)(this + 0x90),&local_30,1); // +0x90: location string
  }
  else {
    FUN_00604000(*(undefined4 *)(this + 0x90),&local_30,1); // +0x90: location string
  }
  puVar3 = *(undefined1 **)(this + 0x15c); // +0x15c: class name string
  if (puVar3 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e; // empty string placeholder
  }
  puVar2 = local_30;
  if (local_30 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;
  }
  puVar1 = local_20;
  if (local_20 == (undefined1 *)0x0) {
    puVar1 = &DAT_0120546e;
  }
  FUN_004d4ad0(&local_10,"{P:%s}{L:%s}{%s}",puVar1,puVar2,puVar3); // format debug string
  puVar3 = local_10;
  if (local_10 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;
  }
  FUN_00603970(param_2,puVar3); // copy to output buffer
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10); // free string
  }
  if (local_30 != (undefined1 *)0x0) {
    (*local_24)(local_30); // free string
  }
  if (local_20 != (undefined1 *)0x0) {
    (*local_14)(local_20); // free string
  }
  return;
}