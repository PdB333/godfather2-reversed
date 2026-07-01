// FUNC_NAME: ConditionEvaluator::evaluateConditions
undefined4 __thiscall ConditionEvaluator::evaluateConditions(int *this, uint handle1, uint data1, uint handle2, int data2, int *ruleArray, uint ruleCount)
{
  int savedHandle1;
  bool isValid;
  int temp;
  
  savedHandle1 = handle1;
  isValid = isValidHandle(handle1, data1);
  if (isValid) {
    isValid = isValidHandle(handle2, data2);
  }
  if (!isValid) {
    return 0;  // invalid handles
  }
  
  handle1 = 0;  // reused as loop index
  if (ruleCount != 0) {
    do {
      // ruleArray points to triples: { leftKey, unused?, rightKey }
      if (*ruleArray == 0) {
        temp = 0;
      } else {
        temp = ruleArray[2];  // rightKey
      }
      
      if (data2 == temp) {
        if (savedHandle1 == *ruleArray) {
          // left side matches rule
          temp = getValueByLeft(data2, data1);
          if (temp != 0) {
            isValid = (**(code (__thiscall **)(int, int))(*this + 0x30))(savedHandle1, temp);
            if (isValid) {
              return 0;  // condition failed
            }
          }
        } else {
          // right side matches rule (handle2 == leftKey condition is not met)
          temp = getValueByRight(data2, ruleArray);
          if (temp != 0) {
            isValid = (**(code (__thiscall **)(uint, int))(*this + 0x34))(handle2, temp);
            if (isValid) {
              return 0;
            }
          }
        }
      }
      handle1 = handle1 + 1;
      ruleArray = ruleArray + 3;
    } while (handle1 < ruleCount);
  }
  
  return 1;  // all conditions passed
}