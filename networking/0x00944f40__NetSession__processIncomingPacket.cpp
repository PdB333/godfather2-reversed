// FUNC_NAME: NetSession::processIncomingPacket
undefined4 __thiscall NetSession::processIncomingPacket(int thisPtr, undefined4 *packetData, int packetSize)
{
  int *nodePtr;
  undefined4 *packetIter;
  undefined4 result;
  undefined4 uVar3;
  int iVar5;
  int local_6c;
  undefined4 local_68;
  int *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  if (packetSize == 0) {
    // Initialize default mask values from global data
    local_50 = _DAT_00d5780c;
    uStack_4c = 0;
    uStack_48 = 0;
    uStack_44 = 0;
    local_40 = 0;
    uStack_3c = _DAT_00d5780c;
    uStack_38 = 0;
    uStack_34 = 0;
    local_30 = 0;
    uStack_2c = 0;
    uStack_28 = _DAT_00d5780c;
    uStack_24 = 0;
    local_20 = 0;
    uStack_1c = 0;
    uStack_18 = 0;
    uStack_14 = _DAT_00d5780c;
  }
  else {
    // Decode packet header from raw data
    FUN_0044b4e0(&local_50, packetSize);
  }
  
  // Copy packet data into local buffer
  local_60 = *packetData;
  local_5c = packetData[1];
  local_58 = packetData[2];
  local_54 = packetData[3];
  local_68 = 0;
  
  // Process the packet through the network layer
  FUN_004df270(&local_6c, &local_60, &local_50, 0x1ff, 0, &local_68);
  
  if (local_6c == 0) {
    return 0xffffffff; // Invalid packet
  }
  
  // Get the session manager and allocate a node
  local_68 = FUN_00943c50();
  local_64 = (int *)FUN_009442b0(&local_68);
  
  // Check if we can accept new packets (not in shutdown or paused state)
  if ((*(int *)(thisPtr + 0xec) == 0) &&
     ((*(int *)(thisPtr + 0xe8) == 0 || ((*(byte *)(thisPtr + 0xdc) & 1) == 0)))) {
    FUN_004de190(); // Signal packet arrival
  }
  
  result = local_68;
  packetIter = *(undefined4 **)(thisPtr + 0xec);
  
  if (packetIter != (undefined4 *)0x0) {
    uVar3 = *packetIter;
    *(int *)(thisPtr + 200) = *(int *)(thisPtr + 200) + 1; // Increment packet counter
    *(int *)(thisPtr + 0xc4) = *(int *)(thisPtr + 0xc4) + -1; // Decrement buffer count
    *(undefined4 *)(thisPtr + 0xec) = uVar3;
    
    if (packetIter != (undefined4 *)0x0) {
      iVar5 = FUN_00944c80(local_68, **(undefined4 **)(thisPtr + 0x100));
      goto LAB_00945059;
    }
  }
  
  iVar5 = 0;
  
LAB_00945059:
  *local_64 = iVar5; // Store the processed packet node
  
  // Link the new node into the packet list
  nodePtr = (int *)(iVar5 + 8);
  if (*(int *)(iVar5 + 8) != 0) {
    *(undefined4 *)(*(int *)(iVar5 + 8) + 8) = 0;
    *nodePtr = 0;
  }
  
  *nodePtr = local_6c;
  if (local_6c != 0) {
    *(int **)(local_6c + 8) = nodePtr;
    local_6c = 0;
  }
  
  // Clean up the processed packet
  FUN_004df830(*(undefined4 *)(iVar5 + 0xc));
  
  if (local_6c != 0) {
    *(undefined4 *)(local_6c + 8) = 0;
  }
  
  return result;
}