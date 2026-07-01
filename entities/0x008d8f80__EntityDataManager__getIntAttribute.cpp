// FUNC_NAME: EntityDataManager::getIntAttribute
undefined4 EntityDataManager::getIntAttribute(undefined4 this, undefined4 attributeId, undefined4 *outValue)

{
  char success;
  undefined4 tempValue;
  
  tempValue = 0;
  success = FUN_004480d0(this,attributeId,&tempValue);
  if (success != '\0') {
    *outValue = tempValue;
    return 1;
  }
  *outValue = 0;
  return 0;
}