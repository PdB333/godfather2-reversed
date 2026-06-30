// FUNC_NAME: DestructorForMultiBaseClass
void __thiscall DestructorForMultiBaseClass::dtor(DestructorForMultiBaseClass *this)
{
  // this + 0x5C: handle/resource id
  int resourceHandle = *(int *)((int)this + 0x5C);
  // Set vtable to base class 1 vtable (0x00d65cdc)
  *(int *)this = 0x00d65cdc;
  // Release resource with type 4 (e.g., sound buffer, network channel)
  resourceRelease(resourceHandle, 4);
  // Finalize/free resource handle
  resourceFinalize(resourceHandle);
  // this + 0x70: pointer to a dynamically allocated object
  if (*(int *)((int)this + 0x70) != 0) {
    // Delete object and nullify pointer
    deallocateObject((int *)this + 0x1c);
  }
  // Set vtable to base class 2 vtable (0x00d63090)
  *(int *)this = 0x00d63090;
  // this + 0x68: another dynamically allocated object
  if (*(int *)((int)this + 0x68) != 0) {
    deallocateObject((int *)this + 0x1a);
  }
  // Global cleanup (e.g., decrement reference counters, free pools)
  globalCleanup();
}