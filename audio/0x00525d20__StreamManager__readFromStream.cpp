// FUNC_NAME: StreamManager::readFromStream
void StreamManager::readFromStream(int param_1, undefined4 *param_2)
{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined8 *puVar4;
  uint uVar5;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined1 local_4;
  
  // +0x18: current read position in stream buffer
  puVar4 = (undefined8 *)(*(int *)(param_1 + 0x18) + 3U & 0xfffffffc);
  *(undefined8 **)(param_1 + 0x18) = puVar4;
  // Read three consecutive 64-bit values from aligned buffer
  uVar1 = *puVar4;          // First 8 bytes
  uVar3 = *(undefined4 *)(puVar4 + 2);  // Bytes 16-19
  uVar2 = puVar4[1];        // Bytes 8-15
  *(int *)(param_1 + 0x18) = (int)puVar4 + 0x14;  // Advance by 20 bytes
  uVar5 = (int)puVar4 + 0x23U & 0xfffffff0;  // Align to 16-byte boundary for secondary read
  *(uint *)(param_1 + 0x18) = uVar5 + 0x40;   // Advance by 64 more bytes
  uStack_10 = (undefined4)((ulonglong)uVar1 >> 0x20);  // High 32 bits of first
  local_14 = (undefined4)uVar1;                       // Low 32 bits of first  
  local_c = (undefined4)uVar2;                         // Low 32 bits of second
  uStack_8 = (undefined4)((ulonglong)uVar2 >> 0x20);  // High 32 bits of second
  local_4 = (undefined1)uVar3;                         // Low byte of third value
  // Call the stream processor callback with the extracted values on stack
  (*(code *)*param_2)(local_14,uStack_10,local_c,uStack_8,local_4,uVar5);
  return;
}