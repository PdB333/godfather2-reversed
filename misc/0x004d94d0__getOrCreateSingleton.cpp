// FUNC_NAME: getOrCreateSingleton
undefined4 * getOrCreateSingleton(void)

{
  if ((_DAT_01223d10 & 1) == 0) {
    _DAT_01223d10 = _DAT_01223d10 | 1;
    DAT_01223d00 = 0;
    DAT_01223d04 = 0;
    DAT_01223d08 = 0;
    DAT_01223d0c = 0;
  }
  return &DAT_01223d00;
}