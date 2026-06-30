// FUNC_NAME: SimManager::constructSimObject
void __thiscall SimManager::constructSimObject(void* this, int objId, int extraParam)
{
  // Get object base pointer from manager/registry using objId
  int objBase = FUN_00621530(objId); 
  // Retrieve the function table pointer at +0x08 from object base
  code* funcPtr = (code*)FUN_00621610(*(void**)(objBase + 8));
  // Call the object's constructor/initializer, returns the object pointer
  int newObj = (*funcPtr)(objId, extraParam);
  // Assign the current counter from manager (offset +0x08) into object's field +0x2c
  *(int*)(newObj + 0x2c) = *(int*)((char*)this + 8);
  // Increment the manager's counter
  *(int*)((char*)this + 8) += 1;
}