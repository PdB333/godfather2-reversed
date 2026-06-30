// FUNC_NAME: UpdateManager::process
void __fastcall UpdateManager::process(UpdateManager *this)
{
  int *currentObject; // piVar1
  bool isFinished; // cVar2
  int *objectPtrArray; // puVar3
  uint idx; // uVar4

  // Acquire global mutex
  acquireMutex(&g_updateMutex);

  currentObject = this->activeObject; // this+0x20
  // Start and process the current active object
  currentObject->vtable->start(currentObject, 0); // vtable+0x38
  currentObject->vtable->process(currentObject); // vtable+0x3c

  // Check if active object is null or is finished (vtable+0x8 returns non-zero)
  if ((this->activeObject == nullptr) || 
     (isFinished = this->activeObject->vtable->isFinished(this->activeObject), isFinished)) {
    // Move to next object in the list
    advanceNextObject(this);
  }

  // Process all objects in the object list
  idx = 0;
  if (this->objectCount != 0) { // this+0x1c
    objectPtrArray = this->objectList; // this+0x8
    do {
      objectPtrArray[idx]->vtable->update(objectPtrArray[idx]); // vtable+0xc
      idx++;
    } while (idx < this->objectCount);
  }

  // Release global mutex
  releaseMutex(&g_updateMutex);
  return;
}