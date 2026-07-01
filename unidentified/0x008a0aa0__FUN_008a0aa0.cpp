// FUNC_NAME: SomeClass::setSomeVectorOrColor
void __thiscall SomeClass::setSomeVectorOrColor(int this, undefined4 param_2)
{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = _DAT_00d5780c; // global constant, possibly a color or vector component
  FUN_008a09a0(this + 0x40, &local_20, param_2, 0); // set member at +0x40 to the constructed value
  return;
}