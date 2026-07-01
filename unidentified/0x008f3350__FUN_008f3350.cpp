// FUNC_NAME: SomeClass::releaseOrResetHandle
void __fastcall releaseOrResetHandle(int param_1)
{
  // Call a virtual function at offset +4 from the vtable pointed to by param_1+0x28
  // The function is called with the value at param_1+0x209c as first argument and 0x40c as second
  (**(code **)(**(int **)(param_1 + 0x28) + 4))(*(undefined4 *)(param_1 + 0x209c), 0x40c);
  // Clear the handle at offset +0x209c
  *(undefined4 *)(param_1 + 0x209c) = 0;
}