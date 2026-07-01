// FUNC_NAME: Player::updateReputationOrScore
void __fastcall Player::updateReputationOrScore(int this)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_2c;
  undefined ***local_28;
  undefined1 local_24;
  undefined **local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  cVar2 = FUN_00481620(); // likely isGameActive() or similar
  if ((cVar2 != '\0') && (*(int *)(this + 0x290) == *(int *)(this + 0x230))) {
    iVar4 = *(int *)(this + 0x288); // current score/reputation value
    uVar5 = 0;
    do {
      piVar1 = (int *)(uVar5 + *(int *)(this + 0x298)); // pointer to array of 0x10-byte entries
      if ((((((*(int *)(uVar5 + *(int *)(this + 0x298)) != 0) || (piVar1[1] != 0)) ||
            (piVar1[2] != 0)) || (piVar1[3] != 0)) &&
          (((*piVar1 != -0x45245246 || (piVar1[1] != -0x41104111)) ||
           ((piVar1[2] != -0x153ea5ab || (piVar1[3] != -0x6eeff6ef)))))) &&
         ((iVar3 = FUN_00446100(piVar1,0), iVar3 != 0 &&
          (*(int *)(this + 0x290) == *(int *)(iVar3 + 0x230))))) {
        iVar3 = FUN_00b9a1c0(); // likely getScoreValue() or getReputationValue()
        iVar4 = iVar4 + iVar3;
      }
      uVar5 = uVar5 + 0x10;
    } while (uVar5 < 0x40);
    local_10 = *(undefined4 *)(this + 0x294);
    local_c = 0xffffffff;
    local_1c = 0xffffffff;
    local_18 = *(undefined4 *)(this + 0x280);
    local_2c = DAT_0112ecfc;
    local_28 = &local_20;
    local_20 = &PTR_LAB_00e35c24;
    local_8 = 0;
    local_4 = 0;
    local_24 = 0;
    local_14 = iVar4;
    FUN_00408a00(&local_2c,0); // likely sendEvent or updateUI
    if ((*(int *)(DAT_0112b9b4 + 0x40) != 0) &&
       (*(int *)(*(int *)(DAT_0112b9b4 + 0x40) + 0xd8) == 2)) {
      FUN_00440590(&DAT_0112fc98,this + 0x3c,*(undefined4 *)(this + 0x28c),0,4); // likely log or debug output
    }
  }
  return;
}