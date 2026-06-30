// FUNC_NAME: LuaErrorHandler::reportParseError
void __thiscall reportParseError(int thisPtr, undefined4 param2)
{
  undefined1 buffer [80]; // stack buffer for formatted error message
  
  if (*(int *)(thisPtr + 4) != 0) { // +0x4 = pointer to error output callback object
    // Format error message: "E01: Parse error near character %d"
    FUN_006a3680(buffer, L"E01: Parse error near character %d", param2);
    // Call the error output callback's method (vtable+4 = output method)
    (**(code **)(**(int **)(thisPtr + 4) + 4))(buffer);
  }
  return;
}