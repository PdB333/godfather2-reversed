// FUNC_NAME: SomeClass::processInputOrSomething
void __thiscall SomeClass::processInputOrSomething(int *this, undefined4 param_2)
{
  byte *flagsPtr;
  bool bVar2;
  float10 fVar3;
  undefined1 local_54 [4];
  undefined1 local_50 [44];
  undefined1 local_24 [32];
  
  bVar2 = false;
  // Call virtual function at offset 0x40 on some global object at DAT_012055a8
  (**(code **)(*DAT_012055a8 + 0x40))(local_50);
  
  flagsPtr = (byte *)(this + 1); // +0x04 flags byte
  if ((*(byte *)(this + 1) & 2) == 0) {
    fVar3 = (float10)FUN_00595490(param_2);
    if ((*flagsPtr & 1) != 0) {
      fVar3 = (float10)FUN_00595490((float)fVar3);
      FUN_00595490((float)fVar3);
    }
    FUN_0059bb50(local_24);
    bVar2 = true;
  }
  if ((*flagsPtr & 4) == 0) {
    fVar3 = (float10)FUN_00595490(param_2);
    if ((*flagsPtr & 1) == 0) {
      FUN_0059bde0(local_54);
    }
    else {
      fVar3 = (float10)FUN_00595490((float)fVar3);
      FUN_00595490((float)fVar3);
      FUN_0059bde0(local_54);
    }
  }
  else if (!bVar2) {
    return;
  }
  // Call virtual function at offset 0x1c on this object
  (**(code **)(*this + 0x1c))(local_54);
  return;
}