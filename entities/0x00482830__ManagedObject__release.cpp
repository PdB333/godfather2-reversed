// FUNC_NAME: ManagedObject::release
void __thiscall ManagedObject::release(void)
{
  int *piVar1;   // pointer to refCount
  undefined4 *puVar2; // pointer to global manager's backup
  int iVar4;      // global manager address
  int iVar5;      // pool index

  // Decrement reference count at this+0x04
  piVar1 = (int *)(this + 4);
  *piVar1 = *piVar1 - 1;
  iVar4 = g_objectManager; // global DAT_01223490
  if (*piVar1 == 0) {
    // Reference count reached zero – start cleanup
    puVar2 = (undefined4 *)(g_objectManager + 0x1c);  // manager +0x1c: backup of some pointer
    iVar5 = this->getPoolIndex();                      // FUN_004830a0 – returns index in manager's pool
    if (iVar5 >= 0) {
      this->removeFromManager();                       // FUN_00483050 – removes from manager lists
    }
    if (*(int *)(iVar4 + 0x20) == 0) {                 // manager +0x20: flag indicating backup is free
      iVar4 = *(int *)(g_objectManager + 0x20);        // (redundant, iVar4 already same)
      *(undefined4 *)(g_objectManager + 0x20) = 0;     // Clear the flag
      deallocate(*puVar2);                             // FUN_009c8f10 – deallocate the backup pointer value
      *puVar2 = 0;                                     // Clear the backup pointer
      *(undefined4 *)(g_objectManager + 0x24) = 0;     // manager +0x24: some count
    }
    deallocate(*(undefined4 *)(this + 0x20c));          // Free object's internal data at this+0x20c
    this->~ManagedObject();                            // FUN_009c8eb0 – actual destructor
  }
  return;
}