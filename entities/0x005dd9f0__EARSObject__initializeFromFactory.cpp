// FUNC_NAME: EARSObject::initializeFromFactory
// Address: 0x005dd9f0
// Role: Initializes this object by calling base class init, then creates a resource via global manager.
// Note: The decompiler shows an uninitialized local_18 check – likely an artifact; actual logic may differ.
undefined1 __thiscall EARSObject::initializeFromFactory(EARSObject *thisObject, undefined4 creationId)
{
  undefined1 status;
  // Base class initialization (likely constructor or reset)
  BaseClass::initialize(thisObject);  // FUN_004d3bc0
  // Use global manager (DAT_01223508) to create a resource based on creationId
  status = ResourceManager::createResource(gResourceManager, creationId);  // FUN_005dc3d0
  // The following block is likely a decompiler artifact; preserved for completeness.
  // local_18 (uninitialized) would represent a potential pointer; if non-zero, call its function.
  if (thisObject->m_potentialPointer != (void*)0x0) {
    (thisObject->m_potentialFunction)(thisObject->m_potentialPointer);
  }
  return status;
}