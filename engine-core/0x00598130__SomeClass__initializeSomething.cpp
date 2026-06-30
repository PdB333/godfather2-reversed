// FUNC_NAME: SomeClass::initializeSomething
undefined4 SomeClass::initializeSomething(void)
{
  int thisPtr; // unaff_ESI
  undefined1 *puVar1;
  int iVar2;
  undefined4 uStack_20;
  undefined4 uStack_14;
  
  uStack_14 = 2;
  uStack_20 = 0x598166;
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr); // vtable call at offset 0x10
  uStack_20 = 2;
  iVar2 = thisPtr + 2;
  (**(code **)(*DAT_01205590 + 0x10))(iVar2,&uStack_14); // vtable call at offset 0x10
  puVar1 = &stack0xffffffe4;
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 4,puVar1); // vtable call at offset 0x10
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 8,&uStack_20); // vtable call at offset 0x10
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0xc,iVar2); // vtable call at offset 0x10
  (**(code **)(*DAT_01205590 + 0x10))(thisPtr + 0x4c,puVar1,0x50); // vtable call at offset 0x10
  return 0x54c;
}