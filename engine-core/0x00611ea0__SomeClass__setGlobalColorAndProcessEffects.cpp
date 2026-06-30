// FUNC_NAME: SomeClass::setGlobalColorAndProcessEffects
void FUN_00611ea0(void)

{
  undefined4 *colorData;
  
  _DAT_011f6880 = *colorData;
  uRam011f6884 = colorData[1];
  uRam011f6888 = colorData[2];
  uRam011f688c = colorData[3];
  if (DAT_012058e8 != 0) {
    if (*(int *)(DAT_012058e8 + 0x1c) != 0) {
      FUN_0060add0(*(undefined4 *)(DAT_012058e8 + 0x10),*(int *)(DAT_012058e8 + 0x1c));
    }
    if (*(int *)(DAT_012058e8 + 0x6c) != 0) {
      FUN_0060add0(*(undefined4 *)(DAT_012058e8 + 0x14),*(int *)(DAT_012058e8 + 0x6c));
    }
  }
  return;
}