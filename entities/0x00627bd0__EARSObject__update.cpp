// FUNC_NAME: EARSObject::update
void EARSObject::update(void)
{
  // Call base update or pre-update logic
  FUN_00627b40();
  
  // Check if some condition based on object state at +0x10
  // +0x10: pointer to some state/component
  // +0x20: some counter/limit
  // +0x24: another counter/value
  if (*(uint *)(*(int *)(in_EAX + 0x10) + 0x20) <= *(uint *)(*(int *)(in_EAX + 0x10) + 0x24)) {
    // Handle overflow/condition met
    FUN_00627360();
  }
  
  // Call another update function with stack parameter
  FUN_00636910(&stack0x00000008);
  
  // Check condition again after first update
  if (*(uint *)(*(int *)(in_EAX + 0x10) + 0x20) <= *(uint *)(*(int *)(in_EAX + 0x10) + 0x24)) {
    FUN_00627360();
  }
  
  // Call another update function
  FUN_006343b0();
  
  // Decrement some counter at +0x8 by 8
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + -8;
  
  // Final update call
  FUN_006338a0();
  
  return;
}