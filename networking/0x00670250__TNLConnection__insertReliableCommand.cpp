// FUNC_NAME: TNLConnection::insertReliableCommand
uint __thiscall TNLConnection::insertReliableCommand(int thisPtr, int *commandList, int param_3)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 local_2c;
  int local_28;
  uint local_24;
  int *local_20;
  uint local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  // Current command index in the list (stored at param_2+5 for some size/offset)
  local_24 = (uint)*(ushort *)(commandList + 5);
  commandList[5] = commandList[5] + 1;
  
  // Calculate pointer to the command slot (each slot is 5 ints + 6 base offset)
  piVar1 = commandList + local_24 * 5 + 6;
  local_2c = 0;
  
  // Store the connection pointer at offset +8 in the slot
  piVar1[2] = thisPtr;
  local_20 = piVar1;
  local_1c = local_24;
  
  // Get a sequence number from the pool
  iVar2 = FUN_00672e60(&local_2c);
  local_28 = piVar1[2];
  
  // Store sequence number at offset +4
  piVar1[1] = iVar2;
  local_2c = 0;
  
  // Allocate and initialize a packet header structure
  piVar3 = (int *)FUN_00673070();
  *piVar3 = local_28;          // +0x00: connection pointer
  piVar3[1] = 0;                // +0x04: flags? set to 0
  piVar3[3] = 0;                // +0x0C: some flag
  piVar3[6] = 0;                // +0x18: something
  piVar3[7] = 0;                // +0x1C: something
  *(undefined1 *)(piVar3 + 8) = 0; // +0x20: first byte of something
  piVar3[5] = iVar2;            // +0x14: sequence number
  piVar3[2] = param_3;          // +0x08: command type? (third parameter)
  *(undefined1 *)(piVar3 + 4) = 3; // +0x10: command state = 3? (not sent yet?)
  piVar1[3] = (int)piVar3;      // Store pointer in slot at offset +0x0C
  
  // Initialize the command
  FUN_00671930(piVar3, &local_2c);
  
  // Some constants for later processing (likely max sizes)
  local_18 = 0xc0000;  // 786432
  local_c = 0xc0000;   // 786432
  local_14 = 0;
  local_10 = 0;
  
  // Get command ID from the system
  uVar4 = FUN_00671870(local_24, &local_2c);
  local_20[4] = uVar4 & 0xffff;  // Store command ID (low 16 bits)
  
  // Update the connection state (first int of connection list)
  iVar2 = *commandList;
  *(undefined4 *)(iVar2 + 0x2c) = 0;  // +0x2C reset
  *(undefined4 *)(iVar2 + 0x30) = 0;  // +0x30 reset
  *(undefined1 *)(iVar2 + 0x1c) = 0;  // +0x1C reset
  commandList[3] = 1;  // Mark that commands have been inserted
  
  return local_1c;  // Return the command index
}