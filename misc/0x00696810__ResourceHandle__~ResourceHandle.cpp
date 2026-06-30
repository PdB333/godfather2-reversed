// FUNC_NAME: ResourceHandle::~ResourceHandle
void __fastcall ResourceHandle::~ResourceHandle(ResourceHandle* this)
{
  // Temporary buffer for internal helper (8 bytes)
  char local_8[8];
  
  // Internal helper call – arguments may be affected by fastcall register mapping.
  // The decompiled shows: (local_8, this, *this->m_pResource, this, this->m_pResource)
  // Note: param_1 appears twice; this might be a decompilation artifact.
  ResourceHandle::releaseHelper(local_8, this, *this->m_pResource, this, this->m_pResource);
  
  // Release the owned resource (pointer at +0x4)
  ResourceManager::releaseResource(this->m_pResource);
  
  // Clear handle fields
  this->m_pResource = nullptr;
  this->m_pNext     = nullptr; // +0x8
}