// FUNC_NAME: MemoryStream::MemoryStream
undefined4 * __thiscall MemoryStream::MemoryStream(MemoryStream *this, byte flags)
{
  int *allocator;
  
  // Set vtable pointer (likely base class or interface)
  this->vtable = (void *)&PTR_FUN_00d5f784;
  // Set second vtable pointer (maybe for derived interface)
  this->interfaceVtable = (void *)&PTR_LAB_00d5f77c;
  
  // Free existing buffer1 at offset 0x1EC (0x7b * 4) if present
  if (this->buffer1 != NULL) {
    MemoryStream::freeBuffer(this->buffer1); // FUN_004daf90
  }
  
  // Free existing buffer2 at offset 0x124 (0x49 * 4) if present
  if (this->buffer2 != NULL) {
    MemoryStream::freeBuffer(this->buffer2); // FUN_004daf90
  }
  
  // Call base class or global initialization
  MemoryStream::baseInit(); // FUN_006c9820
  
  // If flag bit 0 is set, allocate memory using allocator's method
  if ((flags & 1) != 0) {
    allocator = (int *)MemoryStream::getAllocator(); // FUN_009c8f80
    // Call virtual function at index 1 (offset 0x4) on allocator to allocate 0x200 bytes
    (**(code **)(allocator->vtable + 4))(this, 0x200);
  }
  
  return (undefined4 *)this;
}