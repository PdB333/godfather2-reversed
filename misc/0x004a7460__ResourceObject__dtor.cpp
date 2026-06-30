// FUNC_NAME: ResourceObject::dtor
void __thiscall ResourceObject::dtor(ResourceObject *this)
{
  // +0x00: vtable pointer
  *(void **)this = &PTR_FUN_00e35538; // Intermediate destructor vtable
  // +0xA0: pointer to a struct with a function pointer at offset 0 (possibly a release callback)
  if (*(void **)((char *)this + 0xA0) != (void *)0x0) {
    // Call the first function in that struct with argument 1 (e.g., Release(1))
    (*(void (__cdecl *)(int))*(unsigned int *)*(unsigned int *)((char *)this + 0xA0))(1);
  }
  // +0x90: flag indicating if a sub-object at +0x10 needs cleanup
  if (*(int *)((char *)this + 0x90) != 0) {
    // Cleanup sub-object at offset 0x10 (e.g., a string or array)
    FUN_00610100((int)this + 0x10);
  }
  // Final destructor vtable (set before actual deallocation)
  *(void **)this = &PTR_LAB_00e2f638;
}