// FUNC_NAME: EntityDataManager::registerNamedDestination
void __thiscall EntityDataManager::registerNamedDestination(int this, short *destinationName, int param_3)

{
  int *piVar1;
  undefined8 *puVar2;
  byte bVar3;
  undefined4 *puVar4;
  uint uVar5;
  char cVar6;
  short *psVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  int *local_2a0 [2];
  undefined1 local_298 [8];
  undefined **local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined1 *local_284;
  undefined4 local_280;
  undefined1 local_27c;
  undefined1 local_278 [4];
  undefined4 *local_274;
  
  piVar11 = (int *)0x0;
  FUN_0064b9e0(0x40,local_298);
  local_284 = local_298;
  local_28c = 0;
  local_288 = 0;
  local_290 = &PTR_LAB_00e42d64;
  local_280 = 8;
  local_27c = 0;
  local_2a0[0] = (int *)0x0;
  if (0 < *(int *)(this + 0x24)) { // +0x24: entity count
    do {
      piVar11 = *(int **)(*(int *)(this + 0x2c) + (int)local_2a0[0] * 4); // +0x2c: entity array pointer
      if (piVar11[0x6d] == 2) { // +0x1b4: entity state == 2 (active?)
        iVar8 = piVar11[100]; // +0x190: some flag
        if ((char)iVar8 == '\0') {
LAB_00656b68:
          cVar6 = FUN_006549b0();
          if (cVar6 == '\0') {
LAB_00656b7f:
            iVar8 = piVar11[0x61]; // +0x184: destination list count
            piVar10 = piVar11 + 0x61; // pointer to destination count
            iVar9 = 0;
            if (0 < iVar8) {
              psVar7 = (short *)piVar11[99]; // +0x18c: destination list pointer, each entry 20 bytes (10 shorts)
              do {
                // Compare 5 int-sized fields (10 shorts total)
                if (((((*destinationName == *psVar7) && (destinationName[1] == psVar7[1])) &&
                     (*(int *)(destinationName + 2) == *(int *)(psVar7 + 2))) &&
                    ((*(int *)(destinationName + 4) == *(int *)(psVar7 + 4) &&
                     (*(int *)(destinationName + 6) == *(int *)(psVar7 + 6))))) &&
                   (*(int *)(destinationName + 8) == *(int *)(psVar7 + 8))) break;
                iVar9 = iVar9 + 1;
                psVar7 = psVar7 + 10;
              } while (iVar9 < iVar8);
            }
            if (iVar9 == iVar8) {
              iVar9 = 0;
              if (0 < iVar8) {
                psVar7 = (short *)piVar11[99];
                do {
                  // Different comparison logic (without field at offset 2? - first short omitted)
                  if ((*destinationName == *psVar7) && (*(int *)(destinationName + 2) == *(int *)(psVar7 + 2))) &&
                     ((*(int *)(destinationName + 4) == *(int *)(psVar7 + 4) &&
                      ((*(int *)(destinationName + 6) == *(int *)(psVar7 + 6) &&
                       (*(int *)(destinationName + 8) == *(int *)(psVar7 + 8))))))) break;
                  iVar9 = iVar9 + 1;
                  psVar7 = psVar7 + 10;
                } while (iVar9 < iVar8);
              }
              if (iVar9 == iVar8) goto LAB_00656c6b;
              if (iVar8 < 5) { // Max 5 destinations per entity
                FUN_00654620(); // allocate destination slot
                *piVar10 = *piVar10 + 1; // increment count
                puVar2 = (undefined8 *)(piVar11[99] + -0x14 + *piVar10 * 0x14); // compute new slot address
                if (puVar2 != (undefined8 *)0x0) {
                  *puVar2 = *(undefined8 *)destinationName; // copy first 8 bytes (4 shorts)
                  puVar2[1] = *(undefined8 *)(destinationName + 4); // copy next 8 bytes
                  *(undefined4 *)(puVar2 + 2) = *(undefined4 *)(destinationName + 8); // copy last 4 bytes
                }
              }
            }
            if ((char)piVar11[100] != '\0') break;
          }
        }
        else {
          cVar6 = FUN_006549b0();
          if (cVar6 == '\0') {
            if ((char)iVar8 == '\0') goto LAB_00656b68;
            goto LAB_00656b7f;
          }
        }
      }
LAB_00656c6b:
      local_2a0[0] = (int *)((int)local_2a0[0] + 1);
    } while ((int)local_2a0[0] < *(int *)(this + 0x24));
  }
  if (local_2a0[0] == *(int **)(this + 0x24)) {
    return;
  }
  FUN_0065a5e0(local_278); // get some timer
  cVar6 = FUN_0064ca10(param_3,local_278); // check timeout
  if (cVar6 == '\0') {
    while (local_274 != (undefined4 *)0x0) {
      puVar4 = (undefined4 *)local_274[2];
      *local_274 = 0;
      local_274[1] = 0;
      local_274[2] = 0;
      local_274 = puVar4;
    }
    goto LAB_00656fa1;
  }
  FUN_0064b9e0(0x40,local_2a0);
  cVar6 = FUN_006549b0(); // check some flag
  if (cVar6 != '\0') {
    while (local_274 != (undefined4 *)0x0) {
      puVar4 = (undefined4 *)local_274[2];
      *local_274 = 0;
      local_274[1] = 0;
      local_274[2] = 0;
      local_274 = puVar4;
    }
    goto LAB_00656fa1;
  }
  uVar5 = *(uint *)(param_3 + 0x18); // stream position index
  if (*(uint *)(param_3 + 0x2c) < uVar5) { // compare against max index
    *(undefined1 *)(param_3 + 0x1c) = 1; // flag: stream finished
  }
  else {
    bVar3 = *(byte *)((uVar5 >> 3) + *(int *)(param_3 + 0xc)); // bitfield check
    *(uint *)(param_3 + 0x18) = uVar5 + 1;
    if ((bVar3 & (byte)(1 << ((byte)uVar5 & 7))) != 0) { // check if bit is set
      cVar6 = FUN_0046d790(); // check something
      if (cVar6 == '\0') {
        // Create a target position object (24 bytes)
        iVar8 = FUN_009c8e50(0x24); // allocate memory
        if (iVar8 == 0) {
          iVar8 = 0;
        }
        else {
          iVar8 = FUN_00654840(param_3); // read target position
        }
        // Release old target position
        piVar10 = (int *)piVar11[0x54]; // +0x150: old target position
        if (piVar10 != (int *)0x0) {
          piVar1 = piVar10 + 2;
          *piVar1 = *piVar1 + -1;
          if (*piVar1 == 0) {
            (**(code **)(*piVar10 + 8))(); // release
          }
        }
        piVar11[0x54] = iVar8; // store new target position
        if (iVar8 != 0) {
          *(int *)(iVar8 + 8) = *(int *)(iVar8 + 8) + 1;
        }
        iVar8 = piVar11[0x54];
        if ((*(char *)(iVar8 + 0x20) != '\0') &&
           (cVar6 = (**(code **)(*piVar11 + 0x1c))(iVar8,1), cVar6 != '\0')) goto LAB_00656e8d;
      }
      else {
        // Create a facing direction object (44 bytes)
        iVar8 = FUN_009c8e50(0x2c); // allocate memory
        if (iVar8 == 0) {
          iVar8 = 0;
        }
        else {
          iVar8 = FUN_00654ad0(param_3); // read facing direction
        }
        // Release old facing direction
        piVar10 = (int *)piVar11[0x56]; // +0x158: old facing direction
        if (piVar10 != (int *)0x0) {
          piVar1 = piVar10 + 2;
          *piVar1 = *piVar1 + -1;
          if (*piVar1 == 0) {
            (**(code **)(*piVar10 + 8))(); // release
          }
        }
        piVar11[0x56] = iVar8; // store new facing direction
        if (iVar8 != 0) {
          *(int *)(iVar8 + 8) = *(int *)(iVar8 + 8) + 1;
        }
        if ((*(char *)(piVar11[0x56] + 0x24) != '\0') &&
           (cVar6 = (**(code **)(*piVar11 + 0x18))(piVar11[0x56],1), cVar6 != '\0')) {
          piVar10 = *(int **)(piVar11[0x56] + 0x18); // get some referenced object
          if (piVar10 != (int *)0x0) {
            piVar10[2] = piVar10[2] + 1;
          }
          local_2a0[0] = piVar10;
          FUN_00657960(); // some transform operation
          if (piVar10 != (int *)0x0) {
            piVar1 = piVar10 + 2;
            *piVar1 = *piVar1 + -1;
            if (*piVar1 == 0) {
              (**(code **)(*piVar10 + 8))(); // release
            }
          }
LAB_00656e8d:
          piVar10 = piVar11 + 0x54; // pointer to target position
          if ((*(int *)(this + 0x30) == 0) || // +0x30: some world/level reference
             (*(int *)(*(int *)(this + 0x30) + 0x10) != *(int *)(*piVar10 + 0x10))) {
            iVar8 = FUN_009c8e50(0x24);
            if (iVar8 != 0) {
              FUN_0065e100(*(undefined4 *)(*piVar10 + 0x10)); // copy position
            }
            FUN_00657990(); // set transform
          }
          else {
            FUN_00657960(); // adjust transform
          }
          FUN_0065e570(piVar11[0x55],local_2a0,*piVar10); // send to client
          FUN_006544b0(); // notify listeners
          if ((local_2a0[0] != (int *)0x0) &&
             (local_2a0[0][2] = local_2a0[0][2] + -1, local_2a0[0][2] == 0)) {
            (**(code **)(*local_2a0[0] + 8))(); // release
          }
          FUN_0065bf00((int)piVar11 + 0x162,0x10); // clear some buffer
          *(undefined1 *)((int)piVar11 + 0x131) = 1; // flag: update needed
          goto LAB_00656f38;
        }
      }
      FUN_00656aa0(); // cleanup
      goto LAB_00656fa1;
    }
  }
LAB_00656f38:
  *(undefined8 *)(piVar11 + 0x40) = *(undefined8 *)destinationName; // +0x100: store destination name (first 8 bytes)
  *(undefined8 *)(piVar11 + 0x42) = *(undefined8 *)(destinationName + 4); // +0x108: store next 8 bytes
  piVar11[0x44] = *(int *)(destinationName + 8); // +0x110: store last 4 bytes
  piVar11[0x6d] = 4; // +0x1b4: set entity state to 4 (moving to destination?)
  piVar11[0x67] = 0; // +0x19c: clear some flag
  piVar11[0x68] = *(int *)(this + 100); // +0x190: copy some value from entity data manager
  FUN_00656fc0(this); // schedule next step
  while (local_274 != (undefined4 *)0x0) {
    puVar4 = (undefined4 *)local_274[2];
    *local_274 = 0;
    local_274[1] = 0;
    local_274[2] = 0;
    local_274 = puVar4;
  }
LAB_00656fa1:
  FUN_0064b440();
  return;
}