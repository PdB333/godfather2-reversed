// FUNC_NAME: MissionManager::spawnOilCaptureables
void __thiscall MissionManager::spawnOilCaptureables(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = FUN_0043ab10(); // likely getCurrentMission()
  cVar1 = FUN_00904b60(uVar2); // likely isOilMission()
  if (cVar1 != '\0') {
    FUN_00408240(&DAT_0112ff38,"spawn_captureables_oil"); // likely printDebugMessage
  }
  FUN_00478040(param_2); // likely initCaptureableSpawner
  FUN_0043aff0(param_2,0xcbc8f142); // likely setSpawnerType
  cVar1 = FUN_0043b120(); // likely isSpawnComplete
  while (cVar1 == '\0') {
    FUN_0043b210(); // likely processSpawner
    iVar3 = FUN_0043ab70(); // likely getSpawnedEntity
    if (iVar3 == 0) {
      iVar3 = FUN_0043b210(); // likely getLastSpawnedEntity
      *(undefined4 *)(this + 0x60) = *(undefined4 *)(iVar3 + 8); // store entity pointer at +0x60
    }
    FUN_0043b1a0(); // likely advanceSpawner
    cVar1 = FUN_0043b120(); // likely isSpawnComplete
  }
  return;
}