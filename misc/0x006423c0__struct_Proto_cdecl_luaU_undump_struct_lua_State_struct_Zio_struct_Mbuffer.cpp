// Xbox PDB: struct Proto * __cdecl luaU_undump(struct lua_State *,struct Zio *,struct Mbuffer *)
// FUNC_NAME: CommandBuffer::processCommand
void __thiscall CommandBuffer::processCommand(void *this, int stringBuffer, int arg3, int arg4)
{
  char *bufferPtr = *(char **)(stringBuffer + 0x10); // +0x10: pointer to command string data
  char firstChar = *bufferPtr;

  // Handle special command prefixes:
  // '@' = network command, '=' = variable assignment
  if (firstChar == '@' || firstChar == '=') {
    bufferPtr = bufferPtr + 1; // skip the prefix character
  }
  // Escaped commands (0x1B = ESC) indicate binary data
  else if (firstChar == '\x1b') {
    bufferPtr = (char *)"binary string"; // placeholder, likely replaced with actual binary data
  }

  // Prepare arguments for downstream functions
  int localArgs[2];
  localArgs[0] = arg3;
  localArgs[1] = arg4;
  int localBufferPtr = (int)stringBuffer;

  // Execute command processing
  executeCommand();                           // FUN_006421b0 - likely performs the command action
  parseCommandArgs(localArgs, 0);             // FUN_00642070 - parses additional arguments
}