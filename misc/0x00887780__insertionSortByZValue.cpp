// FUNC_NAME: insertionSortByZValue
void insertionSortByZValue(uint *param_1, uint *param_2)
{
  float fVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  
  if (param_1 != param_2) {
    do {
      uVar2 = *param_1;
      fVar1 = *(float *)(uVar2 + 0xc); // +0x0C: z value (float) from object
      puVar4 = param_1;
      puVar5 = param_1;
      while( true ) {
        puVar5 = puVar5 + -1;
        uVar3 = *puVar5;
        if ((fVar1 <= *(float *)(uVar3 + 0xc)) && // Compare z values
           ((fVar1 < *(float *)(uVar3 + 0xc) || (uVar2 <= uVar3)))) break; // Stable sort: use pointer comparison for ties
        *puVar4 = uVar3;
        puVar4 = puVar4 + -1;
      }
      param_1 = param_1 + 1;
      *puVar4 = uVar2;
    } while (param_1 != param_2);
  }
  return;
}