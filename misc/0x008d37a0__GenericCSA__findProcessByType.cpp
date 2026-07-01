// FUNC_NAME: GenericCSA::findProcessByType

int __thiscall GenericCSA::findProcessByType(int this, undefined4 processType)
{
  int iVar1;
  
  iVar1 = FUN_008d3190(&processType); // findProcessSlotByType: searches +0x18 process list for type
  if ((-1 < iVar1) && (iVar1 = *(int *)(this + 0x18) + 4 + iVar1 * 0x18, iVar1 != 0)) {
    return iVar1 + 4; // return pointer to the process entry (+4 skips the type enum)
  }
  iVar1 = FUN_008d35f0(&processType); // insertNewProcessOfType: allocates new process slot
  FUN_008d5df0(); // processCollectionManager::registerProcess? (likely adds to internal list)
  return iVar1 + 4; // return pointer to the newly created process
}