// FUNC_NAME: PopupMenu::handleButtonPress
// Function address: 0x00982910
// Role: Handles button click events for popup menus by matching the action path string.
// The function compares param2 (a path string) against known button paths and triggers corresponding actions.
// Uses fields at +0x6c (popup index) and +0x70 (selected option index).

undefined4 __thiscall PopupMenu::handleButtonPress(int this, byte *pathString)
{
  byte bVar1;
  undefined4 result;
  byte *pComp1;
  int cmpResult;
  byte *pComp2;
  bool bEqual;
  byte formattedPath [64];
  
  // First check: direct match against "/ppop/button/button"
  cmpResult = 0x14;
  bEqual = true;
  pComp1 = (byte *)"/ppop/button/button";
  pComp2 = pathString;
  do {
    if (cmpResult == 0) break;
    cmpResult = cmpResult + -1;
    bEqual = *pComp1 == *pComp2;
    pComp1 = pComp1 + 1;
    pComp2 = pComp2 + 1;
  } while (bEqual);
  if (bEqual) {
LAB_0098292f:
    result = FUN_00466860();           // See: get some ID (e.g., sound or action)
    FUN_005bf350(result);              // Play/perform action
    return 1;
  }
  
  // Check against "/ppop/popup_root/popup_%d/button_0/button"
  FUN_00910160(formattedPath, "/ppop/popup_root/popup_%d/button_0/button", *(int *)(this + 0x6c) + -1);
  pComp1 = formattedPath;
  pComp2 = pathString;
  do {
    bVar1 = *pComp1;
    bEqual = bVar1 < *pComp2;
    if (bVar1 != *pComp2) {
LAB_00982990:
      cmpResult = (1 - (uint)bEqual) - (uint)(bEqual != 0);
      goto LAB_00982995;
    }
    if (bVar1 == 0) break;
    bVar1 = pComp1[1];
    bEqual = bVar1 < pComp2[1];
    if (bVar1 != pComp2[1]) goto LAB_00982990;
    pComp1 = pComp1 + 2;
    pComp2 = pComp2 + 2;
  } while (bVar1 != 0);
  cmpResult = 0;
LAB_00982995:
  if (cmpResult != 0) {
    // Not button_0, try button_1
    FUN_00910160(formattedPath, "/ppop/popup_root/popup_%d/button_1/button", *(int *)(this + 0x6c) + -1);
    pComp1 = formattedPath;
    pComp2 = pathString;
    do {
      bVar1 = *pComp1;
      bEqual = bVar1 < *pComp2;
      if (bVar1 != *pComp2) {
LAB_009829f8:
        cmpResult = (1 - (uint)bEqual) - (uint)(bEqual != 0);
        goto LAB_009829fd;
      }
      if (bVar1 == 0) break;
      bVar1 = pComp1[1];
      bEqual = bVar1 < pComp2[1];
      if (bVar1 != pComp2[1]) goto LAB_009829f8;
      pComp1 = pComp1 + 2;
      pComp2 = pComp2 + 2;
    } while (bVar1 != 0);
    cmpResult = 0;
LAB_009829fd:
    if (cmpResult == 0) goto LAB_0098292f;  // Matched button_1 -> same action as first
    // Not button_1, try button_2
    FUN_00910160(formattedPath, "/ppop/popup_root/popup_%d/button_2/button", *(int *)(this + 0x6c) + -1);
    pComp1 = formattedPath;
    pComp2 = pathString;
    do {
      bVar1 = *pComp1;
      bEqual = bVar1 < *pComp2;
      if (bVar1 != *pComp2) {
LAB_00982a44:
        cmpResult = (1 - (uint)bEqual) - (uint)(bEqual != 0);
        goto LAB_00982a49;
      }
      if (bVar1 == 0) break;
      bVar1 = pComp1[1];
      bEqual = bVar1 < pComp2[1];
      if (bVar1 != pComp2[1]) goto LAB_00982a44;
      pComp1 = pComp1 + 2;
      pComp2 = pComp2 + 2;
    } while (bVar1 != 0);
    cmpResult = 0;
LAB_00982a49:
    if (cmpResult == 0) {
      FUN_005bf350(10);                 // Action ID 10 (e.g., sound or close)
      return 1;
    }
    // Not button_2, try button_3
    FUN_00910160(formattedPath, "/ppop/popup_root/popup_%d/button_3/button", *(int *)(this + 0x6c) + -1);
    pComp1 = formattedPath;
    pComp2 = pathString;
    do {
      bVar1 = *pComp1;
      bEqual = bVar1 < *pComp2;
      if (bVar1 != *pComp2) {
LAB_00982aa2:
        cmpResult = (1 - (uint)bEqual) - (uint)(bEqual != 0);
        goto LAB_00982aa7;
      }
      if (bVar1 == 0) break;
      bVar1 = pComp1[1];
      bEqual = bVar1 < pComp2[1];
      if (bVar1 != pComp2[1]) goto LAB_00982aa2;
      pComp1 = pComp1 + 2;
      pComp2 = pComp2 + 2;
    } while (bVar1 != 0);
    cmpResult = 0;
LAB_00982aa7:
    if (cmpResult == 0) {
      FUN_005bf350(0xc);                // Action ID 12 (0xc)
      return 1;
    }
    // Finally, check against options path
    FUN_00910160(formattedPath, "/ppop/popup_root/popup_%d/options/item_%d/option",
                 *(int *)(this + 0x6c) + -1, *(undefined4 *)(this + 0x70));
    pComp1 = formattedPath;
    do {
      bVar1 = *pComp1;
      bEqual = bVar1 < *pathString;
      if (bVar1 != *pathString) {
LAB_00982b04:
        cmpResult = (1 - (uint)bEqual) - (uint)(bEqual != 0);
        goto LAB_00982b09;
      }
      if (bVar1 == 0) break;
      bVar1 = pComp1[1];
      bEqual = bVar1 < pathString[1];
      if (bVar1 != pathString[1]) goto LAB_00982b04;
      pComp1 = pComp1 + 2;
      pathString = pathString + 2;
    } while (bVar1 != 0);
    cmpResult = 0;
LAB_00982b09:
    if (cmpResult != 0) {
      return 0;                          // No match -> unhandled
    }
  }
  result = FUN_00466840();               // See: get another ID
  FUN_005bf350(result);
  return 1;
}