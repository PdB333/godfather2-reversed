// FUNC_NAME: NetSession::sendDebugMessage
bool __thiscall NetSession::sendDebugMessage(int *this, undefined4 *messageData)
{
  int iVar1;
  undefined4 localId;
  undefined4 data0;
  undefined4 data1;
  undefined4 data2;
  undefined1 packetHeader[8];
  undefined4 extraParam;
  undefined4 debugFlags[4];
  undefined1 unknownSmall[4];
  undefined1 tempBuffer[80];
  undefined1 outputBuffer[96];
  int result;
  
  // Virtual call at vtable+0x3c: likely returns a session or message ID
  (**(code **)(*this + 0x3c))(&localId, unknownSmall);
  
  data0 = *messageData;
  data1 = messageData[1];
  data2 = messageData[2];
  
  // Global constant (likely debug/network flag)
  uStack_130 = DAT_00d5780c; // +0x??
  uStack_120 = localId;
  uStack_11c = DAT_00d5780c;
  
  iVar1 = FUN_007ff880(); // Returns some context flag
  if (iVar1 != 0) {
    debugFlags[0] = FUN_0043b490(); // Returns an extra parameter (e.g., player index)
  }
  
  // Build and send the message packet
  // Arguments: packetHeader, message data source, message type (0x40122), subsystem id (0x01000001), flags, boolean flag
  FUN_005425d0(packetHeader, &data0, 0x40122, &DAT_01000001, debugFlags, iVar1 != 0);
  
  // Serialize into temp buffer
  FUN_0054b2c0(tempBuffer, 1);
  
  // Copy to output buffer
  FUN_009e5ed0(tempBuffer, outputBuffer);
  
  // Return true if result is zero (success)
  return result == 0;
}