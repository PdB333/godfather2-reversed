// FUNC_NAME: SimManager::processPendingDeletes
void SimManager::processPendingDeletes(SimManager* thisPtr)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (thisPtr != 0) {
    iVar2 = FUN_004461c0(thisPtr,0); // SimManager::getPendingDeleteList
    if (iVar2 != 0) {
      FUN_0043aff0(iVar2,0x4ecfbe13); // SimSet::lockIterator
      cVar1 = FUN_0043b120(); // SimSet::isIteratorDone
      if (cVar1 == '\0') {
        while( true ) {
          FUN_0043b210(); // SimSet::incrementIterator
          iVar2 = FUN_0043ab70(); // SimSet::getCurrentObject
          if (iVar2 == 0) break;
          FUN_0043b1a0(); // SimSet::removeCurrentObject
          cVar1 = FUN_0043b120(); // SimSet::isIteratorDone
          if (cVar1 != '\0') {
            return;
          }
        }
        FUN_0043b210(); // SimSet::incrementIterator
        uVar3 = FUN_0043ab90(); // SimSet::getCurrentObject
        FUN_004d3d90(uVar3); // SimObject::deleteObject
      }
    }
  }
  return;
}