// FUNC_NAME: SimManager::buildEntityListFromData
void __fastcall SimManager::buildEntityListFromData(int thisPtr)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  void *pvVar6;
  int iVar7;
  undefined4 *puVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int entityCount;
  uint uStack_2c;
  uint local_28;
  int *local_24;
  undefined1 auStack_20 [8];
  undefined1 auStack_18 [20];
  
  // Free existing entity list at +0x90
  FUN_009c8f10(*(undefined4 *)(thisPtr + 0x90));
  iVar10 = 0;
  *(undefined4 *)(thisPtr + 0x90) = 0;
  
  // Get entity count from data at +0x20 -> +0x0C
  uVar1 = *(uint *)(*(int *)(thisPtr + 0x20) + 0xc);
  *(uint *)(thisPtr + 0x94) = uVar1;
  
  if (uVar1 != 0) {
    // Allocate memory for entity list (each entry 0xC bytes)
    pvVar6 = (void *)FUN_009c8e80(-(uint)((int)((ulonglong)uVar1 * 0xc >> 0x20) != 0) |
                                  (uint)((ulonglong)uVar1 * 0xc));
    if (pvVar6 == (void *)0x0) {
      pvVar6 = (void *)0x0;
    }
    else {
      // Construct entity list entries using vector constructor
      _vector_constructor_iterator_(pvVar6,0xc,uVar1,(_func_void_ptr_void_ptr *)&LAB_00994a70);
    }
    *(void **)(thisPtr + 0x90) = pvVar6;
    
    local_28 = 0;
    local_24 = (int *)0x0;
    
    // Get some interface from +0x0C
    cVar5 = (**(code **)(**(int **)(thisPtr + 0xc) + 0x10))(0xae986323,&local_24);
    local_24 = (int *)(-(uint)(cVar5 != '\\0') & uStack_2c);
    
    iVar11 = 0;
    if (0 < *(int *)(*(int *)(thisPtr + 0x20) + 0xc)) {
LAB_0099576d:
      iVar2 = *(int *)(*(int *)(*(int *)(thisPtr + 0x20) + 8) + iVar11 * 4);
      iVar3 = *(int *)(iVar2 + 0x78);  // Number of properties
      iVar7 = 0;
      if (0 < iVar3) {
        piVar9 = *(int **)(iVar2 + 0x74);  // Property array
        do {
          if (*piVar9 == -0x65eb2ccf) {  // Hash for some property type
            puVar8 = (undefined4 *)FUN_004af8c0(auStack_20,0x9a14d331);
            uVar4 = *puVar8;
            iVar7 = 0;
            if (0 < iVar3) {
              piVar9 = *(int **)(iVar2 + 0x74);
              goto LAB_009957c0;
            }
            break;
          }
          iVar7 = iVar7 + 1;
          piVar9 = piVar9 + 4;
        } while (iVar7 < iVar3);
      }
      goto LAB_00995833;
    }
LAB_0099584a:
    *(int *)(thisPtr + 0x94) = entityCount;
  }
  return;
  
  while( true ) {
    iVar7 = iVar7 + 1;
    piVar9 = piVar9 + 4;
    if (iVar3 <= iVar7) break;
LAB_009957c0:
    if (*piVar9 == 0x34133103) {  // Hash for another property type
      // Store entity index and property value in list
      *(int *)(iVar10 + 4 + *(int *)(thisPtr + 0x90)) = iVar11;
      *(undefined4 *)(iVar10 + *(int *)(thisPtr + 0x90)) = uVar4;
      local_28 = 0;
      puVar8 = (undefined4 *)FUN_004af8c0(auStack_18,0x34133103);
      (**(code **)(*local_24 + 0x98))(&local_28,*puVar8);
      entityCount = entityCount + 1;
      *(uint *)(iVar10 + 8 + *(int *)(thisPtr + 0x90)) = local_28 >> 2;
      iVar10 = iVar10 + 0xc;
      break;
    }
  }
LAB_00995833:
  iVar11 = iVar11 + 1;
  if (*(int *)(*(int *)(thisPtr + 0x20) + 0xc) <= iVar11) goto LAB_0099584a;
  goto LAB_0099576d;
}