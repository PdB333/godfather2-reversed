// FUNC_NAME: Player::checkForcedAction
int Player::checkForcedAction(int this) {
  float fVar1;
  char cVar2;
  int uVar3;
  float fVar4;
  
  if ((*(uint *)(this + 0x249c) >> 1 & 1) != 0) {
    uVar3 = 3;
    uVar3 = (**(code **)(*(int *)(this + 0x1f30) + 8))(3); // call virtual function at offset 8 on some object at +0x1f30
    fVar4 = (float)FUN_00465db0(uVar3, 3); // likely a distance/range calculation
    fVar1 = (float)fVar4;
    cVar2 = FUN_00800be0(); // likely get current game state or difficulty
    if (cVar2 == 0x18) { // some specific state/difficulty
      if (DAT_00d5f18c < fVar1) { // compare against global threshold
        return 2;
      }
    }
    else {
      if (DAT_00d5842c < fVar1) { // different threshold for other states
        return 2;
      }
      if (DAT_00d5f18c < fVar1) {
        return 1;
      }
    }
  }
  return 0;
}