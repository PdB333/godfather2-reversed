// FUNC_NAME: initStaticPresetValues
void initStaticPresetValues(void)
{
  uint *pAlloc;
  uint val1;
  uint val2;

  pAlloc = (uint *)allocate(0xd, 4, 0, 1, 0);
  val1 = DAT_00e2eff4;
  val2 = DAT_00e2b1a4;
  if (pAlloc != (uint *)0x0) {
    pAlloc[0] = val1;
    pAlloc[1] = val2;
    pAlloc[2] = val2;
    pAlloc[3] = val2;
    pAlloc[4] = val2;
    pAlloc[5] = val1;
    pAlloc[6] = val1;
    pAlloc[7] = val1;
    finalizePresetInit();
  }
  return;
}