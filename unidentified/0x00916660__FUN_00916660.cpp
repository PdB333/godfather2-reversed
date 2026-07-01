// FUNC_NAME: SomeClass::setStateAndProcessInput
void __thiscall SomeClass::setStateAndProcessInput(int this, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  puVar1 = (undefined4 *)FUN_00950b20(); // likely getSomeGlobalData()
  if (puVar1 == (undefined4 *)0x0) {
    local_1c = 0.0;
    local_14 = 0;
    local_18 = 0;
    local_20 = 0;
  }
  else {
    local_20 = *puVar1;
    local_1c = (float)puVar1[1];
    local_18 = puVar1[2];
    local_14 = _DAT_00d5780c; // global float
  }
  local_1c = DAT_00d8bbc8 + local_1c; // add global offset
  FUN_0097a8d0(&local_20); // likely processVector or similar
  switch(*(undefined4 *)(this + 8)) { // +0x08: state field
  case 1:
  case 2:
  case 3:
  case 4:
    *(undefined4 *)(this + 8) = 0; // reset state to 0
  }
  *(undefined4 *)(this + 4) = param_2; // +0x04: some parameter field
  *(undefined4 *)(this + 8) = 4; // set state to 4
  FUN_00978a90(param_2); // likely applyState or similar
  return;
}