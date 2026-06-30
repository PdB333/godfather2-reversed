// FUNC_NAME: BinaryHeap::push
void BinaryHeap::push(void)
{
  float fVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  undefined8 *in_EAX;
  undefined8 *puVar6;
  int iVar7;
  float *pfVar8;
  int *unaff_ESI;
  
  iVar7 = unaff_ESI[2]; // heap capacity
  if (unaff_ESI[1] == iVar7) { // heap size == capacity -> grow
    if (iVar7 == 0) {
      iVar7 = 1;
    }
    else {
      iVar7 = iVar7 * 2;
    }
    FUN_005fc8f0(iVar7); // reallocate/resize heap array
  }
  puVar6 = (undefined8 *)(unaff_ESI[1] * 0x10 + *unaff_ESI); // pointer to new element slot (size 0x10 = 16 bytes per element)
  unaff_ESI[1] = unaff_ESI[1] + 1; // increment heap size
  if (puVar6 != (undefined8 *)0x0) {
    *puVar6 = *in_EAX; // copy first 8 bytes of new element
    puVar6[1] = in_EAX[1]; // copy second 8 bytes
  }
  iVar7 = unaff_ESI[1] + -2; // index of parent of last element (heap size -2)
  iVar4 = unaff_ESI[1] + -1; // index of last element
  while( true ) {
    iVar5 = iVar7 / 2; // parent index
    if (iVar5 < 0) {
      return;
    }
    iVar7 = *unaff_ESI; // heap array base
    fVar1 = *(float *)(iVar7 + iVar5 * 0x10); // parent's key (float at offset 0)
    pfVar8 = (float *)(iVar4 * 0x10 + iVar7); // child's key
    puVar6 = (undefined8 *)(iVar7 + iVar5 * 0x10); // parent element pointer
    if (fVar1 < *pfVar8 || fVar1 == *pfVar8) break; // heap property satisfied (parent <= child)
    // swap parent and child
    uVar2 = *(undefined8 *)pfVar8;
    uVar3 = *(undefined8 *)(pfVar8 + 2);
    *(undefined8 *)pfVar8 = *puVar6;
    *(undefined8 *)(pfVar8 + 2) = puVar6[1];
    iVar7 = iVar5 + -1; // move up the tree
    *puVar6 = uVar2;
    puVar6[1] = uVar3;
    iVar4 = iVar5;
  }
  return;
}