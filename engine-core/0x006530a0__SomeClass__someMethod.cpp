// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, int param_2)
{
  int in_EAX;
  int iVar1;
  
  FUN_00653230(this,param_2);
  if (param_2 == 0) {
    iVar1 = (**(code **)(*this + 0x4c))();
    if (this[0x47] == 0) { // +0x11C
      this[0x47] = iVar1; // +0x11C
    }
    else {
      *(int *)(this[0x48] + 0x10) = iVar1; // +0x120
    }
    this[0x48] = iVar1; // +0x120
    *(undefined4 *)(iVar1 + 0x10) = 0;
    *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(this[0x69] + 100); // +0x1A4
    FUN_00653760();
    *(int *)(in_EAX + 0x34) = this[0x72]; // +0x1C8
    (**(code **)(*this + 0x38))();
  }
  if (this[0x6c] != 0) { // +0x1B0
    FUN_0065a6c0(this[0x6c],this[0x26],this[0x24],param_2); // +0x1B0, +0x98, +0x90
    FUN_0064c980(3,this[0x6c]); // +0x1B0
  }
  return;
}