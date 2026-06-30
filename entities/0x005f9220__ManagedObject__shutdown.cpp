// FUNC_NAME: ManagedObject::shutdown
void ManagedObject::shutdown()
{
  // Pre-cleanup global decrement or lock release
  g_refCountDec();
  
  // Delete child object via virtual deallocator (size 0xc = 12 bytes)
  // The deallocator is stored at vtable offset +4
  (this->vtable->deallocate)(m_pChild, 0xc);
  m_pChild = nullptr;
  
  // If sub-object exists, delete it via the sub-manager's virtual deallocator
  if (m_pSubObject != nullptr) {
    (m_pSubManager->vtable->deallocate)(m_pSubObject, 0);
    m_pSubObject = nullptr;
  }
  
  // Call cleanup/release on the sub-manager via virtual function at offset +0xc
  (m_pSubManager->vtable->release)();
  
  // Post-cleanup global increment or lock release
  g_refCountDec();
}