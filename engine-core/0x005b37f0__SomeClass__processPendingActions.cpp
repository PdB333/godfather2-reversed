// FUNC_NAME: SomeClass::processPendingActions
void FUN_005b37f0(undefined4 param_1)
{
  uint *puVar1;
  char cVar2;
  undefined4 *in_EAX;
  undefined4 unaff_ESI;
  
  // Iterate through a linked list starting at offset 0x60 from the object pointed by *in_EAX
  // Each node has a next pointer at offset 0x18 (0x18 * 4 = 96 bytes per node)
  for (puVar1 = *(uint **)(*(int *)*in_EAX + 0x60); puVar1 != (uint *)0x0;
      puVar1 = (uint *)puVar1[0x18]) {
    // Check if bit 15 of the first uint is set (mask 0x8000)
    // If bit 15 is 0 (i.e., (~(byte)(*puVar1 >> 0xf) & 1) == 0), then condition holds
    if ((((~(byte)(*puVar1 >> 0xf) & 1) == 0) && (cVar2 = FUN_005a4140(), cVar2 == '\0')) &&
       (*(int *)puVar1[0x16] < 0)) {
      // If all conditions met, call another function with param_1 and unaff_ESI
      FUN_005b5970(param_1,unaff_ESI);
    }
  }
  return;
}