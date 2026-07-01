// FUNC_NAME: TaskManager::hasActiveTaskWithState
int __fastcall TaskManager::hasActiveTaskWithState(int thisPtr)
{
  uint index = 0;
  int result = 0;
  
  if (*(int *)(thisPtr + 8) != 0) {
    while (true) {
      int taskPtr = *(int *)(*(int *)(thisPtr + 4) + index * 4); // +0x4: task array pointer, +0x8: task count
      char isActive = FUN_006b4440(); // likely returns if task is running/active
      if (((isActive != 0) && 
           (isActive = FUN_00849ea0(*(int *)(taskPtr + 0x48)), isActive != 0)) && // check task state at +0x48
           (isActive = FUN_008c7790(*(int *)(taskPtr + 0x40)), isActive != 0)) break; // check other condition at +0x40
      index++;
      if (*(uint *)(thisPtr + 8) <= index) {
        return 0; // no matching active task found
      }
    }
    result = 1; // found an active task with matching state
  }
  return result;
}