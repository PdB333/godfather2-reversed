// FUNC_NAME: EntityComponent::checkAndExecutePendingOperation

void __thiscall EntityComponent::checkAndExecutePendingOperation(EntityComponent* thisObj)
{
  // Check if the pending flag (bit 0) is not already set
  if ((thisObj->flags & 1) == 0) {
    // Mark as pending and clear the executed flag (bit 1)
    thisObj->flags |= 1;
    thisObj->flags &= ~2;
  }

  // Query some global condition (e.g., game state, readiness)
  char conditionMet = checkGlobalCondition();  // FUN_00725ef0

  if (conditionMet != '\0') {
    // Set the executed flag
    thisObj->flags |= 2;

    // Call a virtual function on a sub-object at offset +0x128.
    // The sub-object's vtable has the target function at index 2 (offset 8 in vtable).
    // Passing this as the 'this' pointer to that function.
    void* subObject = *(void**)thisObj->subObjectPtr;  // deref to vtable
    void (*virtualFunc)(EntityComponent*) = *(void(**)(EntityComponent*))((char*)subObject + 8);
    virtualFunc(thisObj);
  }
}