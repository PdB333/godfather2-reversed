// FUNC_NAME: EARSObject::~EARSObject

void __thiscall EARSObject::~EARSObject(EARSObject *this)
{
  // Call global pre-destructor cleanup (e.g., unregister from manager)
  EARSObject::staticPreCleanup(); // FUN_005f9f80

  // Release child object at offset +0x18 (this->m_pChildB) with a flag (0xc)
  ((void (__thiscall *)(EARSObject *, int))this->vtable[1])(this->m_pChildB, 0xc);
  this->m_pChildB = 0;

  // If there is a second child at +0x14 (this->m_pChildA), release it with flag 0
  if (this->m_pChildA != 0) {
    ((void (__thiscall *)(EARSObject *, int))this->m_pChildA->vtable[1])(this->m_pChildA, 0);
    this->m_pChildA = 0;
  }

  // Call finalize on the parent/owner object at +0x10 (this->m_pOwner)
  // The call uses vtable[3] (offset 12) – likely a "release" or "detach" method
  ((void (__thiscall *)(EARSObject *))this->m_pOwner->vtable[3])(this->m_pOwner);

  // Call global post-destructor cleanup
  EARSObject::staticPostCleanup(); // FUN_005f9520
}