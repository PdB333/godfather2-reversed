// FUNC_NAME: SomeManager::resetSomeData
void SomeManager::resetSomeData(int param_1)
{
  switch(param_1) {
  case 0:
    FUN_00402050(&DAT_011301c0,0); // +0x0? Reset data at offset 0x1c0
    return;
  case 1:
    FUN_00402050(&DAT_011304d8,0); // +0x4d8? Reset data at offset 0x4d8
    return;
  case 2:
    FUN_00402050(&DAT_01130448,0); // +0x448? Reset data at offset 0x448
    return;
  case 3:
    FUN_00402050(&DAT_011302c8,0); // +0x2c8? Reset data at offset 0x2c8
    return;
  case 4:
    FUN_00402050(&DAT_01130310,0); // +0x310? Reset data at offset 0x310
    return;
  case 5:
    FUN_00402050(&DAT_01130208,0); // +0x208? Reset data at offset 0x208
    return;
  case 6:
    FUN_00402050(&DAT_011302c0,0); // +0x2c0? Reset data at offset 0x2c0
  }
  return;
}