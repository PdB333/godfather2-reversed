// FUNC_NAME: NPCCrewComponent::NPCCrewComponent
undefined4 * __thiscall NPCCrewComponent::NPCCrewComponent(undefined4 *this, undefined4 owner, undefined4 flags)
{
  char cVar1;
  int *piVar2;
  
  // Call base class constructor (Component::Component)
  Component::Component(owner, flags);
  
  // Set vtable pointer for NPCCrewComponent
  *this = &NPCCrewComponent_vtable;  // 0x00d72ba0
  
  // Initialize flags/state bytes at offsets 0x54 and 0x55
  *(byte *)((int)this + 0x54) = 0;
  *(byte *)((int)this + 0x55) = 0;
  
  // Get pointer to embedded sub-object at offset 0x48 (m_pSubObject)
  // If null, owner pointer is null; otherwise compute owner from sub-object offset
  if (this[0x12] == 0) {
    piVar2 = (int *)0x0;
  }
  else {
    // Sub-object is embedded in owner at offset 0x48, so owner = subObject - 0x48
    piVar2 = (int *)(this[0x12] + -0x48);
  }
  // Store owner pointer at offset 0x50 (m_pOwner)
  this[0x14] = piVar2;
  
  // Call virtual function on owner at vtable offset 0x290 (e.g., registerComponent)
  (**(code **)(*piVar2 + 0x290))(0, 4);
  
  // Debug/logging if enabled
  cVar1 = isDebugMode();  // FUN_00481640
  if (cVar1 != '\0') {
    debugLog(0);          // FUN_00472130
    debugLogMore(0);      // FUN_004721c0
  }
  
  return this;
}