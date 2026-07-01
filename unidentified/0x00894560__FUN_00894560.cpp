// FUNC_NAME: UnknownClass::replicateProperty
void __thiscall replicateProperty(void* self, int param_2, undefined4 param_3, char param_4)
// Address: 0x00894560
// Replicates a property value to other players via reliable/unreliable packets.
// param_2: pointer to a property descriptor or network state structure
// param_3: context (e.g., connection or player index)
// param_4: flag indicating whether to force reliable delivery
{
  char isFirstAttempt;
  undefined4 reliableFlag;
  uint byteFlags;
  undefined4 forceReliableU4;
  
  forceReliableU4 = 0;
  if (param_4 != '\0') {
    forceReliableU4 = *(undefined4 *)(param_2 + 0xc); // +0x0C: reliability override (e.g., queue priority)
  }
  // _param_4 seems to be a local variable initialized to 0 (unused return buffer? Ghidra artifact)
  _param_4 = 0; // This appears to be a decompiler remnant for an out-of-scope stack variable
  
  // First attempt: send as unreliable (isReliable=0), with isSequenced=1, isGuaranteed=1, queue=0
  isFirstAttempt = FUN_00893e70(
      &_param_4,                     // output buffer (unused here)
      *(undefined4 *)(param_2 + 8),  // +0x08: property value or data pointer
      param_3,                       // context (player/connection)
      1,                             // isGuaranteed (might be reversed? 1 could be reliable)
      1,                             // isSequenced (deliver in order)
      0                              // queue index
  );
  
  if (isFirstAttempt != '\0') {
    // Extract flags from struct byte at +0x03 (bitfield: lower 2 bits)
    byteFlags = *(byte *)(param_2 + 3) & 3; // +0x03: flags (bits 0-1: delivery flags, 2=?, 3=?)
    
    // Get some property-specific flag/priority from 'self' object
    // This might be the connection's priority or a property index
    reliableFlag = FUN_00893410(self); // Likely returns a reliability count or priority level
    
    // Second attempt: send with more specific flags, possibly unreliable or updated
    FUN_00893e70(
        &_param_4,                     // output buffer
        *(undefined4 *)(param_2 + 4),  // +0x04: another property value (or delta/previous value)
        param_3,                       // context
        reliableFlag,                  // from self (e.g., priority or packet type)
        byteFlags,                     // delivery flags from struct
        forceReliableU4                // forced reliable override (from +0x0C)
    );
  }
  return;
}
// Note: FUN_00893e70 is likely the core network send function (sendPacket/queuePacket)
// FUN_00893410 appears to return a value from 'self' indicating state for this property (e.g., sequence number, priority)