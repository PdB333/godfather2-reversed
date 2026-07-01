// FUNC_NAME: MissionData::loadFromXMLStream
void __thiscall MissionData::loadFromXMLStream(int thisPtr, undefined4 xmlStream)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int missionId;
  
  FUN_008bb320(xmlStream);
  missionId = 0;
  FUN_0043aff0(xmlStream,0x36cac259);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210(); // Advance to next XML element
    uVar2 = FUN_0043ab70(); // Get element type
    switch(uVar2) {
    case 0:
      missionId = FUN_0043b210(); // Read mission ID
      missionId = *(int *)(missionId + 8);
      break;
    case 1: // missionFlags
      iVar3 = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x290) = *(undefined4 *)(iVar3 + 8); // +0x290 missionFlags
      break;
    case 2: // missionName
      iVar3 = thisPtr + 0x2b0;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 3: // startTime
      iVar3 = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x2c0) = *(undefined4 *)(iVar3 + 8); // +0x2c0 startTime
      break;
    case 4: // endTime
      iVar3 = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x2c4) = *(undefined4 *)(iVar3 + 8); // +0x2c4 endTime
      break;
    case 5: // isActive
      iVar3 = FUN_0043b210();
      *(undefined1 *)(thisPtr + 0x2c8) = *(undefined1 *)(iVar3 + 8); // +0x2c8 isActive
      break;
    case 6: // rewardType
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(thisPtr + 0x294,uVar2); // +0x294 rewardType (string)
      break;
    case 7: // rewardValue
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0x29c,uVar2); // +0x29c rewardValue (int)
    }
    FUN_0043b1a0(); // Close current element
    cVar1 = FUN_0043b120();
  }
  if (DAT_0112afa0 != 0) {
    FUN_00408900(thisPtr + 0x3c,&DAT_0112afa0,0x8000); // Copy global data to +0x3c
  }
  if (missionId != 0) {
    *(uint *)(thisPtr + 0x290) = *(uint *)(thisPtr + 0x290) | 0x10; // Set flag bit 4
    *(int *)(thisPtr + 0x194) = missionId; // +0x194 missionId
  }
  if ((*(uint *)(thisPtr + 0x290) & 1) != 0) {
    *(uint *)(thisPtr + 0x290) = *(uint *)(thisPtr + 0x290) & 0xffffffbf; // Clear flag bit 6
  }
  if ((*(uint *)(thisPtr + 0x290) & 0x10) != 0) {
    *(uint *)(thisPtr + 0x290) = *(uint *)(thisPtr + 0x290) & 0xffffffbf; // Clear flag bit 6
  }
  return;
}