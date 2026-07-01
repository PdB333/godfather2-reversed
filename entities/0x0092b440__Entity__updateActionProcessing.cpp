// FUNC_NAME: Entity::updateActionProcessing
void __fastcall Entity::updateActionProcessing(int this)
{
  int actionObject; // eax, returned from action resolution

  // Check if the current action pointer is null
  if (*(int *)(this + 0x50) == 0) {
    // No current action: query two potential new action sources
    FUN_0090a5a0();                  // potentially retrieve global action?
    actionObject = FUN_00791300();   // get new action from pool/generator
  } else {
    // Has an active action: update or retrieve its continuation
    actionObject = FUN_0079f9d0();   // e.g., getNextAction or resumeAction
  }

  if (actionObject != 0) {
    // Configure the action with the object and a parameter at offset 0x54
    FUN_009bcb30(actionObject);                        // attachAction(actionObject)
    FUN_009bbc50(*(undefined4 *)(this + 0x54));        // setActionParameter(parameter)

    // Execute the action via a global virtual call table (likely ActionManager singleton)
    // DAT_011304fc points to a global processing context; offset 0x28 = 10th vtable entry
    (**(code **)(*DAT_011304fc + 0x28))();             // executeCurrentAction()
  }
  // If actionObject is null, nothing to do
}