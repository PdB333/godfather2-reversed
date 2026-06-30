// FUNC_NAME: DebugLogManager::dumpDebugStats
void DebugLogManager::dumpDebugStats(void)
{
  int iVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  int local_205c;
  undefined1 *local_2058;
  undefined4 local_2054;
  undefined4 local_2050;
  code *local_204c;
  int local_2048;
  undefined4 local_2044;
  undefined4 local_2040;
  code *local_203c;
  int iStack_2038;
  undefined4 uStack_2034;
  undefined4 uStack_2030;
  code *pcStack_202c;
  undefined1 local_2028 [4116];
  undefined1 auStack_1014 [4112];
  undefined4 uStack_4;
  
  uStack_4 = 0x6944aa;
  // only if something is pending and not yet dumped
  if ((g_numStats != 0) && (g_statsDumped == 0)) {
    local_2058 = (undefined1 *)0x0;
    local_2054 = 0;
    local_2050 = 0;
    local_204c = (code *)0x0;
    // Write header: two formatted lines with hashed strings
    printfHash(g_logStream, &local_2058, "{#%u}\n\n{#%u}\n\n", 0x76cd4f26, 0x76cd4f27);
    iVar4 = 0;
    local_205c = 0;
    do {
      puVar3 = &g_statArray; // array of 5-int entries
      do {
        iVar1 = puVar3[-1]; // type field (at offset -4 from current? Actually -1 int)
        if (iVar1 == local_205c) {
          if (iVar1 == 0) {
            uVar5 = 0xcb339725; // hash for "type0"?
          }
          else {
            if (iVar1 != 1) goto LAB_006945c2;
            uVar5 = 0xfde88b79; // hash for "type1"?
          }
          local_2048 = 0;
          local_2044 = 0;
          local_2040 = 0;
          local_203c = (code *)0x0;
          beginLogEntry(); // FUN_00604be0
          puVar2 = (undefined1 *)*puVar3; // string pointer from entry
          if (puVar2 == (undefined1 *)0x0) {
            puVar2 = &emptyString;
          }
          writeLogField(0x65, puVar2); // FUN_00604c10(0x65,...)
          iVar4 = iVar4 + 1;
          writeLogInt(0x6e, iVar4); // FUN_00604c80(0x6e,count)
          printfHash(g_logStream, local_2028, &local_2048, "{#%u}\n", uVar5);
          printFormatted(local_2048, 0, local_2044); // FUN_004d43f0
          endLogEntry(); // FUN_00604c00
          if (local_2048 != 0) {
            (*local_203c)(local_2048);
          }
        }
LAB_006945c2:
        if ((iVar4 == 4) || (iVar4 == g_numStats)) goto LAB_006945f7;
        puVar3 = puVar3 + 5; // next entry (5 ints per entry)
      } while ((int)puVar3 < (int)&DAT_01129d84); // end of stat array
    } while ((iVar4 != g_numStats) && (local_205c = local_205c + 1, local_205c < 2));
LAB_006945f7:
// After loop, write footer line with count and total
    iStack_2038 = 0;
    uStack_2034 = 0;
    uStack_2030 = 0;
    pcStack_202c = (code *)0x0;
    beginLogEntry();
    writeLogInt(100, iVar4); // total items processed
    writeLogInt(0x65, g_numStats); // expected total
    printfHash(g_logStream, auStack_1014, &iStack_2038, "\n{#%u}", 0xe4c9f9d9);
    printFormatted(iStack_2038, 0, uStack_2034);
    // Allocate some structure (size 0xf0)
    iVar4 = allocatorAlloc(0xf0); // FUN_009c8e50(0xf0)
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = allocatorGetObject(0); // FUN_00982280(0)
    }
    puVar2 = local_2058;
    if (local_2058 == (undefined1 *)0x0) {
      puVar2 = &emptyString;
    }
    setAllocatorName(puVar2); // FUN_00981eb0(puVar2)
    *(undefined4 *)(iVar4 + 0xc) = 7; // Set some flag
    finalizeAllocator(); // FUN_00982e10()
    g_numStats = 0;
    g_statsDumped = 1;
    endLogEntry();
    if (iStack_2038 != 0) {
      (*pcStack_202c)(iStack_2038);
    }
    if (local_2058 != (undefined1 *)0x0) {
      (*local_204c)(local_2058);
    }
  }
  return;
}