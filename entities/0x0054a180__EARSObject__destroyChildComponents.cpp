// FUNC_NAME: EARSObject::destroyChildComponents
void __fastcall EARSObject::destroyChildComponents(EARSObject* thisPtr)
{
  // Save this pointer for clarity
  EARSObject* self = thisPtr;
  void** vtablePtr = reinterpret_cast<void**>(self);

  // Step 1: Replace vtable with base class destructor vtable
  *vtablePtr = &PTR_FUN_00e39c30;  // Points to base destructor vtable

  // Step 2: Destroy component list (stored at offset +0x8)
  ComponentList* compList = reinterpret_cast<ComponentList*>(self->m_pComponentList);  // +0x8
  if (compList->m_count > 0)              // +0xC in the ComponentList struct
  {
    for (int i = 0; i < compList->m_count; i++)
    {
      // Each component provides a destructor function pointer
      compList->m_components[i]->destroy(0);  // Call component destructor with flag 0
    }
  }

  // Step 3: Handle reference‑counted destruction helper (at offset +0x4)
  DestructionHelper* helper = reinterpret_cast<DestructionHelper*>(self->m_pDestructionHelper);  // +0x4
  if (helper->m_hasReferences != 0)          // short at +0x4
  {
    helper->m_refCount--;                    // short at +0x6
    if (helper->m_refCount == 0)
    {
      helper->m_releaseFunction(1);          // fptr at +0x0, called with 1
    }
  }

  // Step 4: Finalise vtable (possibly post‑destruction or base class vtable)
  *vtablePtr = &PTR_LAB_00e39c34;  // Final vtable for base class
}