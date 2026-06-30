// FUNC_NAME: DebugCommandHandler::processDebugCommands
void DebugCommandHandler::processDebugCommands(void)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  uint *puVar6;
  
  uVar2 = DAT_01205684; // g_debugCommandCount
  cVar1 = DAT_01205656; // g_debugCommandActive
  if (0 < DAT_012056bc) { // g_debugCommandQueueSize
    if (DAT_01205656 == '\0') { // g_debugCommandActive == false
      puVar6 = (uint *)(DAT_01206880 + 0x14); // g_debugCommandBuffer + 0x14
      **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08; // push command
      *puVar6 = *puVar6 + 4;
      *(undefined1 *)*puVar6 = 0;
      *puVar6 = *puVar6 + 4 & 0xfffffffc;
    }
    else if (1 < DAT_01205684) { // g_debugCommandCount > 1
      FUN_005d5880(DAT_0119da54,0xc0); // debugOutput(g_debugString, 0xc0)
      FUN_005d56f0(); // flushDebugOutput()
      DAT_00f1765c = 0xfffffffe; // g_debugState = -2
    }
    iVar3 = DAT_01206880; // g_debugCommandBuffer
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40; // push command
    *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + 4;
    **(undefined1 **)(iVar3 + 0x14) = 1;
    *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) + 4 & 0xfffffffc;
    uVar4 = DAT_0122221c; // g_debugCommandParam
    piVar5 = (int *)(DAT_01206880 + 0x14); // g_debugCommandBuffer + 0x14
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126eec; // push command
    *piVar5 = *piVar5 + 4;
    *(undefined4 *)*piVar5 = uVar4;
    *piVar5 = *piVar5 + 4;
    FUN_005d5d40(); // executeDebugCommand()
    DAT_012056bc = 0; // g_debugCommandQueueSize = 0
    if ((cVar1 == '\0') && (1 < uVar2)) { // if command was inactive and count > 1
      puVar6 = (uint *)(DAT_01206880 + 0x14); // g_debugCommandBuffer + 0x14
      **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08; // push command
      *puVar6 = *puVar6 + 4;
      *(undefined1 *)*puVar6 = 1;
      *puVar6 = *puVar6 + 4 & 0xfffffffc;
    }
    puVar6 = (uint *)(DAT_01206880 + 0x14); // g_debugCommandBuffer + 0x14
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40; // push command
    *puVar6 = *puVar6 + 4;
    *(undefined1 *)*puVar6 = 0;
    *puVar6 = *puVar6 + 4 & 0xfffffffc;
  }
  return;
}