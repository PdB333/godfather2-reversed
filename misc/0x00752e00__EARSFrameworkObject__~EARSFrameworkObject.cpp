// FUNC_NAME: EARSFrameworkObject::~EARSFrameworkObject
void __fastcall ~EARSFrameworkObject(void *this)
{
  char cVar1;

  // Set vtable pointer for this object
  *(void **)this = &VTABLE_EARSFrameworkObject; // +0x00 vtable

  // If m_pFramework (+0x50) is not null, release it
  if (*(void **)((char *)this + 0x50) != 0) {
    // Call a sequence of cleanup functions on the framework
    EARSFramework_Release();               // likely release reference
    EARSFramework_Shutdown();              // generic shutdown
    // Virtual call: framework->vtable[0x290](1) (probably a finalize method)
    (**(void (__thiscall **)(int, int))(*(int *)this + 0x290))(1);
    EARSFramework_PreDestroy();            // pre-destroy callback
    EARSFramework_ReleaseRef();            // release reference
    setFrameworkActive(0);                 // deactivate
    setFrameworkFlag(6, g_globalFlag);     // set a flag
    // Check bit 4 (0x10) of m_flags (+0xA4) and clear if set
    if (((*(uint *)((char *)this + 0xA4) >> 4) & 1) != 0) {
      clearResource(0, 0, g_resourceData);
      *(uint *)((char *)this + 0xA4) &= 0xFFFFFFEF; // clear bit 4
    }
    // Virtual call: framework->vtable[0x10](0x369AC561, &local)
    cVar1 = (**(code (__thiscall **)(int, uint, int *))(*(int *)this + 0x10))
                   (0x369AC561, &stack_local);
    if ((cVar1 != '\0') && (this != 0) &&
        ((*(uint *)((char *)this + 0xA4) >> 3) & 1) != 0) {
      releaseResource();                  // release some resource
      setFrameworkFlag(0x4B);             // another flag operation
      *(uint *)((char *)this + 0xA4) &= 0xFFFFFFF7; // clear bit 3
    }
  }

  // Free child objects at +0x9C and +0x70 if non-null
  if (*(void **)((char *)this + 0x9C) != 0) {
    operatorDelete();
  }
  if (*(void **)((char *)this + 0x70) != 0) {
    operatorDelete();
  }

  // Final cleanup (likely destructor of base class)
  baseCleanup();

  return;
}