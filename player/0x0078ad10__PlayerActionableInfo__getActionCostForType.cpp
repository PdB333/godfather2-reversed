// FUNC_NAME: PlayerActionableInfo::getActionCostForType
float __thiscall PlayerActionableInfo::getActionCostForType(int thisPtr, uint actionType, int playerPtr)
{
  int actionCostTable;
  float result;
  
  actionCostTable = *(int *)(thisPtr + 0x1c);
  result = 0.0f;
  if ((actionCostTable != 0) && (actionCostTable != 0x3c)) {
    if ((actionType != *(uint *)(playerPtr + 0x68c) >> 2) && (actionType != *(uint *)(playerPtr + 0x6b4) >> 2)) {
      if (actionType == *(uint *)(playerPtr + 0x6b8) >> 2) {
        return *(float *)(actionCostTable + 0x94); // +0x94: cost for this specific action type
      }
      if ((actionType != *(uint *)(playerPtr + 0x668) >> 2) &&
         (actionType != *(uint *)(playerPtr + 0x698) >> 2)) {
        if (((((((actionType != *(uint *)(playerPtr + 0x678) >> 2) &&
                (actionType != *(uint *)(playerPtr + 0x67c) >> 2)) &&
               (actionType != *(uint *)(playerPtr + 0x680) >> 2)) &&
              ((actionType != *(uint *)(playerPtr + 0x684) >> 2 &&
               (actionType != *(uint *)(playerPtr + 0x688) >> 2)))) &&
             ((actionType != *(uint *)(playerPtr + 0x6a0) >> 2 &&
              ((actionType != *(uint *)(playerPtr + 0x6a4) >> 2 &&
               (actionType != *(uint *)(playerPtr + 0x6a8) >> 2)))))) &&
            (actionType != *(uint *)(playerPtr + 0x6ac) >> 2)) &&
           (actionType != *(uint *)(playerPtr + 0x6b0) >> 2)) {
          return *(float *)(actionCostTable + 0xa0); // +0xa0: default cost for unlisted actions
        }
        return *(float *)(actionCostTable + 0x9c); // +0x9c: cost for secondary group
      }
      return *(float *)(actionCostTable + 0x98); // +0x98: cost for primary group
    }
    result = *(float *)(actionCostTable + 0x90); // +0x90: cost for special action types
  }
  return result;
}