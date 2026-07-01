// FUNC_NAME: Vector::resizeAndConstruct
undefined4 * __thiscall Vector::resizeAndConstruct(undefined4 *this, uint newSize)
{
  uint *newBuffer;
  uint uVar2;
  uint *result;
  
  uVar2 = -(uint)((int)((ulonglong)newSize * 8 >> 0x20) != 0) | (uint)((ulonglong)newSize * 8);
  newBuffer = (uint *)FUN_009c8e80(-(uint)(0xfffffffb < uVar2) | uVar2 + 4);
  if (newBuffer == (uint *)0x0) {
    result = (uint *)0x0;
  }
  else {
    result = newBuffer + 1;
    *newBuffer = newSize;
    _vector_constructor_iterator_(result,8,newSize,(_func_void_ptr_void_ptr *)&LAB_0094eae0);
  }
  this[1] = newSize;  // +0x04: capacity
  *this = result;      // +0x00: data pointer
  this[2] = 0;         // +0x08: size
  this[3] = 0;         // +0x0C: unknown
  return this;
}