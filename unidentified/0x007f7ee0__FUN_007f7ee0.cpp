// FUNC_NAME: SomeClass::getSomeData
void __fastcall SomeClass::getSomeData(int *this)
{
  int iVar1;
  undefined4 unaff_ESI;
  undefined1 local_c [8];
  undefined8 *puStack_4;
  
  // Call virtual method at vtable+0xa4 (likely a getter or copy function)
  (**(code **)(*this + 0xa4))(local_c, this + 0x1c6); // +0x1c6 is some data field
  iVar1 = FUN_00471610(); // Get some global object/manager
  *puStack_4 = *(undefined8 *)(iVar1 + 0x30); // Copy 8 bytes from offset 0x30
  *(undefined4 *)(puStack_4 + 1) = *(undefined4 *)(iVar1 + 0x38); // Copy next 4 bytes from offset 0x38
  *(undefined4 *)((int)puStack_4 + 4) = unaff_ESI; // Store ESI value
  return;
}