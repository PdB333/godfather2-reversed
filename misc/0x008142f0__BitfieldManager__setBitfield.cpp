// FUNC_NAME: BitfieldManager::setBitfield
undefined4 __thiscall BitfieldManager::setBitfield(int this, ushort bitMask, int entityId, char isSet, undefined4 param5)
{
  undefined4 *puVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  ushort uVar8;
  uint uVar9;
  ushort uVar10;
  bool bVar11;
  undefined4 local_c;
  
  uVar3 = *(uint *)(this + 0xc); // +0x0C: count of entries
  uVar9 = 0;
  local_c = 0;
  if (uVar3 != 0) {
    piVar7 = *(int **)(this + 8); // +0x08: pointer to entry array
    do {
      if (*piVar7 == entityId) break;
      uVar9 = uVar9 + 1;
      piVar7 = piVar7 + 2;
    } while (uVar9 < uVar3);
  }
  if (uVar9 == uVar3) {
    iVar5 = *(int *)(this + 0x10); // +0x10: capacity
    if (*(int *)(this + 0xc) == iVar5) {
      if (iVar5 == 0) {
        iVar5 = 1;
      }
      else {
        iVar5 = iVar5 * 2;
      }
      FUN_00814020(iVar5); // resize array
    }
    puVar1 = (undefined4 *)(*(int *)(this + 8) + *(int *)(this + 0xc) * 8);
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0xfe16702f; // magic number for new entry
    }
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
    piVar7 = (int *)(*(int *)(this + 8) + uVar9 * 8);
    *piVar7 = entityId;
    *(undefined2 *)(piVar7 + 1) = 0; // clear bitfield A
    *(undefined2 *)((int)piVar7 + 6) = 0; // clear bitfield B
  }
  uVar4 = *(ushort *)(*(int *)(this + 8) + 4 + uVar9 * 8); // current bitfield A
  iVar5 = *(int *)(this + 8) + uVar9 * 8;
  uVar2 = *(ushort *)(iVar5 + 6); // current bitfield B
  uVar10 = -(uVar4 | uVar2) & (uVar4 | uVar2); // lowest set bit in combined bitfields
  if (isSet == '\0') {
    uVar8 = uVar2 | bitMask;
    bitMask = uVar4 & ~bitMask;
  }
  else {
    uVar8 = uVar2 & ~bitMask;
    bitMask = uVar4 | bitMask;
  }
  if (uVar4 != bitMask || uVar2 != uVar8) {
    uVar4 = -(bitMask | uVar8) & (bitMask | uVar8); // lowest set bit in new combined bitfields
    if ((uVar10 == 0) || (uVar4 <= uVar10)) {
      iVar6 = FUN_00405720(entityId, 0); // check if entity is player
      bVar11 = iVar6 == 0;
      if ((*(ushort *)(iVar5 + 6) & uVar10) != 0) {
        if (bVar11) {
          FUN_00447b50(entityId, param5); // handle player bitfield B change
        }
        else {
          FUN_00406280(entityId, 0); // handle NPC bitfield B change
        }
      }
      if ((*(ushort *)(iVar5 + 4) & uVar10) != 0) {
        if (bVar11) {
          FUN_00447b50(entityId, param5); // handle player bitfield A change
        }
        else {
          FUN_00406280(entityId, 1); // handle NPC bitfield A change
        }
      }
      if ((uVar4 & uVar8) != 0) {
        if (bVar11) {
          FUN_00447ab0(entityId, 0, param5); // handle player bitfield B set
        }
        else {
          FUN_00406230(entityId, 0); // handle NPC bitfield B set
          if ((((char)param5 != '\0') && (iVar6 = FUN_004059b0(entityId), iVar6 != 0)) &&
             (iVar6 = FUN_004025a0(iVar6), iVar6 != 0)) {
            FUN_00404c40(iVar6); // additional processing
          }
        }
      }
      if ((uVar4 & bitMask) != 0) {
        if (bVar11) {
          FUN_00447ab0(entityId, 1, param5); // handle player bitfield A set
        }
        else {
          FUN_00406230(entityId, 1); // handle NPC bitfield A set
          if ((char)param5 != '\0') {
            local_c = FUN_00814120(entityId); // get some value
          }
        }
      }
    }
    *(ushort *)(iVar5 + 4) = bitMask; // update bitfield A
    *(ushort *)(iVar5 + 6) = uVar8; // update bitfield B
  }
  return local_c;
}