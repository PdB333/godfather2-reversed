// FUNC_NAME: TNLConnection::sendImpulsePacket
undefined4 * TNLConnection::sendImpulsePacket(undefined4 *this, int *param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 *param_8)

{
  int *piVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  
  // Check if the impulse data (4 ints) is non-zero
  if ((*param_2 != 0 || param_2[1] != 0) || (param_2[2] != 0 || param_2[3] != 0)) {
    // Get the connection's packet stream manager
    piVar1 = (int *)FUN_004e0f60();
    // If valid and the stream is active
    if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
      // If we have optional data to attach (e.g. position)
      if (param_8 != (undefined4 *)0x0) {
        local_30 = *param_8;
        local_2c = param_8[1];
        local_28 = param_8[2];
        local_24 = DAT_00e2b1a4; // +0x? unknown global
      }
      // Set event type (param_6, param_7) and sequence/version
      local_1c = param_6;
      local_18 = param_7;
      // Conditional: if param_8 non-null, use local_30 address; else 0
      local_14 = -(uint)(param_8 != (undefined4 *)0x0) & (uint)&local_30;
      local_20 = 2; // Event type: IMPULSE (or similar)
      // Send the impulse packet through the stream
      FUN_004df210(*piVar1, param_3, param_4, param_5);
      return this;
    }
  }
  // If invalid or no impulse data, return failure
  *this = 0;
  return this;
}