// FUNC_NAME: UIManager::createUIElement
uint * __thiscall UIManager::createUIElement(char *elementType, undefined4 param_2, undefined4 param_3, int param_4)
{
  char cVar1;
  uint *puVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  // Attempt to allocate a base UI element from the resource manager
  puVar2 = (uint *)FUN_005aea60(param_3, in_EAX, elementType, 1, 1);
  
  // Check if element is valid and if certain conditions are met
  if (((~(byte)(*puVar2 >> 0xf) & 1) != 0) ||
     ((cVar1 = FUN_005a3dc0(), cVar1 == '\0' && (cVar1 = FUN_005a7eb0(), cVar1 == '\0')))) {
    // If conditions fail, process pending operations
    if (0 < param_4) {
      do {
        FUN_005a0c50(); // Process UI events
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    return (uint *)0x0;
  }
  
  // Determine element type and create appropriate UI object
  iVar3 = __stricmp(elementType, "sound");
  if (iVar3 == 0) {
    iVar3 = (*DAT_0119caf0)(0x58, 0); // Allocate memory for sound element
    if (iVar3 != 0) {
      FUN_0059c3b0(); // Initialize sound element
      puVar2 = (uint *)FUN_005bb420(); // Get sound element pointer
      goto LAB_005aefd3;
    }
  }
  else {
    iVar3 = __stricmp(elementType, "array");
    if (iVar3 == 0) {
      iVar3 = (*DAT_0119caf0)(0x58, 0); // Allocate memory for array element
      if (iVar3 == 0) {
        puVar2 = (uint *)0x0;
      }
      else {
        puVar2 = (uint *)FUN_005ab3e0(); // Initialize array element
      }
      iVar3 = 0;
      if (0 < param_4) {
        do {
          uVar4 = FUN_005a0d00(iVar3); // Get child element
          FUN_005ab520(uVar4); // Add child to array
          iVar3 = iVar3 + 1;
        } while (iVar3 < param_4);
      }
      goto LAB_005aefd3;
    }
    iVar3 = __stricmp(elementType, "color");
    if (iVar3 == 0) {
      iVar3 = (*DAT_0119caf0)(0x50, 0); // Allocate memory for color element
      if (iVar3 != 0) {
        FUN_005a0d00(0); // Initialize color
        puVar2 = (uint *)FUN_005ac0e0(); // Get color element pointer
        goto LAB_005aefd3;
      }
    }
    else {
      iVar3 = __stricmp(elementType, "movieclip");
      if (iVar3 == 0) {
        iVar3 = (*DAT_0119caf0)(); // Allocate memory for movieclip element
        if (iVar3 != 0) {
          puVar2 = (uint *)FUN_005ac2c0(); // Initialize movieclip
          goto LAB_005aefd3;
        }
      }
      else {
        // Default: allocate generic UI element
        iVar3 = (*DAT_0119caf0)(0x4c, 0);
        if (iVar3 != 0) {
          puVar2 = (uint *)FUN_005a8660(); // Initialize generic element
          goto LAB_005aefd3;
        }
      }
    }
  }
  puVar2 = (uint *)0x0;
  
LAB_005aefd3:
  // Check if element needs special handling based on type flags
  if (puVar2 != DAT_0119cbbc) {
    uVar5 = *puVar2 & 0x7fff;
    if ((uVar5 != 0x19) &&
       (((~(byte)(*puVar2 >> 0xf) & 1) != 0 ||
        (((uVar5 != 0xb && (uVar5 != 0x18)) && (uVar5 != 0x17)))))) {
      FUN_0059c230(puVar2); // Apply special element behavior
    }
  }
  
  // Finalize element creation
  FUN_005aec20(puVar2, param_4);
  FUN_005a0c50(); // Process UI events
  return puVar2;
}