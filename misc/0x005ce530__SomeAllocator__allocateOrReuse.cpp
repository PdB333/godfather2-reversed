// FUNC_NAME: SomeAllocator::allocateOrReuse
int * SomeAllocator::allocateOrReuse(int *param_1)

{
  int *piVar1;
  undefined4 *in_EAX;
  int *piVar2;
  
  piVar2 = (int *)FUN_005cec70(in_EAX,param_1); // Try to find existing slot
  if (piVar2 == (int *)0x0) {
    in_EAX[1] = *in_EAX; // Copy some value to next slot
    piVar2 = (int *)FUN_005d0c30(); // Allocate new block
    in_EAX[0xc] = in_EAX[0xc] + 1; // Increment count at +0x30
    piVar1 = (int *)*piVar2; // Get current head
    if (piVar1 != param_1) {
      *piVar2 = (int)param_1; // Set new head
      if (param_1 != (int *)0x0) {
        (**(code **)*param_1)(); // Call virtual function on param_1
      }
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 4))(); // Call virtual function on old head
      }
    }
    piVar2[4] = 0; // +0x10: reset field
    piVar2[5] = 0; // +0x14: reset field
    piVar2[6] = 0; // +0x18: reset field
    piVar2[1] = 1; // +0x04: set to 1
    piVar2[2] = 1; // +0x08: set to 1
    piVar2[3] = 1; // +0x0C: set to 1
  }
  return piVar2;
}