// FUNC_NAME: MemoryAllocator::allocateAligned
uint __fastcall MemoryAllocator::allocateAligned(int *this, undefined4 param_2)
{
  int iVar1;
  int iVar2;
  int *unaff_ESI;
  
  iVar1 = (**(code **)(*this + 8))(param_2);  // Call virtual function at vtable+8 (likely baseAllocate)
  iVar2 = *unaff_ESI;  // Get alignment value from ESI register (passed via __fastcall)
  if (iVar2 < 0x11) {  // Minimum alignment is 16 bytes
    iVar2 = 0x10;
  }
  *unaff_ESI = iVar2;  // Store alignment back
  return iVar1 + 0xfU & 0xfffffff0;  // Round up to nearest 16-byte boundary
}