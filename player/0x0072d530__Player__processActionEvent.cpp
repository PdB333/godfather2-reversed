// FUNC_NAME: Player::processActionEvent
void __thiscall Player::processActionEvent(int *thisPtr, int *eventData)
{
  // eventData+4 holds a pointer to an object (e.g., a trigger or interactable)
  int *targetObject = *(int **)(eventData + 4);
  if (targetObject != (int *)0x0)
  {
    // Compare object's type/hash at +0x38 with player's current action state at +0x7BA (0x1EE8)
    int playerActionId = thisPtr[0x7ba]; // offset 0x1EE8
    if (*(int *)(targetObject + 0xe) == playerActionId) // targetObject+0x38 (0xe*4) = offset 0x38
    {
      // Log or update debug system
      FUN_004086d0(&DAT_0112a5e0); // possibly Debug::print
      // Clear a flag on the event data
      FUN_0046ffe0(*(int *)(eventData + 8), 0); // likely TaskManager::removeTask or similar
      // Dispatch a virtual event (function index 0x288/4 = 0xA2) with command 4 and two arguments
      (*(code **)(*thisPtr + 0x288))(4, *(int *)(eventData + 0xc), *(int *)(eventData + 0x10));
      // Trigger follow-up behavior
      FUN_0072d290(); // probably continueQueue or nextAction
    }
  }
  return;
}