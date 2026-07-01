// FUNC_NAME: SomeClass::getNextItemInList
int __fastcall getNextItemInList(int *param_1)
{
  // Check if the list head pointer is null
  if (*param_1 == 0) {
    FUN_00b97aea(); // likely assertion or error handler
  }
  // Check if the current node's next pointer matches the list head's next pointer (end of list)
  if (param_1[1] == *(int *)(*param_1 + 0x18)) {
    FUN_00b97aea(); // likely assertion or error handler
  }
  // Return pointer to the next item (offset +8 from the current node)
  return param_1[1] + 8;
}