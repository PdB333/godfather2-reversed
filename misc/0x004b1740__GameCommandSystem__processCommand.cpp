// FUNC_NAME: GameCommandSystem::processCommand
int __cdecl GameCommandSystem::processCommand(int param_1, const char *commandName, int arg0, int arg1)
{
  // Check if command exists in global table
  int commandId = GetCommandId(commandName, 0, 0);
  if (commandId == 0) {
    return 0;
  }

  // Initialize a local command parameters structure (size ~0x3C)
  // Offsets are relative to ebp-0x70 (local_70)
  int localStruct[0x3C / 4] = {0}; // approximate
  // Fill structure with constants (likely from global defaults)
  localStruct[0x00] = 1;              // +0x70: some flag
  localStruct[0x01] = 0;              // +0x6c
  localStruct[0x02] = 0;              // +0x68
  localStruct[0x03] = 0;              // +0x64
  localStruct[0x04] = 1;              // +0x60: another flag
  localStruct[0x05] = 0;              // +0x5c
  localStruct[0x06] = 0;              // +0x58
  localStruct[0x07] = 0;              // +0x54
  localStruct[0x08] = 0;              // +0x50
  localStruct[0x09] = 0;              // +0x4f (byte)
  localStruct[0x0A] = DAT_00e2b1a4;   // +0x4c
  localStruct[0x0B] = DAT_00e2b04c;   // +0x48
  localStruct[0x0C] = DAT_00e2b050;   // +0x44
  localStruct[0x0D] = 0;              // +0x40
  localStruct[0x0E] = 0;              // +0x3c
  localStruct[0x0F] = 0;              // +0x38
  localStruct[0x10] = 0;              // +0x34

  // Get global context (e.g., task manager)
  void *globalContext = GetGlobalContext();
  RegisterCommand(globalContext, commandId);

  // Allocate a command buffer (string storage)
  char *commandData = NULL;
  int commandDataSize = 0;
  int flag2 = 0;
  typedef void (__cdecl *DestructorFn)(char *);
  DestructorFn destructor = NULL;
  AllocateCommandBuffer(&commandData, commandId, 0);

  // Use default placeholder if no buffer allocated
  const char *commandString = (commandData != NULL) ? commandData : "DEFAULT_STRING_ADDR";

  // Check global flag at g_GameManager+0x1744 (enable processing?)
  if (*(char *)((int)g_GameManager + 0x1744) != '\0') {
    // Dispatch command with parameters (arg0 stored in array)
    int args[2] = { arg0, arg1 };
    if (DispatchToCommandHandler(g_GameManager, param_1, commandString, args, -1)) {
      if (commandData != NULL) {
        destructor(commandData);
      }
      return 1;
    }
  }

  if (commandData != NULL) {
    destructor(commandData);
  }
  return 0;
}