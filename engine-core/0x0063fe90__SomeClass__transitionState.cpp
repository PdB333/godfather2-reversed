// FUNC_NAME: SomeClass::transitionState
void SomeClass::transitionState(void)
{
  // Call to update substate or perform pre-transition logic
  this->updateSubstate(); // FUN_0063fad0

  // Transition state from 1 (e.g., 'idle') to 3 (e.g., 'active')
  if (this->state == 1) {
    this->state = 3;
  }

  // Call to process pending events or animations
  this->processEvents(); // FUN_00643310

  // Access the internal data block (at offset +0x1c from this->m_pData)
  int* pDataBlock = reinterpret_cast<int*>(this->m_pData); // unaff_EDI
  int iVar1 = pDataBlock[0x1c / 4]; // dereference +0x1c to get pointer

  // Copy value from +0x18 to +0x1c of that pointed object (e.g., update velocity from desired velocity)
  *(int*)(iVar1 + 0x1c) = *(int*)(iVar1 + 0x18);

  // Apply the update to the object
  this->applyDataUpdate(iVar1); // FUN_00642880
}