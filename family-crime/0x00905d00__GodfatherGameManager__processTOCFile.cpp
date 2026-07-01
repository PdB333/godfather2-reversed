// FUNC_NAME: GodfatherGameManager::processTOCFile
void __thiscall GodfatherGameManager::processTOCFile(int *this, int param_2, char *param_3, undefined4 param_4)
{
  char *_Str;
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  char *local_4c [3];
  code *pcStack_40;
  int local_3c;
  undefined4 local_38;
  code *local_30;
  char *local_2c;
  code *local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  code *local_10;
  char *local_c;
  undefined1 local_8;
  undefined4 local_4;
  
  _Str = param_3;
  // Find first newline
  pcVar2 = _strchr(param_3,10);
  // Find second newline (skip first line)
  pcVar3 = _strchr(pcVar2 + 1,10);
  pcVar3 = pcVar3 + 1;
  cVar1 = *pcVar3;
  pcVar2 = pcVar3;
  // Find end of third line
  while (cVar1 != '\n') {
    pcVar2 = pcVar2 + 1;
    cVar1 = *pcVar2;
  }
  local_30 = (code *)0x0;
  // Extract the third line (likely the TOC file path)
  FUN_004d3c40(pcVar3,(int)pcVar2 - (int)pcVar3);
  // Set global folder
  FUN_004d3bc0("globalfolder");
  // Open TOC file
  FUN_004d4300(&DAT_00e2f048);
  FUN_004d43f0(local_3c,0,local_38);
  FUN_004d4300("_toc.str");
  pcVar2 = local_4c[0];
  if (local_4c[0] == (char *)0x0) {
    pcVar2 = &DAT_0120546e;
  }
  // Search for the TOC entry in the file
  pcVar2 = _strstr(_Str,pcVar2);
  if (((pcVar2 != (char *)0x0) && (pcVar2 = _strchr(pcVar2,0x20), pcVar2 != (char *)0x0)) &&
     (pcVar3 = _strchr(pcVar2,10), pcVar3 != (char *)0x0)) {
    local_20 = (code *)0x0;
    // Extract the hex address after the space
    FUN_004d3c40(pcVar2 + 1,(int)pcVar3 - (int)(pcVar2 + 1));
    pcVar2 = local_2c;
    if (local_2c == (char *)0x0) {
      pcVar2 = &DAT_0120546e;
    }
    // Parse hex address
    iVar4 = FID_conflict__sscanf(pcVar2,"0x%x",&param_3);
    if (iVar4 != 0) {
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      local_10 = (code *)0x0;
      local_c = (char *)0xfe16702f;
      local_8 = 0;
      local_4 = 0;
      // Initialize some structure
      FUN_004d3e20(local_4c);
      local_c = param_3;
      // Call virtual function at +0x2c (likely some validation)
      cVar1 = (**(code **)(*param_1 + 0x2c))(param_3);
      local_8 = cVar1 != '\0';
      // Process the entry
      FUN_00905ca0(&local_1c);
      if (local_1c != 0) {
        (*local_10)(local_1c);
      }
    }
    if (local_2c != (char *)0x0) {
      (*local_20)(local_2c);
    }
  }
  // Trim trailing newlines from the string
  pcVar2 = _strchr(_Str,0);
  pcVar2 = pcVar2 + -1;
  cVar1 = *pcVar2;
  while (cVar1 != '\n') {
    *pcVar2 = '\0';
    pcVar2 = _strchr(_Str,0);
    pcVar2 = pcVar2 + -1;
    cVar1 = *pcVar2;
  }
  // Call some processing function
  FUN_004122e0(param_2,_Str,param_4);
  // Set flag at +0x129 to 0
  *(undefined1 *)(param_2 + 0x129) = 0;
  // Update some array at this[0x86] + 0x18 + (this[0x87] - 1) * 0x1c
  // with value from this[0x83] + (this[0x87] - 1) * 4
  *(undefined4 *)(this[0x86] + 0x18 + (this[0x87] + -1) * 0x1c) =
       *(undefined4 *)(this[0x83] + (this[0x87] + -1) * 4);
  if (local_4c[0] != (char *)0x0) {
    (*pcStack_40)(local_4c[0]);
  }
  if (local_3c != 0) {
    (*local_30)(local_3c);
  }
  return;
}