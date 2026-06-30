// FUNC_NAME: Resource::~Resource()
void __thiscall Resource::~Resource(Resource *this)
{
  // Check if internal pointer at +0x04 is not null, then release it
  if (this->m_pInternal != nullptr) {
    releaseObject(this->m_pInternal); // FUN_004daf90
  }
  // Set vtable pointer to base sentinel vtable (00e2f0c0)
  *(void **)this = &g_ResourceBaseVTable; // PTR_LAB_00e2f0c0
}