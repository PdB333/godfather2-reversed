// FUNC_NAME: UIListWidget::handleScrollInput
undefined4 __thiscall UIListWidget::handleScrollInput(int this, byte *inputName, float inputValue)

{
  byte bVar1;
  byte *pbVar2;
  int cmpResult;
  byte *pbVar4;
  bool bVar5;
  
  // Check if list is disabled (offset +0xa08 likely a disabled flag)
  if (*(char *)(this + 0xa08) != '\0') {
    return 0;
  }
  
  // Compare inputName against first string at +0x404 (likely "ScrollUp" string)
  pbVar2 = (byte *)(this + 0x404);
  pbVar4 = inputName;
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_009611b0:
      cmpResult = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_009611b5;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_009611b0;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  cmpResult = 0;
LAB_009611b5:
  if (cmpResult != 0) {
    // Compare inputName against second string at +0x604 (likely "ScrollDown" string)
    pbVar2 = (byte *)(this + 0x604);
    pbVar4 = inputName;
    do {
      bVar1 = *pbVar2;
      bVar5 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_009611e1:
        cmpResult = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_009611e6;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar5 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_009611e1;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    cmpResult = 0;
LAB_009611e6:
    if ((cmpResult != 0) && (cmpResult = FUN_00960c50(inputName), cmpResult == -1)) {
      return 0;
    }
  }
  
  // Compare inputValue against thresholds for scroll direction
  if (_DAT_00d5780c < inputValue) {
    FUN_005a04a0("ScrollUp",0,&DAT_00d8d668,0);
    return 1;
  }
  if (DAT_00d5ccf8 <= inputValue) {
    return 0;
  }
  FUN_005a04a0("ScrollDown",0,&DAT_00d8d668,0);
  return 1;
}