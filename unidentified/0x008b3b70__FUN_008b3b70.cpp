// FUNC_NAME: SomeClass::setColorFromHealth
void SomeClass::setColorFromHealth(uint param_1, uint param_2)
{
  int *healthPtr;
  uint local_4;
  
  healthPtr = (int *)FUN_004baf90(param_1);
  if (healthPtr != (int *)0x0) {
    local_4 = 0;
    param_1 = 0;
    if (*healthPtr == 0) {
      local_4 = 0xff;
    }
    else {
      param_1 = 0xff;
    }
    FUN_0094ac00(param_2,local_4,0,param_1);
  }
  return;
}