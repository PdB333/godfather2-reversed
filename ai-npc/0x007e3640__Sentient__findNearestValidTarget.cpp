// FUNC_NAME: Sentient::findNearestValidTarget
int __thiscall Sentient::findNearestValidTarget(int this, int excludeTarget1, int excludeTarget2)
{
  int bestTarget;
  int *iter;
  char isValid;
  int currentTarget;
  float bestDistance;
  float distance;
  int playerIndex;
  
  if (*(int *)(this + 0x84) == 0) {
    bestTarget = 0;
  }
  else {
    bestTarget = *(int *)(this + 0x84) + -0x48; // +0x84: currentTarget, offset -0x48 to get object pointer
    if (bestTarget != 0) {
      return bestTarget;
    }
  }
  
  playerIndex = FUN_00471610(); // GetPlayerIndex() - returns current player index
  bestDistance = DAT_00d6f97c; // Maximum search distance constant
  
  // +0x98: linked list of target candidates (next pointer at offset +0x0C)
  for (iter = *(int **)(this + 0x98); iter != (int *)0x0; iter = (int *)iter[3]) {
    if ((((*iter != 0) && (currentTarget = *iter + -0x48, currentTarget != 0)) && (currentTarget != excludeTarget1)) &&
       ((currentTarget != excludeTarget2 && (isValid = FUN_007f81c0(currentTarget, DAT_00d5f52c), isValid != '\0')))) {
      // FUN_007f81c0: IsTargetValid(target, someGlobalFlag)
      // FUN_007f8020: CalculateDistanceSquared(pos1, pos2)
      int targetIndex = FUN_00471610(); // Get index for distance calculation
      distance = (float)FUN_007f8020(targetIndex + 0x30, playerIndex + 0x30, playerIndex + 0x20);
      if (distance < bestDistance) {
        bestTarget = currentTarget;
        bestDistance = distance;
      }
    }
  }
  
  return bestTarget;
}