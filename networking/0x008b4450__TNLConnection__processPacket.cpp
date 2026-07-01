// FUNC_NAME: TNLConnection::processPacket
void __thiscall TNLConnection::processPacket(int thisPtr, int *packetPtr)
{
  int *currentPacket;
  char isValid;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint *puVar6;
  int local_4;
  
  currentPacket = packetPtr;
  FUN_008ae520(packetPtr);
  local_4 = *(int *)(thisPtr + 0x60);
  if ((local_4 == 0) || (*(int *)(local_4 + 8) == 0)) {
    local_4 = 0;
  }
  do {
    if (local_4 == 0) {
      return;
    }
    iVar3 = (*(code *)PTR_FUN_00e35c28)();
    if ((*(byte *)(iVar3 + 0x30) & 1) != 0) {
      uVar4 = (*(code *)PTR_FUN_00e35c28)();
      uVar5 = (**(code **)(*currentPacket + 4))();
      uVar4 = FUN_004bb600(uVar4);
      isValid = FUN_00411fd0(uVar4,uVar5);
      if (isValid != '\0') {
        puVar6 = (uint *)(*(code *)PTR_FUN_00e35c28)();
        if (puVar6 == (uint *)0x0) {
          return;
        }
        if (*(int *)(thisPtr + 0x60) == 0) {
          return;
        }
        if (*(int *)(DAT_01223484 + 8) == 0) {
          return;
        }
        isValid = FUN_00481620();
        if (isValid == '\0') {
          return;
        }
        if (((*(byte *)(thisPtr + 0x188) & 1) != 0) && (*puVar6 < *(uint *)(thisPtr + 400))) {
          iVar3 = **(int **)(*(int *)(thisPtr + 0x18c) + *puVar6 * 4);
          uVar4 = (**(code **)(*packetPtr + 0xc))();
          (**(code **)(iVar3 + 0x10))(uVar4);
        }
        if ((*(uint *)(thisPtr + 0x188) >> 1 & 1) == 0) {
          return;
        }
        FUN_008b3d60(&packetPtr,puVar6 + 2);
        if (packetPtr == (int *)0x0) {
          return;
        }
        if (*(int *)(DAT_01223484 + 0x30) != 0) {
          (**(code **)(**(int **)(DAT_01223484 + 0x30) + 8))(packetPtr[1]);
        }
        FUN_008b4120(puVar6 + 2);
        return;
      }
    }
    (*_UNK_00e35c2c)();
  } while( true );
}