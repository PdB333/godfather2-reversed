// FUNC_NAME: GameRelationManager::findObjectByRelationChain
undefined4 __thiscall GameRelationManager::findObjectByRelationChain(int this, int targetId)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  
  // Offset 0x94: count of ID mappings (structures of 3 ints each)
  uint idMappingCount = *(uint *)(this + 0x94);
  uVar2 = 0;
  if (idMappingCount != 0) {
    // Offset 0x90: pointer to array of ID mapping entries (3 ints per entry)
    int *idMappingArray = *(int **)(this + 0x90);
    while (*idMappingArray != targetId) {
      uVar2 = uVar2 + 1;
      idMappingArray = idMappingArray + 3;
      if (idMappingCount <= uVar2) {
        return 0;
      }
    }
    // Offset 0x20: pointer to relationship node manager
    int *relManager = *(int **)(this + 0x20);
    // Use second int of mapping (index) to fetch an object from manager's array at +0x08
    int object = *(int *)(*(int *)(relManager + 8) + (*(int **)(this + 0x90))[uVar2 * 3 + 1] * 4);
    if (object != 0) {
      do {
        iVar6 = object;
        object = 0;
        if (0 < *(int *)(relManager + 0x18)) { // Number of relationship link entries
          piVar7 = *(int **)(relManager + 0x14); // Array of pointers to link nodes
          while (*(int *)(*piVar7 + 0x14) != iVar6) { // Link node's child ID != current object
            object = object + 1;
            piVar7 = piVar7 + 1;
            if (*(int *)(relManager + 0x18) <= object) goto LAB_00997b7e;
          }
          object = *(int *)(*piVar7 + 0x18); // Next node in chain (sibling/parent)
          if (object == 0) break;
          iVar8 = *(int *)(object + 0x78); // Number of property entries (hash-constant pairs)
          iVar4 = 0;
          if (iVar8 < 1) break;
          piVar7 = *(int **)(object + 0x74); // Array of 4-int property entries
          piVar9 = piVar7;
          while (*piVar9 != -0x65eb2ccf) { // -0x65EB2CCF = 0x9A14D331, likely a hash constant (e.g., CHILD_RELATION_HASH)
            iVar4 = iVar4 + 1;
            piVar9 = piVar9 + 4;
            if (iVar8 <= iVar4) goto LAB_00997b7e;
          }
          iVar4 = 0;
          piVar9 = piVar7;
          if (0 < iVar8) {
            do {
              if (*piVar9 == -0x65eb2ccf) {
                iVar8 = piVar7[iVar4 * 4 + 2]; // Third element of matching property entry (value associated with hash)
                goto LAB_00997bd8;
              }
              iVar4 = iVar4 + 1;
              piVar9 = piVar9 + 4;
            } while (iVar4 < iVar8);
          }
          iVar8 = 0;
LAB_00997bd8:
          if (iVar8 != targetId) break;
        }
      } while( true );
LAB_00997b7e:
      object = 0;
      if (0 < *(int *)(relManager + 0xc)) { // Number of objects in manager's list
        piVar7 = *(int **)(relManager + 8); // Array of object pointers
        do {
          if (*piVar7 == iVar6) break;
          object = object + 1;
          piVar7 = piVar7 + 1;
        } while (object < *(int *)(relManager + 0xc));
      }
      uVar5 = FUN_00997340(); // Returns some result based on found object index
      return uVar5;
    }
  }
  return 0;
}