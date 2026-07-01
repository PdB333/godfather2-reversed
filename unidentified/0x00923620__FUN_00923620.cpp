// FUNC_NAME: SomeClass::setSelectedIndex
void __thiscall setSelectedIndex(int this, int newIndex)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (*(int *)(this + 0x54) != newIndex) {
    FUN_005a04a0("CloseSelection",0,&DAT_00d87288,0);
    *(int *)(this + 0x54) = newIndex;
    FUN_005a04a0("OpenSelection",0,&DAT_00d87288,0);
    local_c = DAT_011302b0;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
  }
  return;
}