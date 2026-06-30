// FUNC_NAME: LuaBinding::getFieldValue
uint * FUN_005ab7b0(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  uint *puVar5;
  long lVar6;
  char *pcVar7;
  char *unaff_ESI;
  
  pcVar3 = param_1;
  iVar4 = __stricmp(unaff_ESI,"length");
  if (iVar4 == 0) {
    // Handle "length" field - return the length of the array/table
    puVar5 = (uint *)(*DAT_0119caf0)(8,0);  // Allocate 8 bytes
    if (puVar5 == (uint *)0x0) {
      return (uint *)0x0;
    }
    uVar2 = *(uint *)(pcVar3 + 0x54);  // +0x54: array length field
    *puVar5 = *puVar5 & 0xffff8007 | 7;  // Set type flags (likely Lua type tag)
    *(undefined2 *)((int)puVar5 + 2) = 0;
    *puVar5 = *puVar5 | 0x8000;
    puVar5[1] = uVar2;  // Store the length value
    return puVar5;
  }
  
  // Try to parse the field name as an integer index
  param_1 = (char *)0x0;
  lVar6 = _strtol(unaff_ESI,&param_1,10);
  pcVar7 = unaff_ESI;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  
  // Check if the entire string was parsed as a number
  if (((int)pcVar7 - (int)(unaff_ESI + 1) < 1) ||
     (param_1 != unaff_ESI + ((int)pcVar7 - (int)(unaff_ESI + 1)))) {
    // Not a valid integer index - try to look up by name
    puVar5 = (uint *)FUN_005bb050(pcVar3 + 4,unaff_ESI);  // +4: hash table offset
    if (puVar5 != (uint *)0x0) {
      return puVar5;
    }
  }
  else {
    // Valid integer index - access array element
    iVar4 = FUN_0059c450();  // Get the Lua state/table
    if (((-1 < lVar6) && (lVar6 < *(int *)(iVar4 + 0x54))) &&  // +0x54: array size
       (*(int *)(*(int *)(iVar4 + 0x4c) + lVar6 * 4) != 0)) {  // +0x4c: array data pointer
      return *(uint **)(*(int *)(iVar4 + 0x4c) + lVar6 * 4);  // Return element at index
    }
  }
  
  // Return nil if not found
  return DAT_0119cbbc;  // Global nil value
}