// FUNC_NAME: StringTable::internString
int StringTable::internString(char *str, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  int iVar6;
  undefined4 local_14;
  int local_10 [3];
  code *local_4;
  
  bVar5 = false;
  local_14 = 0;
  iVar6 = (int)DAT_01129f90 - DAT_01129f8c; // Calculate size difference between current and base pointer
  iVar3 = FUN_009c8e50(0x4c); // Allocate 0x4C bytes for string entry
  if (iVar3 == 0) {
    local_14 = 0;
  }
  else {
    pcVar4 = str;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    FUN_004dba80(str,(int)pcVar4 - (int)(str + 1)); // Hash the string (likely CRC or FNV)
    bVar5 = true;
    local_14 = FUN_0069afc0(local_10,&DAT_01129f9c,param_3,param_2,param_4); // Insert into hash table
  }
  if (DAT_01129f90 < DAT_01129f94) { // Check if there's room in the string pool
    puVar2 = DAT_01129f90 + 1;
    if (DAT_01129f90 != (undefined4 *)0x0) {
      *DAT_01129f90 = local_14; // Store the string ID
      DAT_01129f90 = puVar2;
      puVar2 = DAT_01129f90;
    }
  }
  else {
    FUN_0069ab10(DAT_01129f90,&local_14); // Expand the string pool
    puVar2 = DAT_01129f90;
  }
  DAT_01129f90 = puVar2;
  if ((bVar5) && (local_10[0] != 0)) {
    (*local_4)(local_10[0]); // Call cleanup function if needed
  }
  return iVar6 >> 2; // Return index into string table
}