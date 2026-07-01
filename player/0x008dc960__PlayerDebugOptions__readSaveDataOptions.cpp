// FUNC_NAME: PlayerDebugOptions::readSaveDataOptions
void __thiscall PlayerDebugOptions::readSaveDataOptions(int this, undefined4 streamPtr)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 *puVar4;
  
  // Begin reading save data entry
  FUN_0046f160(streamPtr);
  FUN_0043aff0(streamPtr,0xb16d66f3);  // Write tag ID
  cVar1 = FUN_0043b120();  // Check if end of stream
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();  // Read next entry type
    uVar2 = FUN_0043ab70();  // Get entry ID
    switch(uVar2) {
    case 0:  // EntranceCheckpointData
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x180) = *(undefined4 *)(iVar3 + 8);  // +0x180 entranceCheckpoint
      FUN_008ddab0(this);
      break;
    case 1:  // EntrancePosition
      FUN_0043b210();
      puVar4 = (undefined8 *)FUN_0043abe0();
      *(undefined8 *)(this + 0x1d0) = *puVar4;  // +0x1d0 entrancePosition (x,y)
      *(undefined4 *)(this + 0x1d8) = *(undefined4 *)(puVar4 + 1);  // +0x1d8 entranceZ
    case 8:  // Some extra data
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1b4,uVar2);
      break;
    case 2:  // boolOption1
      iVar3 = FUN_0043b210();
      *(bool *)(this + 0x1cc) = *(int *)(iVar3 + 8) != 0;  // +0x1cc someBool1
      break;
    case 3:  // integerOption2
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x19c,uVar2);
      break;
    case 4:  // boolOption3
      iVar3 = FUN_0043b210();
      *(bool *)(this + 0x1cd) = *(int *)(iVar3 + 8) != 0;  // +0x1cd someBool2
      break;
    case 5:  // integerOption4
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x188) = *(undefined4 *)(iVar3 + 8);  // +0x188 someInteger
      break;
    case 6:  // integerOption5
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x1a4,uVar2);
      break;
    case 7:  // triggerActorId
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x1c8) = *(undefined4 *)(iVar3 + 8);  // +0x1c8 triggerActorID
    }
    FUN_0043b1a0();  // Advance stream
    cVar1 = FUN_0043b120();  // Check if end of stream
  } while( true );
}