// FUNC_NAME: EquippedItemManager::refreshItemStates
undefined4 EquippedItemManager::refreshItemStates()
{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  float *pfVar10;
  int unaff_EDI; // this pointer
  float fVar11;
  int local_4;

  // +0x14: flags field, clear bit 0x20000000 (maybe "needsUpdate" flag)
  *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) & 0xdfffffff;
  bVar5 = false;
  bVar4 = false;
  local_4 = 0;
  if (*(char *)(unaff_EDI + 0x1c) == '\0') { // +0x1c: number of slots, if 0 skip
LAB_0051c699:
    if ((*(byte *)(unaff_EDI + 0x14) & 2) == 0) goto LAB_0051c6a6;
  }
  else {
    // +0x30: array of slot descriptors, each 9 ints (0x24 bytes)
    piVar8 = (int *)(unaff_EDI + 0x30);
    iVar7 = DAT_011946b4; // global count of item templates
    do {
      // piVar9 points to the slot data (first int is an offset relative to this)
      piVar9 = (int *)(*piVar8 + unaff_EDI);
      iVar6 = 0;
      if (iVar7 < 1) {
LAB_0051c5f5:
        *piVar8 = 0; // no matching template, clear slot pointer
      }
      else {
        do {
          piVar1 = (int *)(&DAT_011946b8)[iVar6]; // global array of item templates (each 5 ints?)
          if (piVar1[2] == *piVar9) { // template.itemId == slot.itemId
            if (piVar1 == (int *)0x0) goto LAB_0051c5f5;
            if (piVar1[4] == piVar9[1]) { // template.someProperty == slot.someProperty
              *piVar8 = (int)piVar9; // update slot pointer to the matching template
              *piVar9 = (int)piVar1; // store template pointer into slot
              // call virtual function at +0x14 on (piVar9 + 3) – slot's "activate" method
              (**(code **)(*piVar1 + 0x14))(piVar9 + 3);
              uVar2 = piVar9[2]; // slot flags at offset +8
              if ((piVar8[2] & 0x10U) != 0) { // slot->flags & 0x10
                bVar4 = true;
              }
              if (((uVar2 & 1) != 0) && ((!bVar4 || ((piVar8[2] & 0x20U) == 0)))) {
                bVar5 = true;
              }
              if ((uVar2 & 4) != 0) {
                *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) | 0x40000000; // set bit 30 in flags
              }
              if ((uVar2 & 0x10) != 0) {
                piVar8[2] = piVar8[2] | 0x100; // slot->flags |= 0x100
              }
              iVar7 = DAT_011946b4;
              if ((piVar8[2] & 0x100U) != 0) {
                *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) | 4; // set bit 2 in flags
              }
            }
            else {
              *piVar8 = 0; // property mismatch, clear slot
            }
            goto LAB_0051c66e;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar7);
        *piVar8 = 0;
      }
LAB_0051c66e:
      local_4 = local_4 + 1;
      piVar8 = piVar8 + 9; // advance to next slot
    } while (local_4 < (int)(uint)*(byte *)(unaff_EDI + 0x1c));
    if ((!bVar5) || (0.0 < *(float *)(unaff_EDI + 0x18))) goto LAB_0051c699;
  }
  // Set "needsUpdate" flag (bit 29)
  *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) | 0x20000000;
LAB_0051c6a6:
  iVar7 = 0;
  // +0x28: current cooldown timer, initially set from global default
  *(undefined4 *)(unaff_EDI + 0x28) = DAT_00e2b1a4;
  if (*(char *)(unaff_EDI + 0x1c) != '\0') {
    // +0x48: array of per-slot cooldown floats (each slot has 9 ints, start at +0x48)
    pfVar10 = (float *)(unaff_EDI + 0x48);
    do {
      puVar3 = (undefined4 *)pfVar10[-6]; // slot pointer stored 6 ints before the cooldown (i.e., at start of slot)
      if (puVar3 != (undefined4 *)0x0) {
        fVar11 = *(float *)(unaff_EDI + 0x28); // current minimum
        if (*pfVar10 <= *(float *)(unaff_EDI + 0x28)) { // if this slot's cooldown is smaller
          fVar11 = *pfVar10;
        }
        *(float *)(unaff_EDI + 0x28) = fVar11; // update minimum cooldown
        // Call virtual function at offset 0x2c on the slot's item object
        (**(code **)(*(int *)*puVar3 + 0x2c))();
      }
      iVar7 = iVar7 + 1;
      pfVar10 = pfVar10 + 9; // advance to next slot's cooldown
    } while (iVar7 < (int)(uint)*(byte *)(unaff_EDI + 0x1c));
  }
  return 1;
}