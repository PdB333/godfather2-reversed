// FUNC_NAME: TNLConnection::processGamePacket
void __thiscall TNLConnection::processGamePacket(uint param_1, int param_2)
{
  undefined4 *puVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  int this; // unaff_ESI, this pointer
  int *piVar5;
  
  uVar3 = in_EAX + param_1;
  if (*(uint *)(param_2 + 0x44) < in_EAX + param_1) {
    uVar3 = *(uint *)(param_2 + 0x44);
  }
  if (param_1 < uVar3) {
    iVar4 = uVar3 - param_1;
    piVar5 = (int *)(param_2 + 4 + param_1 * 8);
    do {
      // Process each event in the packet (events are 8 bytes each)
      switch(piVar5[1]) { // eventType at offset +4
      case 1: // Event type: GhostUpdate
        iVar2 = *piVar5; // ghostId
        puVar1 = *(undefined4 **)(this + 8); // eventBuffer write pointer
        *puVar1 = 2; // GhostUpdateEvent type
        puVar1[1] = iVar2;
        *(int *)(this + 8) = *(int *)(this + 8) + 8;
        break;
      case 2: // Event type: GhostDelete
        puVar1 = *(undefined4 **)(this + 8);
        iVar2 = *piVar5; // ghostId
        *puVar1 = 3; // GhostDeleteEvent type
        puVar1[1] = iVar2;
        *(int *)(this + 8) = *(int *)(this + 8) + 8;
        break;
      case 3: // Event type: GhostValidation
        puVar1 = *(undefined4 **)(this + 8);
        iVar2 = *piVar5; // ghostId
        *puVar1 = 1; // GhostValidationEvent type
        puVar1[1] = (uint)(iVar2 != 0); // bool valid
        *(int *)(this + 8) = *(int *)(this + 8) + 8;
        break;
      case 4: // Unknown event type
        FUN_00625ca0(); // error handler
      }
      piVar5 = piVar5 + 2;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return;
}