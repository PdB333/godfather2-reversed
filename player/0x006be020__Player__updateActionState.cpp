// FUNC_NAME: Player::updateActionState
void __fastcall Player::updateActionState(int thisPlayer)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  // Check if player has a vehicle (+0x54) and various conditions
  if ((((*(int *)(thisPlayer + 0x54) == 0) ||
       (((iVar2 = FUN_006b0ee0(*(int *)(thisPlayer + 0x54)), iVar2 != 0 &&
         (cVar1 = FUN_006b4440(), cVar1 != '\0')) && (iVar2 = FUN_006b4860(), iVar2 == 0)))) &&
      // Check if player is alive (+0x88) and game state is valid
      (((iVar2 = FUN_00446100(thisPlayer + 0x88,0), iVar2 != 0 && (iVar3 = FUN_007915b0(), iVar3 != 0))
       && ((~(byte)(*(uint *)(iVar3 + 0x84) >> 5) & 1) != 0)))) &&
     // Check if player is in combat or specific states
     (((cVar1 = FUN_007900b0(), cVar1 == '\0' || (iVar3 = FUN_008bf2f0(iVar2), iVar3 == 1)) ||
      ((iVar3 == 3 &&
       ((iVar3 = *(int *)(thisPlayer + 0x54), iVar3 != 0 && (iVar4 = FUN_00790d90(), iVar3 == iVar4))))
      )))) {
    // Check player flags (+0x5c) for specific bit
    uVar5 = *(uint *)(iVar2 + 0x5c) >> 0x15;
    if ((uVar5 & 1) != 0) {
      FUN_00792560(iVar2);
    }
    // Handle combat state
    iVar3 = FUN_00791300();
    if ((iVar3 != 0) && (cVar1 = FUN_0083e6a0(iVar3), cVar1 != '\0')) {
      FUN_0083de30(iVar3);
      FUN_006bd3a0(iVar3);
    }
    // Check if player should die
    cVar1 = FUN_00791230();
    if (cVar1 != '\0') {
      FUN_00791250(thisPlayer,0xffffffff);
      return;
    }
    // Clear flag if set
    if ((uVar5 & 1) != 0) {
      FUN_00792d80(iVar2);
    }
  }
  return;
}