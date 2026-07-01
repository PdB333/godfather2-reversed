// FUNC_NAME: GenericContainer::removeItemByType
void __thiscall GenericContainer::removeItemByType(int this, int itemType)
{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  
  iVar7 = 0;
  if (*(int *)(this + 8) < 1) { // +0x8: itemCount / slot count
    return;
  }
  do {
    iVar1 = *(int *)(*(int *)(this + 0xc) + iVar7 * 4); // +0xC: slotArray (pointer to array of slot pointers)
    piVar8 = (int *)**(undefined4 **)(iVar1 + 0x18);   // +0x18: itemList (linked list head node pointer)
    while( true ) {
      iVar6 = *(int *)(*(int *)(this + 0xc) + iVar7 * 4);
      piVar2 = *(int **)(iVar6 + 0x18);                  // +0x18: itemList pointer
      if (iVar1 != iVar6) {
        FUN_00b97aea(); // assertion / debug break
      }
      if (piVar8 == piVar2) break; // wrapped around to head, no more items
      if (piVar8 == *(int **)(iVar1 + 0x18)) {
        FUN_00b97aea(); // assertion
      }
      if (piVar8[4] == 0) {       // +0x10: item data pointer (null means no item)
        iVar6 = 0;
      }
      else {
        iVar6 = piVar8[4] + -0x48; // dereference item data and subtract header size to get type
      }
      if (iVar6 == itemType) {
        puVar3 = *(undefined4 **)(*(int *)(this + 0xc) + iVar7 * 4);
        if (piVar8 == *(int **)(iVar1 + 0x18)) {
          FUN_00b97aea(); // assertion
        }
        if (piVar8 == (int *)puVar3[6]) { // puVar3[6] = +0x18? actually slot+0x18 is head
          return; // already removed
        }
        // Remove node from doubly-linked list
        *(int *)piVar8[1] = *piVar8;       // piVar8[0]=prev, piVar8[1]=next
        *(int *)(*piVar8 + 4) = piVar8[1];
        if (piVar8[4] != 0) {              // piVar8[4] = item data pointer
          FUN_004daf90(piVar8 + 4);        // destruct item data (likely calling operator delete)
        }
        piVar8[2] = (int)&PTR_FUN_00e32808; // vtable placeholder for freed node
        puVar5 = (undefined4 *)piVar8[3];  // piVar8[3] = child list head
        while (puVar5 != (undefined4 *)0x0) { // clear child list
          puVar4 = (undefined4 *)puVar5[1];
          puVar5[1] = 0;
          *puVar5 = 0;
          puVar5 = puVar4;
        }
        (**(code **)(*(int *)*puVar3 + 4))(piVar8, 0x2c); // call vtable destructor (size 0x2c)
        puVar3[7] = puVar3[7] + -1; // decrement item count at slot+0x1C
        return;
      }
      if (piVar8 == *(int **)(iVar1 + 0x18)) {
        FUN_00b97aea(); // assertion
      }
      piVar8 = (int *)*piVar8; // advance to next node in linked list
    }
    iVar7 = iVar7 + 1;
    if (*(int *)(this + 8) <= iVar7) {
      return;
    }
  } while( true );
}