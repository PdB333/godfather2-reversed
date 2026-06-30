// FUNC_NAME: StaticInit::initializeSubsystems
void StaticInit::initializeSubsystems(void)

{
  if ((_DAT_01129a3c & 1) == 0) {
    _DAT_01129a3c = _DAT_01129a3c | 1;
    FUN_00482440(); // Likely initializes some subsystem (e.g., memory manager or logging)
    _atexit((_func_4879 *)&LAB_00d51490); // Register cleanup function for subsystem 1
  }
  if ((_DAT_01129a3c & 2) == 0) {
    _DAT_01129a3c = _DAT_01129a3c | 2;
    FUN_005be4f0(); // Likely initializes another subsystem (e.g., file system or audio)
    _atexit((_func_4879 *)&LAB_00d51480); // Register cleanup function for subsystem 2
  }
  return;
}