// FUNC_NAME: GlobalInitializer::registerStaticClass
void GlobalInitializer::registerStaticClass(void)
{
  int baseAddr;
  uint *stackPtr;
  undefined4 *alignedPtr;
  undefined4 savedEdi;
  
  baseAddr = DAT_01206880;
  // +0x14: pointer to current position in static initialization table
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c30;
  *(int *)(baseAddr + 0x14) = *(int *)(baseAddr + 0x14) + 4;
  stackPtr = (uint *)(baseAddr + 0x14);
  // Align to 4 bytes
  alignedPtr = (undefined4 *)(*(int *)(baseAddr + 0x14) + 3U & 0xfffffffc);
  *stackPtr = (uint)alignedPtr;
  *alignedPtr = savedEdi;
  // Align to 4 bytes, store 1 (likely class ID or flag)
  alignedPtr = (undefined4 *)(*stackPtr + 7 & 0xfffffffc);
  *stackPtr = (uint)alignedPtr;
  *alignedPtr = 1;
  // Align to 4 bytes, store another 1
  alignedPtr = (undefined4 *)(*stackPtr + 7 & 0xfffffffc);
  *stackPtr = (uint)alignedPtr;
  *alignedPtr = 1;
  *stackPtr = *stackPtr + 4;
  return;
}