// FUNC_NAME: Debug::handleDebugCommand
// Address: 0x008ccbc0
// This function is a handler for a specific debug command message (identified by param2 = 0xD5F82C42).
// It checks a flags bitmask at this+0x70 and if the bitwise AND of that mask with (currentFlags | param3) is non-zero,
// it triggers a debug log/display.

void __thiscall Debug::handleDebugCommand(int this, int commandId, uint additionalFlags)
{
  uint currentFlags;    // uVar1
  char buffer[12];      // local_c

  // Compare command ID to a specific hash constant (likely a debug activation hash)
  if (commandId == 0xD5F82C42) {
    // Get current system flags from some global/manager function
    currentFlags = getCurrentDebugFlags();  // FUN_0088cfd0
    // Check if the combined flags (currentFlags | additionalFlags) intersect with this object's flags
    if ((*(uint *)(this + 0x70) & (currentFlags | additionalFlags)) != 0) {
      // Emit debug output (1,0,0 might indicate a debug level or category)
      logDebugMessage(1, 0, 0);              // FUN_004a3d40
      // Retrieve a debug string by hash into buffer
      getDebugStringByHash(0x20e5862, buffer); // FUN_00417200
    }
  }
  // No else – ignore mismatched commands
}