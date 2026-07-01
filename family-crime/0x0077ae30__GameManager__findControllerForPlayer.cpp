// FUNC_NAME: GameManager::findControllerForPlayer
uint GameManager::findControllerForPlayer(int param_1) // +0x0 = this for __thiscall
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_20 [3]; // scoped object buffer
  code *local_14;
  int local_10 [3]; // scoped object buffer
  code *local_4;
  
  uVar3 = 0xc; // default: no controller found (0x3F? but loop goes to 0xC)
  FUN_004d53a0(0x20); // alloc temp scope manager
  if (*(int *)(param_1 + 4) != 0) { // +0x4 = some active flag
    uVar1 = FUN_004d4730(0x20,0); // create temp object
    FUN_004d4e90(local_20,uVar1); // init scope guard for object
    uVar4 = 0;
    do {
      iVar2 = FUN_004d4690((&PTR_DAT_00e51cdc)[uVar4 * 2]); // check if controller slot is occupied
      if (iVar2 == 0) {
        uVar1 = FUN_004d5000(local_10,&DAT_00e337ec); // allocate string "Player" or similar
        FUN_004d3e20(uVar1); // assign name? or set player name
        uVar3 = uVar4; // found controller index
        if (local_10[0] != 0) {
          (*local_4)(local_10[0]); // release scope object
        }
        break;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < 0xc); // check 12 controller slots
    if (local_20[0] != 0) {
      (*local_14)(local_20[0]); // release scope object
    }
  }
  return uVar3; // returns controller slot index (0-11) or 0xC for none
}