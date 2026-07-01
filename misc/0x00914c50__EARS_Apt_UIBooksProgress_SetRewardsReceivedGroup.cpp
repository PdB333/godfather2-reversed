// Xbox PDB: EARS_Apt_UIBooksProgress_SetRewardsReceivedGroup
// FUNC_NAME: ProgressMenu::populateFavorsList
void __fastcall ProgressMenu::populateFavorsList(int thisPtr)
{
  int favorIndex;
  int* favorArray;
  char flag;
  char* favorName;
  uint i;
  int* favorListPtr;
  char* iconName;
  char* displayName;
  char* unknownStr;
  int localCounter;
  void* nullFunc;
  
  // Initialize the progress group for favors
  FUN_005a04a0("ProgressSetGroup", 0, &DAT_00d84448, 1, "$dv_menu_books_progress_favors_earned");
  
  // Initialize favor counter (offset +0x04 in 'this')
  *(int*)(thisPtr + 4) = 0;
  
  favorListPtr = (int*)DAT_011299c0;
  favorArray = (int*)(DAT_011299c0 + 8);  // offset +0x08: pointer to favor list
  i = 0;
  
  if (*(int*)(favorListPtr + 0xc) != 0) {  // offset +0x0c: number of favors
    do {
      favorIndex = *(int*)(*favorArray + i * 4);  // each element pointer
      if (favorIndex != 0 && ((*(uint*)(favorIndex + 0x170) >> 4 & 1) != 0)) {  // +0x170 bit 4: favor earned?
        localCounter = 0;
        unknownStr = 0;
        nullFunc = 0;
        
        // Get localized favor name using favor ID at +0x80
        FUN_004d4ad0(&unknownStr, &PTR_LAB_00d78708, *(undefined4*)(favorIndex + 0x80));
        
        flag = FUN_00891920();  // Check if favor is completed
        if (flag == '\0') {
          flag = FUN_008918c0();  // Check if favor is discovered
          if (flag == '\0') {
            displayName = "$dv_menu_books_progress_unknow_favor";
            iconName = "Unknown";
          } else {
            displayName = unknownStr;
            if (unknownStr == 0) {
              displayName = &DAT_0120546e;  // empty string
            }
            iconName = "icon_reward_favor";
          }
        } else {
          displayName = unknownStr;
          if (unknownStr == 0) {
            displayName = &DAT_0120546e;
          }
          iconName = "icon_reward_favor_checked";
        }
        
        // Add the item to the progress list
        FUN_005a04a0("ProgressAddItem", 0, &DAT_00d84448, 3, &DAT_00e36da0, iconName, displayName);
        
        // Increment favor count
        *(int*)(thisPtr + 4) = *(int*)(thisPtr + 4) + 1;
        
        // Cleanup allocated string if any (function pointer in local_4 is null, potential bug)
        if (unknownStr != 0) {
          ((void (*)(char*))nullFunc)(unknownStr);
        }
      }
      i = i + 1;
    } while (i < *(uint*)(favorListPtr + 0xc));
  }
  return;
}