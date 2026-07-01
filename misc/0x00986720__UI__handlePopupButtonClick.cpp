// FUNC_NAME: UI::handlePopupButtonClick
char FUN_00986720(byte *buttonName)
{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  char result;
  uint buttonIndex;
  bool bVar7;
  byte pathBuffer [64];
  
  result = '\0';
  buttonIndex = 0;
  do {
    if (1 < buttonIndex) {
      return result;
    }
    // Build path: /spop/popup_root/popup/button_%d/button
    FUN_00910160(pathBuffer, "/spop/popup_root/popup/button_%d/button", buttonIndex);
    pbVar2 = pathBuffer;
    pbVar4 = buttonName;
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_00986770:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_00986775;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar7 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_00986770;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00986775:
    if (iVar3 == 0) {
      // Match found - build button path and trigger roll out
      FUN_00910160(pathBuffer, &DAT_00e3266c, buttonIndex);
      FUN_005a04a0("RollOutButton", 0, &DAT_00d90d34, 1, pathBuffer);
      result = '\x01';
    }
    buttonIndex = buttonIndex + 1;
    if (result != '\0') {
      return result;
    }
  } while( true );
}