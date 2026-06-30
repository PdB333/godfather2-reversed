// FUNC_NAME: SomeClass::registerStringTableEntries
void SomeClass::registerStringTableEntries(void)
{
  byte *pbVar1;
  char cVar2;
  char *pcVar3;
  undefined4 uVar4;
  int iVar5;
  int this; // unaff_EDI, likely this pointer
  
  // Iterate through string table indices 0x54 to 0x8C (step 4)
  // These are likely hash/ID values for string table entries
  iVar5 = 0x54;
  do {
    // Get pointer to string literal (likely a debug label or table name)
    // The string "table index is NaN" suggests these are table indices
    pcVar3 = *(char **)("table index is NaN" + iVar5 + 4);
    
    // Calculate string length (iterate to null terminator)
    do {
      cVar2 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    
    // Call function to get hash/ID for this string
    uVar4 = FUN_00638920(); // Likely stringToHash or getStringId
    
    // Store the hash/ID in the string table array at offset +0x10 from this
    // +0x10: pointer to string table array
    *(undefined4 *)(iVar5 + *(int *)(this + 0x10)) = uVar4;
    
    // Set flag 0x10 on the entry at offset +5 (likely a status/validity flag)
    pbVar1 = (byte *)(*(int *)(*(int *)(this + 0x10) + iVar5) + 5);
    *pbVar1 = *pbVar1 | 0x10;
    
    iVar5 = iVar5 + 4;
  } while (iVar5 < 0x90);
  
  return;
}