// FUNC_NAME: EAObject::deallocateFromPool
void EAObject::deallocateFromPool(int param_1)
{
  // Call virtual destructor (vtable+0xC)
  (**(code **)(**(int **)(param_1 + -0x10) + 0xc))();
  // Call operator delete (vtable+0x4) with the object pointer and zero (pool deallocation)
  (**(code **)(**(int **)(param_1 + -0x10) + 4))((undefined4 *)(param_1 + -0x10),0);
  return;
}