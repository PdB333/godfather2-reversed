// FUNC_NAME: OptionsManager::initOptionValues
void __fastcall OptionsManager::initOptionValues(int this)
{
  int iVar1;
  
  *(undefined4 *)(this + 0x54) = 0; // currentOptionIndex
  if (*(int *)(this + 0x60) != 0) { // optionCount
    do {
      if (*(int *)(this + 0x58) == 0) { // isOptionInitialized
        iVar1 = *(int *)(this + 0x54); // currentOptionIndex
        if (iVar1 == 0) {
          *(undefined4 *)(this + 0x6c) = *(undefined4 *)(this + 0x70); // defaultOptionValue0
        }
        else if (iVar1 == 1) {
          *(undefined4 *)(this + 0x6c) = *(undefined4 *)(this + 0x74); // defaultOptionValue1
        }
        else if (iVar1 == 2) {
          *(undefined4 *)(this + 0x6c) = *(undefined4 *)(this + 0x78); // defaultOptionValue2
        }
        FUN_005a04a0("InitOptionValue",0,&DAT_00d87288,0); // logInitOptionValue
      }
      *(int *)(this + 0x54) = *(int *)(this + 0x54) + 1; // increment currentOptionIndex
    } while (*(uint *)(this + 0x54) < *(uint *)(this + 0x60)); // loop until all options processed
  }
  return;
}