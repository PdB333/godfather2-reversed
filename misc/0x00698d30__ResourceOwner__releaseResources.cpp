// FUNC_NAME: ResourceOwner::releaseResources
void __thiscall ResourceOwner::releaseResources(void)
{
  // +0x10: m_pObject1 - pointer to first owned object
  // +0x1c: m_pDeleter1 - function pointer to release m_pObject1
  if (this->m_pObject1 != 0) {
    this->m_pDeleter1(this->m_pObject1);
    // Call the custom deleter for object1
  }
  // +0x20: m_pObject2 - pointer to second owned object
  // +0x2c: m_pDeleter2 - function pointer to release m_pObject2
  if (this->m_pObject2 != 0) {
    this->m_pDeleter2(this->m_pObject2);
    // Call the custom deleter for object2
  }
  return;
}