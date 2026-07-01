// FUNC_NAME: TNLHashMap::insertOrFind
void __thiscall TNLHashMap::insertOrFind(undefined4 *this, undefined4 *outKey, int *key)
{
  int *piVar1;
  longlong lVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  
  iVar7 = this[1]; // +0x04: currentDepth
  piVar6 = (int *)*this; // +0x00: rootNode
  do {
    if (iVar7 < 0) {
      piVar6 = *(int **)piVar6[2]; // +0x08: next pointer
      if ((piVar6 == (int *)0x0) || (*piVar6 != *key)) {
        uVar3 = FUN_00963cd0(); // getHashBits
        uVar5 = this[1]; // currentDepth
        if (uVar5 < uVar3) {
          while (uVar5 = uVar5 + 1, uVar5 <= uVar3) {
            *(undefined4 *)(this[5] + uVar5 * 4) = *this; // +0x14: pathStack
          }
          this[1] = uVar3; // update depth
        }
        piVar4 = (int *)FUN_009c8e50(0xc); // allocateNode (12 bytes)
        piVar6 = (int *)0x0;
        if (piVar4 != (int *)0x0) {
          lVar2 = (ulonglong)(uVar3 + 1) * 4;
          iVar7 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar2 >> 0x20) != 0) | (uint)lVar2); // allocateKeyArray
          piVar4[2] = iVar7; // +0x08: keyArray
          piVar6 = piVar4;
        }
        *piVar6 = *key; // store key
        uVar5 = 0;
        do {
          *(undefined4 *)(piVar6[2] + uVar5 * 4) =
               *(undefined4 *)(*(int *)(*(int *)(this[5] + uVar5 * 4) + 8) + uVar5 * 4); // copy path
          *(int **)(*(int *)(*(int *)(this[5] + uVar5 * 4) + 8) + uVar5 * 4) = piVar6; // link back
          uVar5 = uVar5 + 1;
        } while (uVar5 <= uVar3);
        this[4] = this[4] + 1; // +0x10: nodeCount
      }
      *outKey = piVar6;
      return;
    }
    piVar4 = (int *)(piVar6[2] + iVar7 * 4); // get child pointer at current depth
    if (*(int *)(piVar6[2] + iVar7 * 4) != 0) {
      do {
        piVar1 = (int *)*piVar4;
        if (*key <= *piVar1) break;
        piVar4 = (int *)(piVar1[2] + iVar7 * 4);
        piVar6 = piVar1;
      } while (*(int *)(piVar1[2] + iVar7 * 4) != 0);
    }
    iVar7 = iVar7 + -1;
    *(int **)(this[5] + 4 + iVar7 * 4) = piVar6; // store path
  } while( true );
}