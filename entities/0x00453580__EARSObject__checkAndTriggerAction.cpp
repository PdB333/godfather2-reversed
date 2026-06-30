// FUNC_NAME: EARSObject::checkAndTriggerAction
void __thiscall EARSObject::checkAndTriggerAction(int param_2)
{
  char cVar1;
  int iVar2;
  void *pvVar3;
  
  // Get associated object from the pair (this, param_2)
  iVar2 = getEntityFromParams(this, param_2);
  if ((iVar2 != 0) && 
      (pvVar3 = *(void **)(iVar2 + 0xc), pvVar3 != 0) && 
      ((*(uint *)((int)pvVar3 + 0x30) >> 1 & 1) != 0) && 
      (*(int *)((int)pvVar3 + 0x2c) != 0)) {
    // Check if global state allows processing
    cVar1 = isStateActive();
    if (cVar1 != '\0') {
      // Execute the action if all conditions are met
      triggerAction(this, param_2);
    }
  }
  return;
}