// FUNC_NAME: Player::checkInteractionProximity
void __fastcall Player::checkInteractionProximity(int *thisPlayer)
{
  bool bFoundFrame;
  char cVar2;
  int iVar3;
  int *pEntity;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int local_50;
  float local_4c;
  int local_48;
  int local_44;
  float fStack_40;
  int local_3c;
  int *local_38 [3];
  undefined8 uStack_2c;
  float fStack_24;
  undefined1 auStack_20 [12];
  undefined1 auStack_14 [16];
  
  // Get the entity list manager from this player (+0x3e5 = 997)
  local_44 = thisPlayer[0x3e5];  // Entity manager / object list pointer
  if (local_44 != 0) {
    local_3c = *(int *)(local_44 + 0xc4);  // count of entities
    bFoundFrame = false;
    local_4c = 0.0;
    local_48 = 0;
    if (0 < local_3c) {
      do {
        pEntity = *(int **)(*(int *)(local_44 + 0xc0) + local_48 * 4);  // entity array at +0xc0
        if ((pEntity != (int *)0x0) && (*(char *)((int)pEntity + 0x10) + (int)pEntity != 0)) {
          // Get the player's own component? Tag 0x2001
          FUN_004af8c0(local_38, 0x2001);
          int *pOtherPlayer = (int *)0x0;
          if (local_38[0] != (int *)0x0) {
            pOtherPlayer = local_38[0];
          }
          // Check if valid, not self, and can be interacted with (+0x15e >= 0)
          if (((pOtherPlayer != (int *)0x0) && (pOtherPlayer != thisPlayer)) &&
             (-1 < *(char *)((int)pOtherPlayer + 0x15e))) {
            local_50 = 0;
            // Query if entity has a specific type (unique ID 0x369ac561)
            cVar2 = (**(code **)(*pOtherPlayer + 0x10))(0x369ac561, &local_50);
            if (((cVar2 != '\0') && (local_50 != 0)) && (iVar3 = FUN_007ff880(), iVar3 == 0)) {
              if (!bFoundFrame) {
                // Get some base speed/scalar (vfunc +0x1b0) and compute squared radius
                fVar5 = (float10)(**(code **)(*thisPlayer + 0x1b0))();
                fVar5 = ((float10)DAT_00e540e8 + (float10)DAT_00d58cbc) * fVar5;
                local_4c = (float)(fVar5 * fVar5);
                // Get current position (vfunc +0x4c)
                (**(code **)(*thisPlayer + 0x4c))(auStack_14);
                iVar3 = FUN_00471610();  // Get some global time or frame data
                uStack_2c = *(undefined8 *)(iVar3 + 0x30);
                fStack_24 = *(float *)(iVar3 + 0x38);
                bFoundFrame = true;
              }
              // Get new position for this frame
              iVar3 = FUN_00471610();
              fVar6 = (float)uStack_2c - *(float *)(iVar3 + 0x30);
              fVar7 = uStack_2c._4_4_ - *(float *)(iVar3 + 0x34);
              fVar8 = fStack_24 - *(float *)(iVar3 + 0x38);
              // Check if player has moved less than threshold (i.e., standing still)
              if (fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6 <= local_4c) {
                // Get other entity's position
                (**(code **)(*pOtherPlayer + 0x4c))(auStack_20);
                // Check line-of-sight / distance to interact
                cVar2 = FUN_0084c940(&uStack_2c, iVar3 + 0x30, auStack_14, auStack_20,
                                     DAT_00d5ef70, DAT_00d72dac, &fStack_40);
                if ((cVar2 != '\0') && (fStack_40 < DAT_00e540e8)) {
                  // Trigger interaction
                  FUN_0072fdb0(thisPlayer);
                }
              }
            }
          }
        }
        local_48 = local_48 + 1;
      } while (local_48 < local_3c);
    }
  }
  return;
}