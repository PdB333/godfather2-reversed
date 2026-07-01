// FUNC_NAME: SomeStreamAllocatorClass::allocateBuffers
void __fastcall allocateBuffers(int this)
{
  void *allocBuf1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  
  // Allocate first buffer of size 0x114 bytes
  allocBuf1 = (void *)(**(code **)**(undefined4 **)(this + 0x28))(0x114, &local_c);
  memset(allocBuf1, 0, 0x114);
  
  // Store at +0x20a0 (buffer pointer) and +0x20a4 (buffer size = 0x114)
  *(void **)(this + 0x20a0) = allocBuf1;
  *(undefined4 *)(this + 0x20a4) = 0x114;
  
  local_c = 0;
  
  // Allocate second buffer of size 0x40000 (262144 bytes)
  allocBuf1 = (void *)(**(code **)**(undefined4 **)(this + 0x28))(0x40000, &stack0xffffffec);
  memset(allocBuf1, 0, 0x40000);
  
  // Store at +0x20a8 (buffer pointer) and +0x20ac (buffer size = 0x40000)
  *(void **)(this + 0x20a8) = allocBuf1;
  *(undefined4 *)(this + 0x20ac) = 0x40000;
  
  return;
}