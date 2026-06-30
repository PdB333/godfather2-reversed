// FUNC_NAME: LuaRegexMatcher::processCaptures
int LuaRegexMatcher::processCaptures(int param_1, int param_2)
{
  int *captureArray;
  int captureCount;
  int index;
  int *capturePtr;
  int captureStart;
  int captureEnd;
  int iVar2;
  int iVar3;
  undefined4 *stackVar;
  code *pcVar5;
  int iVar6;
  int *piVar8;
  int *unaff_EDI; // this pointer
  int iStack_c;
  
  iVar6 = checkStack(); // FUN_006254f0 - likely a stack guard check
  if (iVar6 == 0) {
    logError("stack overflow (%s)", "too many captures"); // FUN_00627bd0
  }
  
  // If no captures needed and we have input, just copy the string segment
  if ((unaff_EDI[3] == 0) && (param_1 != 0)) {
    copySubstring(param_1, param_2 - param_1); // FUN_00625c60
    return 1;
  }
  
  iStack_c = 0;
  if (0 < unaff_EDI[3]) { // number of captures
    piVar8 = unaff_EDI + 4; // capture array start (offset +0x10)
    do {
      iVar6 = piVar8[1]; // capture end index
      if (iVar6 == -1) {
        logError("unfinished capture"); // FUN_00627bd0
        pcVar5 = (code *)swi(3); // debug break
        iVar6 = (*pcVar5)();
        return iVar6;
      }
      if (iVar6 == -2) { // empty capture
        iVar6 = *piVar8; // capture start
        iVar2 = *unaff_EDI; // string start
        iVar3 = unaff_EDI[2]; // output buffer pointer
        stackVar = *(undefined4 **)(iVar3 + 8); // +0x8 in output buffer
        *stackVar = 3; // type hint
        stackVar[1] = (float)((iVar6 - iVar2) + 1); // length of matched text
        // Advance output buffer pointer
        *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 8;
      }
      else { // match found
        iVar2 = unaff_EDI[2]; // output buffer
        iVar3 = *piVar8; // capture start
        // Check if we have room in the output buffer (header +0x20 <= +0x24 check)
        if (*(uint *)(*(int *)(iVar2 + 0x10) + 0x20) <= *(uint *)(*(int *)(iVar2 + 0x10) + 0x24)) {
          expandBuffer(); // FUN_00627360
        }
        stackVar = *(undefined4 **)(iVar2 + 8); // current output position
        *stackVar = 4; // type hint for substring
        uVar7 = storeMatchedString(iVar2, iVar3, iVar6); // FUN_00638920 - stores the substring
        stackVar[1] = uVar7;
        *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 8;
      }
      iStack_c = iStack_c + 1;
      piVar8 = piVar8 + 2; // advance to next capture pair
    } while (iStack_c < unaff_EDI[3]);
  }
  return unaff_EDI[3]; // return number of captures processed
}