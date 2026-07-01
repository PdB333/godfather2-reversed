// Xbox PDB: int __cdecl luaL_loadfile(struct lua_State *,char const *)
// FUNC_NAME: StreamManager::loadStreamFromFile
undefined4 StreamManager::loadStreamFromFile(char *filename)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  FILE *pFVar5;
  int iVar6;
  int *piVar7;
  int unaff_EDI;
  FILE *local_204;
  
  // Calculate number of entries already in stream buffer (8 bytes per entry)
  iVar6 = (*(int *)(unaff_EDI + 8) - *(int *)(unaff_EDI + 0xc) >> 3) + 1;
  
  if (filename == (char *)0x0) {
    // No filename - use default stream
    if (*(uint *)(*(int *)(unaff_EDI + 0x10) + 0x20) <= *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x24)) {
      FUN_00627360(); // likely growBuffer or realloc
    }
    puVar1 = *(undefined4 **)(unaff_EDI + 8);
    *puVar1 = 4; // stream type = 4 (likely BNK or audio)
    uVar2 = FUN_00638920(); // getStreamID or generateID
    puVar1[1] = uVar2;
    *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 8;
    local_204 = (FILE *)FUN_00b995f7(); // getDefaultFileHandle or stdin
  }
  else {
    FUN_00625d40(&PTR_LAB_00e41624,filename); // log or resolve path
    local_204 = _fopen(filename,"r");
  }
  
  if (local_204 == (FILE *)0x0) {
LAB_0062913c:
    uVar2 = FUN_00629050(iVar6); // handleLoadError or cleanup
    return uVar2;
  }
  
  pFVar5 = local_204;
  iVar3 = FID_conflict__getc(local_204);
  iVar3 = _ungetc(iVar3,pFVar5);
  iVar4 = _isspace(iVar3);
  
  // Check if file is binary (not text)
  if (((iVar4 == 0) && (iVar3 = _isprint(iVar3), iVar3 == 0)) &&
     (pFVar5 = (FILE *)FUN_00b995f7(), local_204 != pFVar5)) {
    _fclose(local_204);
    local_204 = _fopen(filename,"rb");
    if (local_204 == (FILE *)0x0) goto LAB_0062913c;
  }
  
  piVar7 = (int *)(*(int *)(unaff_EDI + 8) + -8);
  if (((piVar7 != (int *)0x0) && (*piVar7 != 4)) &&
     (FUN_00633990(), // flush or finalize previous stream
     *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x20) <= *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x24)))
  {
    FUN_00627360(); // grow buffer
  }
  
  uVar2 = FUN_00626310(); // parseStream or loadData
  iVar3 = _ferror(local_204);
  pFVar5 = (FILE *)FUN_00b995f7();
  if (local_204 != pFVar5) {
    _fclose(local_204);
  }
  
  if (iVar3 != 0) {
    FUN_006255e0(); // logError
    uVar2 = FUN_00629050(iVar6); // handleLoadError
    return uVar2;
  }
  
  FUN_00625630(); // finalizeLoad
  return uVar2;
}