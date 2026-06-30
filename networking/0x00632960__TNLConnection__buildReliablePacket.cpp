// FUNC_NAME: TNLConnection::buildReliablePacket
undefined4 TNLConnection::buildReliablePacket(void)
{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  // Check if buffer is full before writing
  FUN_00628260(&DAT_00e41e98);
  if (*(uint *)(*(int *)(in_EAX + 0x10) + 0x20) <= *(uint *)(*(int *)(in_EAX + 0x10) + 0x24)) {
    FUN_00627360();
  }
  
  // Write packet header: type 4 (reliable data chunk)
  puVar1 = *(undefined4 **)(in_EAX + 8);
  *puVar1 = 4;
  uVar2 = FUN_00638920();  // Get next sequence number
  uVar3 = DAT_00e2afac;    // Some global constant
  puVar1[1] = uVar2;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 8;
  
  // Write packet header: type 3 (acknowledgment)
  puVar1 = *(undefined4 **)(in_EAX + 8);
  *puVar1 = 3;
  puVar1[1] = uVar3;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 8;
  
  // Finalize packet construction
  iVar4 = *(int *)(in_EAX + 8);
  FUN_00633d60(iVar4 + -0x18,iVar4 + -0x10,iVar4 + -8);
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + -0x10;
  
  // Check buffer again
  if (*(uint *)(*(int *)(in_EAX + 0x10) + 0x20) <= *(uint *)(*(int *)(in_EAX + 0x10) + 0x24)) {
    FUN_00627360();
  }
  
  // Write another reliable data chunk
  puVar1 = *(undefined4 **)(in_EAX + 8);
  *puVar1 = 4;
  uVar3 = FUN_00638920();
  puVar1[1] = uVar3;
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 8;
  
  // Check buffer again
  if (*(uint *)(*(int *)(in_EAX + 0x10) + 0x20) <= *(uint *)(*(int *)(in_EAX + 0x10) + 0x24)) {
    FUN_00627360();
  }
  
  // Create a new packet object
  iVar4 = FUN_00638110(0);
  *(code **)(iVar4 + 0xc) = FUN_00631960;  // Set packet handler
  puVar1 = *(undefined4 **)(in_EAX + 8);
  puVar1[1] = iVar4;
  *puVar1 = 6;  // Packet type 6 (reliable packet)
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + 8;
  
  // Finalize packet construction
  FUN_00633d60(in_EAX + 0x40,*(int *)(in_EAX + 8) + -0x10,*(int *)(in_EAX + 8) + -8);
  *(int *)(in_EAX + 8) = *(int *)(in_EAX + 8) + -0x10;
  
  return 1;
}