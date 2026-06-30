// FUNC_NAME: SoundListener::updateListenerPriority
void __fastcall SoundListener::updateListenerPriority(SoundListener *this)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 *local_24;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14;
  
  piVar4 = (int *)((int)this + 0x524); // +0x524: current listener index
  iVar3 = 0;
  if (*(int *)((int)this + 0x524) == 0) {
    local_30 = 0;
  }
  else {
    local_30 = *(int *)((int)this + 0x524) + -0x48; // offset to listener data
  }
  local_28 = 0;
  local_24 = (undefined4 *)0x0;
  local_2c = 0;
  if ((*(int *)((int)this + 0x694) == 0) || (*(int *)((int)this + 0x694) == 0x48)) {
    // No override listener, or override is invalid
    if (*piVar4 != 0) {
      FUN_004daf90(piVar4); // remove current listener
      *piVar4 = 0;
    }
    piVar4 = (int *)((int)this + 0x24); // +0x24: array of potential listeners (32 slots, each 0x50 bytes)
    iVar2 = 0;
    piVar1 = piVar4;
    do {
      if (*(int *)((int)this + 0x520) <= iVar2) break; // +0x520: count of listeners
      if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
        // Calculate distance squared from listener position (at +0x14, +0x18, +0x1c)
        fVar7 = (float)piVar1[4] - *(float *)((int)this + 0x1c);
        fVar6 = (float)piVar1[3] - *(float *)((int)this + 0x18);
        fVar5 = (float)piVar1[2] - *(float *)((int)this + 0x14);
        piVar1[6] = (int)((fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5) * (float)piVar1[5]); // weighted distance
        iVar2 = iVar2 + 1;
      }
      // Repeat for next 7 entries in the 0x50 byte block (each entry is 0x10 bytes? or 8 ints?)
      // ... (the pattern repeats for indices 10, 14, 1e, 28, 32, 3c, 46)
      // Each block has 8 potential listener entries
      iVar3 = iVar3 + 8;
      piVar1 = piVar1 + 0x50; // 0x50 = 80 bytes per block
    } while (iVar3 < 0x20); // 32 blocks total
    
    local_34 = 0x20;
    fVar5 = DAT_00e4474c; // some max distance threshold
    do {
      if (((*piVar4 != 0) && (*piVar4 != 0x48)) && (fVar6 = (float)piVar4[6], fVar6 < fVar5)) {
        // Found a closer listener
        if ((int *)((int)this + 0x524) != piVar4) {
          iVar3 = *piVar4;
          if (*(int *)((int)this + 0x524) != iVar3) {
            if (*(int *)((int)this + 0x524) != 0) {
              FUN_004daf90((int)this + 0x524); // remove old listener
            }
            *(int *)((int)this + 0x524) = iVar3; // set new listener
            if (iVar3 != 0) {
              *(undefined4 *)((int)this + 0x528) = *(undefined4 *)(iVar3 + 4); // +0x528: next listener in linked list
              *(int *)(iVar3 + 4) = (int)this + 0x524; // update linked list
            }
          }
        }
        local_24 = (undefined4 *)piVar4[7]; // +0x1c: some data
        local_28 = piVar4[8]; // +0x20: some data
        local_2c = piVar4[-1]; // -4: previous entry?
        fVar5 = fVar6; // update min distance
      }
      piVar4 = piVar4 + 10; // 10 ints = 40 bytes per entry? or 0x28?
      local_34 = local_34 + -1;
    } while (local_34 != 0);
  }
  else if (piVar4 != (int *)((int)this + 0x694)) {
    // Override listener exists
    iVar3 = *(int *)((int)this + 0x694);
    if (*piVar4 != iVar3) {
      if (*piVar4 != 0) {
        FUN_004daf90(piVar4); // remove current
      }
      *piVar4 = iVar3; // set override
      if (iVar3 != 0) {
        *(undefined4 *)((int)this + 0x528) = *(undefined4 *)(iVar3 + 4);
        *(int **)(iVar3 + 4) = piVar4;
      }
    }
  }
  if (*(int *)((int)this + 0x524) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)((int)this + 0x524) + -0x48;
  }
  if (local_30 != iVar3) {
    // Listener changed
    if (local_30 != 0) {
      FUN_006a40b0(0); // deactivate old listener
    }
    if ((*(int *)((int)this + 0x524) != 0) && (*(int *)((int)this + 0x524) != 0x48)) {
      FUN_006a40b0(1); // activate new listener
    }
  }
  if (local_2c != *(int *)((int)this + 0x534)) {
    // Some other state changed
    if (*(undefined4 **)((int)this + 0x530) != (undefined4 *)0x0) {
      local_1c = **(undefined4 **)((int)this + 0x530);
      local_18 = 0;
      local_14 = 0;
      FUN_00408a00(&local_1c,0); // release old resource
    }
    *(int *)((int)this + 0x530) = local_28; // +0x530: some resource pointer
    *(undefined4 **)((int)this + 0x52c) = local_24; // +0x52c: some data pointer
    if (local_24 != (undefined4 *)0x0) {
      local_1c = *local_24;
      local_18 = 0;
      local_14 = 0;
      FUN_00408a00(&local_1c,0); // acquire new resource
    }
    *(int *)((int)this + 0x534) = local_2c; // +0x534: some state
  }
  return;
}