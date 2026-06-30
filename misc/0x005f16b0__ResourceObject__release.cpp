// FUNC_NAME: ResourceObject::release
// Address: 0x005f16b0
void ResourceObject::release(void)
{
  // Retrieve handle (short) and size (int) from object fields
  short handle = *(short *)(this + 0x8);
  int size = *(int *)(this + 0x18);
  
  // First release call (likely to global resource manager or deallocator)
  releaseResource(handle, size);
  
  // Call a virtual method on the global resource manager (vtable at DAT_01223510, offset 0x20)
  // This method takes the handle as argument
  (*(void (__fastcall *)(short))(*DAT_01223510 + 0x20))(handle);
  
  // Second release call (duplicate, perhaps for refcount or safety)
  releaseResource(handle, size);
  
  // If the resource is not marked as "permanent" (bit 6 of flags at +0x10), perform additional cleanup
  if ((*(byte *)(this + 0x10) & 0x40) == 0) {
    additionalCleanup();
  }
  
  // Zero out three fields at offsets 0x24, 0x28, 0x2c (likely pointers or counters)
  *(int *)(this + 0x24) = 0;
  *(int *)(this + 0x28) = 0;
  *(int *)(this + 0x2c) = 0;
}