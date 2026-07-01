// Xbox PDB: AptDisplayList::placeObject
// FUNC_NAME: AptDisplayList::processPlaceObject2
void AptDisplayList::processPlaceObject2(undefined4 *this, uint *placeObject2, int displayList)
{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  undefined4 *puVar4;
  uint *puVar5;
  uint uVar6;
  int unaff_FS_OFFSET;
  char *pCur;
  char *file;
  undefined4 line;
  int assertBehavior;
  undefined1 *assertVar;
  
  puVar5 = placeObject2;
  puVar4 = this;
  if ((*placeObject2 & 2) == 0) {
    if ((*placeObject2 & 1) != 0) {
      // Handle PlaceObject (type 0x01) - find existing character
      FUN_005b1f80(*this, placeObject2[1], 0, &placeObject2, &this);
      if (this == (undefined4 *)0x0) {
        pCur = "pCur";
        file = "..\\source\\Apt\\AptDisplayList.cpp";
        line = 0x20a;
        assertBehavior = 2;
        assertVar = &DAT_0112901a;
        FUN_0059bf00(); // Assertion failure handler
        return;
      }
      FUN_005b2b60(puVar4, this, 0, 0, 0, displayList, 0xffffffff);
    }
    return;
  }
  
  // Handle PlaceObject2 (type 0x02) - character ID validation
  if (((int)placeObject2[2] < 0) ||
     (*(int *)(*(int *)(*(int *)(*(int *)(displayList + 0x58) + 8) + 4) + 0x14) <= (int)placeObject2[2])) {
    // Assertion: character ID out of bounds
    pCur = 
    "pPlaceObject2->nCharacterID >= 0 && pPlaceObject2->nCharacterID < pParent->pData->pCharacter->pParentAnim->animation.nCharacters"
    ;
    file = "..\\source\\Apt\\AptDisplayList.cpp";
    line = 0x1f2;
    assertBehavior = 2;
    assertVar = &DAT_01129018;
    if (DAT_01129018 != '\0') {
      piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
      uVar6 = 1;
      if (((piVar1 == (int *)0x0) ||
          (uVar6 = (**(code **)(*piVar1 + 8))
                             (&pCur,
                              "pPlaceObject2->nCharacterID >= 0 && pPlaceObject2->nCharacterID < pParent->pData->pCharacter->pParentAnim->animation.nCharacters"
                             ), assertVar != (undefined1 *)0x0)) && ((uVar6 & 2) != 0)) {
        *assertVar = 0;
      }
      if (((piVar1 != (int *)0x0) || (assertBehavior != 4)) &&
         (((uVar6 & 1) != 0 || ((assertBehavior == 0 || (assertBehavior == 1)))))) {
        pcVar3 = (code *)swi(3); // Debug break
        (*pcVar3)();
        return;
      }
    }
  }
  
  // Get character data pointer from animation data structure
  // displayList +0x58: parent display list data
  // parent->pData->pCharacter->pParentAnim->animation.characters[nCharacterID]
  iVar2 = *(int *)(*(int *)(*(int *)(*(int *)(*(int *)(displayList + 0x58) + 8) + 4) + 0x18) +
                  puVar5[2] * 4);
  if (iVar2 == 0) {
    pCur = "pCharacter";
    file = "..\\source\\Apt\\AptDisplayList.cpp";
    line = 500;
    assertBehavior = 2;
    assertVar = &DAT_01129019;
    FUN_0059bf00(); // Assertion failure handler
    return;
  }
  
  // Check for flag 0x20 (has matrix transform)
  if ((*puVar5 & 0x20) == 0) {
    uVar6 = 0;
  }
  else {
    uVar6 = puVar5[0xc]; // PlaceObject2 matrix data at offset 0x30 (0xc * 4)
  }
  
  // Process the place object with character data and optional matrix
  FUN_005b2b60(this, 0, puVar5[1], iVar2, uVar6, displayList, puVar5[0xd]); // color transform at offset 0x34
  return;
}