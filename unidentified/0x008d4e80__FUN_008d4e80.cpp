// FUNC_NAME: SomeClass::resetSomeState
void __fastcall SomeClass::resetSomeState(int this)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (DAT_00e44598 <= *(float *)(this + 0x70)) {
    // If some global threshold is <= this->field_0x70, call a function with this->field_0x68, 0, this->field_0x70, 0, 0
    FUN_00440590(this + 0x68, 0, *(float *)(this + 0x70), 0, 0);
  }
  else {
    // Otherwise, copy this->field_0x68 to local_c, set local_8 and local_4 to 0, and call FUN_00408a00 with &local_c
    local_c = *(undefined4 *)(this + 0x68);
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c);
  }
  // Clear this->field_0x80 and this->field_0x84
  *(undefined1 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  return;
}