// FUNC_NAME: Entity::getDebugName
void __thiscall Entity::getDebugName(int this, undefined4 param_2, undefined4 param_3)
{
  undefined1 *debugName;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  FUN_00603d30(*(undefined4 *)(this + 0x20),&local_10,1); // get entity name from name table at +0x20
  debugName = local_10;
  if (local_10 == (undefined1 *)0x0) {
    debugName = &DAT_0120546e; // default "unknown" string
  }
  FUN_005c4660(param_2,debugName,param_3,local_c); // copy string to output buffer
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10); // free allocated string
  }
  return;
}