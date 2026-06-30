// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(EARSObject* this)
{
  // Set vtable pointers for multiple inheritance (offsets 0x00, 0x3C, 0x48, 0x50)
  this->vtable = &PTR_FUN_00d5f4d4;
  *(void**)((char*)this + 0x3C) = &PTR_LAB_00d5f4c4;
  *(void**)((char*)this + 0x48) = &PTR_LAB_00d5f4c0;
  *(void**)((char*)this + 0x50) = &PTR_LAB_00d5f4bc;

  // Clean up previously allocated resources (if any)
  if (this->m_pResource1 != nullptr) { // offset +0x98
    releaseResource(&this->m_pResource1);
  }
  if (this->m_pResource2 != nullptr) { // offset +0x90
    releaseResource(&this->m_pResource2);
  }

  // Global initialization routine
  initializeSubsystem();
}