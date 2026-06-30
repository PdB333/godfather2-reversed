// FUNC_NAME: SoundManager::setupAudioGraph
undefined4 SoundManager::setupAudioGraph(SoundManager* thisPtr)

{
  int iVar1;
  undefined4 *in_EAX;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int local_30;
  undefined4 local_28 [2];
  undefined4 local_20 [2];
  undefined4 local_18 [2];
  undefined4 local_10;
  undefined4 local_8;
  
  iVar1 = thisPtr;
  uVar2 = FUN_004dafd0(" TIMESTRETCHED_CHANNELS"); // Get hash for "TIMESTRETCHED_CHANNELS"
  *in_EAX = uVar2;
  FUN_004d3d90(" TIMESTRETCHED_CHANNELS"); // Find audio graph node
  puVar3 = in_EAX + 0x10;
  iVar4 = 5;
  do {
    *puVar3 = *in_EAX;
    puVar3 = puVar3 + 0xc;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  piVar5 = in_EAX + 10;
  local_30 = 5;
  do {
    if ((((piVar5[-5] == 0) && // Check if channel slot is empty
         (*(int *)(iVar1 + 0x580) != 0)) && // Audio engine handle
        (*(int *)(iVar1 + 0x56c) != 0)) && // Some state
       (piVar5[2] == 0x10)) { // Channel type == 16
      FUN_00c9eac0(); // Begin audio graph setup
      // Setup audio graph nodes for this channel
      // SndPlayer node
      FUN_005e9ba0("SndPlayer");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x536e5031); // 'SnP1'
      puVar3 = local_20;
      *(undefined4 *)(thisPtr + 4) = uVar2;
      uVar2 = FUN_00c9cd50(0x536e5031);
      FUN_00c9cba0(*(undefined4 *)(iVar1 + 0x580),uVar2,puVar3);
      local_20[0] = DAT_00e2dd14;
      *(undefined4 **)(*piVar5 + -0xc + piVar5[1] * 0xc) = local_20;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // Rechannel node
      FUN_005e9ba0("Rechannel");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x52636830); // 'Rch0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // Resample node
      FUN_005e9ba0("Resample");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x52737030); // 'Rsp0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // Timestretch node
      FUN_005e9ba0("Timestretch");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x54537430); // 'TSt0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // GeneralPurposeLowpass node
      FUN_005e9ba0("GeneralPurposeLowpass");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x4c493230); // 'LI20'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // AuxSend1 node
      FUN_005e9ba0("AuxSend1");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x53656e30); // 'Sen0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // AuxSend2 node
      FUN_005e9ba0("AuxSend2");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x53656e30); // 'Sen0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // AuxSend3 node
      FUN_005e9ba0("AuxSend3");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x53656e30); // 'Sen0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // SendToMaster node (with Pan2 parameters)
      FUN_005e9ba0(&DAT_00e3f8e4); // "SendToMaster"
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x506e3231); // 'Pn21'
      puVar3 = local_18;
      *(undefined4 *)(thisPtr + 4) = uVar2;
      uVar2 = FUN_00c9cd50(0x506e3231);
      FUN_00c9cba0(*(undefined4 *)(iVar1 + 0x580),uVar2,puVar3);
      local_8 = 0;
      local_18[0] = DAT_0110ae38;
      local_10 = DAT_00e44720;
      *(undefined4 **)(*piVar5 + -0xc + piVar5[1] * 0xc) = local_18;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // SendToMaster node
      FUN_005e9ba0("SendToMaster");
      thisPtr = *piVar5 + -0xc + piVar5[1] * 0xc;
      uVar2 = FUN_00c9cd50(0x53656e30); // 'Sen0'
      *(undefined4 *)(thisPtr + 4) = uVar2;
      *(undefined4 *)(*piVar5 + -0xc + piVar5[1] * 0xc) = 0;
      *(undefined1 *)(*piVar5 + -4 + piVar5[1] * 0xc) = 6;
      
      // Commit the audio graph
      iVar4 = FUN_00ca55a0(*(undefined4 *)(iVar1 + 0x580),0,piVar5[1],*piVar5,0);
      piVar5[-5] = iVar4;
      piVar5[-4] = iVar4 + 0x50;
      if ((iVar4 != 0) && (iVar4 + 0x50 != 0)) {
        // Connect AuxSend1 to reverb bus
        puVar3 = &thisPtr;
        thisPtr = 0;
        uVar2 = FUN_004dafd0("AuxSend1",puVar3);
        iVar4 = FUN_005e9d90(uVar2,puVar3);
        if (((iVar4 != 0) &&
            ((*(int *)(thisPtr + 0x28) == 0x53656e30 && (*(int **)(iVar1 + 0x39c) != (int *)0x0))))
           && (**(int **)(iVar1 + 0x39c) != 0)) {
          FUN_00c9cbe0(*(undefined4 *)(iVar1 + 0x580),*(undefined4 *)(iVar4 + 0x10),0,local_28);
          local_28[0] = **(undefined4 **)(iVar1 + 0x39c);
          FUN_00c9cd40(0,local_28);
        }
        // Connect AuxSend2 to reverb bus
        puVar3 = &thisPtr;
        uVar2 = FUN_004dafd0("AuxSend2",puVar3);
        iVar4 = FUN_005e9d90(uVar2,puVar3);
        if ((((iVar4 != 0) && (*(int *)(thisPtr + 0x28) == 0x53656e30)) &&
            (*(int **)(iVar1 + 0x3cc) != (int *)0x0)) && (**(int **)(iVar1 + 0x3cc) != 0)) {
          FUN_00c9cbe0(*(undefined4 *)(iVar1 + 0x580),*(undefined4 *)(iVar4 + 0x10),0,local_28);
          local_28[0] = **(undefined4 **)(iVar1 + 0x3cc);
          FUN_00c9cd40(0,local_28);
        }
        // Connect AuxSend3 to reverb bus
        puVar3 = &thisPtr;
        uVar2 = FUN_004dafd0("AuxSend3",puVar3);
        iVar4 = FUN_005e9d90(uVar2,puVar3);
        if (((iVar4 != 0) && (*(int *)(thisPtr + 0x28) == 0x53656e30)) &&
           ((*(int **)(iVar1 + 0x3fc) != (int *)0x0 && (**(int **)(iVar1 + 0x3fc) != 0)))) {
          FUN_00c9cbe0(*(undefined4 *)(iVar1 + 0x580),*(undefined4 *)(iVar4 + 0x10),0,local_28);
          local_28[0] = **(undefined4 **)(iVar1 + 0x3fc);
          FUN_00c9cd40(0,local_28);
        }
        // Connect SendToMaster to master bus
        puVar3 = &thisPtr;
        uVar2 = FUN_004dafd0("SendToMaster",puVar3);
        iVar4 = FUN_005e9d90(uVar2,puVar3);
        if ((iVar4 != 0) && (*(int *)(thisPtr + 0x28) == 0x53656e30)) {
          FUN_00c9cbe0(*(undefined4 *)(iVar1 + 0x580),*(undefined4 *)(iVar4 + 0x10),0,local_28);
          local_28[0] = **(undefined4 **)(iVar1 + 0x42c);
          FUN_00c9cd40(0,local_28);
        }
      }
      FUN_00c9eae0(); // End audio graph setup
    }
    piVar5 = piVar5 + 0xc;
    local_30 = local_30 + -1;
  } while (local_30 != 0);
  return 1;
}