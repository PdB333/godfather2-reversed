// FUNC_NAME: Player::spawnOrRespawn
void __fastcall Player::spawnOrRespawn(int this)
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  piVar1 = (int *)FUN_00800b10(); // GetPlayerController? Returns some controller/input object
  if (piVar1 != (int *)0x0) {
    piVar2 = (int *)FUN_007079a0(); // GetGameManager? Returns game manager singleton
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 0x250))(piVar1); // GameManager::setPlayerController? (vtable+0x250)
      (**(code **)(*piVar1 + 0x160))(0); // Controller::setInputEnabled(false) (vtable+0x160)
      (**(code **)(*piVar1 + 0x7c))(); // Controller::reset? (vtable+0x7c)
    }
    FUN_004088c0(piVar1 + 0xf); // Some cleanup on controller +0x3C (0xF*4)
    FUN_00894c90(0xe3264e1a); // Audio::stopSound? With hash 0xe3264e1a
    iVar3 = *(int *)(this + 0x74); // Player +0x74 = mPlayerData? or mCharacterData
    if (iVar3 != 0) {
      uVar4 = 4;
      FUN_008e9cb0(0xa5975eb2,iVar3,4); // Some entity/object function with hash
      FUN_008ecfb0(iVar3,uVar4); // Set state/flag to 4 (e.g., dead->alive)
    }
    if (*(int *)(this + 0x74) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(this + 0x74) + 0x3c; // +0x3C = position offset in character data
    }
    FUN_00440590(&DAT_0112e020,iVar3,DAT_00e446f4,0,4); // Set spawn point? DAT_0112e020 is global spawn manager
    uVar4 = FUN_0090e2d0(0,20000,2,0,0,0); // Create timer? (delay, duration, type, ...)
    *(undefined4 *)(*(int *)(this + 0x74) + 0xe4c) = uVar4; // Store timer handle at character data +0xE4C (respawn timer)
  }
  return;
}