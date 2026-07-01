// FUNC_NAME: GodfatherGameManager::spawnPlayerOrSomething
void __thiscall GodfatherGameManager::spawnPlayerOrSomething(int *this, char param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 auStack_24 [4];
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  cVar1 = FUN_00481640(); // likely isGameActive() or similar
  if (((cVar1 != '\0') && (this[0x212] != 0)) && (this[0x7be] != -1)) {
    cVar1 = FUN_0089c630(); // likely isCutscenePlaying()
    if (cVar1 == '\0') {
      cVar1 = FUN_00414d50(); // likely isPlayerAlive()
      if (cVar1 == '\0') {
        uStack_14 = _DAT_00d5780c; // some global color/vector constant
        if (param_2 == '\0') {
          if (this[0x7bd] == 1) {
            local_20 = 0;
            uStack_1c = 0;
            uStack_18 = _DAT_00d5780c;
          }
          else {
            local_20 = _DAT_00d5780c;
            uStack_18 = 0;
            uStack_1c = 0;
          }
        }
        else {
          local_20 = _DAT_00d5780c;
          uStack_1c = _DAT_00d5780c;
          uStack_18 = 0;
        }
        if (this[0x7c3] != 0) {
          FUN_004df600(); // likely resetCamera()
        }
        cVar1 = FUN_004df190(); // likely isSpawnAllowed()
        if (cVar1 != '\0') {
          puVar2 = (undefined4 *)FUN_004eb390(0x30,0x10); // operator new(0x30, 0x10)
          uVar4 = _DAT_00d5780c;
          puVar5 = (undefined4 *)0x0;
          if (puVar2 != (undefined4 *)0x0) {
            puVar2[1] = 0;
            puVar2[8] = 0;
            *puVar2 = &PTR_FUN_00e372b4; // vtable for some object
            puVar2[4] = uVar4;
            puVar2[5] = uVar4;
            puVar2[6] = uVar4;
            puVar2[7] = uVar4;
            puVar5 = puVar2;
          }
          puVar3 = (undefined1 *)this[0x211]; // +0x844 - some string/name
          if (puVar3 == (undefined1 *)0x0) {
            puVar3 = &DAT_0120546e; // default string
          }
          FUN_004ec1c0(puVar3); // likely setName()
          puVar5[4] = local_20;
          puVar5[5] = uStack_1c;
          puVar5[6] = uStack_18;
          puVar5[7] = uStack_14;
          uVar4 = (**(code **)(*this + 0x58))(0,this,0,0); // virtual call at +0x58
          uVar4 = FUN_00471610(uVar4); // likely getTransform()
          uVar4 = FUN_004df330(auStack_24,this + 0x7bf,uVar4); // likely setSpawnPosition()
          FUN_00414db0(uVar4); // likely spawnPlayer()
          FUN_00414df0(); // likely postSpawn()
          FUN_004df830(puVar5); // likely cleanup or delete
        }
      }
    }
  }
  return;
}