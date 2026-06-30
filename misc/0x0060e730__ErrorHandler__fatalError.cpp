// FUNC_NAME: ErrorHandler::fatalError
void ErrorHandler::fatalError(void)
{
  code *pcVar1;
  LPCSTR errorMessage;
  char *caption;
  UINT uType;
  
  uType = 0x40010; // MB_ICONERROR | MB_SYSTEMMODAL
  caption = "Error";
  errorMessage = (LPCSTR)ErrorHandler::getErrorMessage(); // FUN_0060e6c0
  MessageBoxA((HWND)0x0, errorMessage, caption, uType);
  if (DAT_01205750 != 0) { // global flag indicating if crash dump system is initialized
    CrashDump::writeDump(1); // FUN_00607e10
    CrashDump::cleanup(); // FUN_00607c30
  }
  __exit(0xffffffff);
  pcVar1 = (code *)swi(3); // software interrupt to trigger debugger
  (*pcVar1)();
  return;
}