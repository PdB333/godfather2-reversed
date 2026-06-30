// FUNC_NAME: SomeClass::calcSomethingOrState
uint __thiscall SomeClass::calcSomethingOrState(int *this)
{
  float vtableFloat1; // from vtable offset 0xC4
  float vtableFloat2; // from vtable offset 0xC0
  float globalFloat; // from global pointer offset 0x204
  uint *globalPtr; // from global DAT_012233a0 + 4
  uint baseVal; // result of global pointer dereference
  uint result;
  bool compResult;
  int baseObject; // derived pointer from field at offset 0x2004
  float someField; // at offset 0x108 from baseObject

  // Get global pointer from (DAT_012233a0 + 4). This is likely a pointer to a global object
  globalPtr = *(uint **)(DAT_012233a0 + 4);
  baseVal = *globalPtr; // uVar2
  result = baseVal; // uVar3
  if (baseVal != 0) {
    // Subtract 0x1F30 as a magic check
    if (baseVal - 0x1F30 != 0) {
      // Read a float at offset 0x204 from the global structure
      globalFloat = *(float *)(baseVal + 0x204);
      // Call two virtual functions (via vtable at *this)
      vtableFloat1 = (*(float (**)(void))(*this + 0xC4))(); // returns float
      vtableFloat2 = (*(float (**)(void))(*this + 0xC0))(); // returns float
      // Check a field at this + 0x2004 (0x801 * 4)
      if (this[0x801] == 0) {
        baseObject = 0;
      } else {
        // Subtract 0x48 from the pointer to get a base object
        baseObject = this[0x801] - 0x48;
      }
      // Read a float at baseObject + 0x108
      someField = *(float *)(baseObject + 0x108);
      // Perform comparison using global float, constant _DAT_00D5780C, and virtual function results
      compResult = (float)(vtableFloat2 / vtableFloat1) <= someField * globalFloat + (_DAT_00d5780c - globalFloat);
    } else {
      compResult = false; // if baseVal == 0x1F30, no further code; result is baseVal (non-zero) but compResult not set? Actually if the outer if is true but inner if (baseVal - 0x1F30 != 0) fails, then the code jumps to return? The decompiled shows that if uVar3 (baseVal - 0x1F30) != 0, it enters the block; else it falls through to return uVar3 & 0xffffff00. So we replicate that.
    }
  }
  // Build return value: low byte is compResult (if block executed), high 24 bits from baseObject shifted right by 8
  if (baseVal != 0 && baseVal - 0x1F30 != 0) {
    return ((uint)baseObject >> 8 & 0xFFFFFF) | (compResult ? 1 : 0);
  }
  // If baseVal == 0 or baseVal == 0x1F30, return baseVal with low byte cleared
  return (uint)(baseVal - 0x1F30) & 0xFFFFFF00; // original: uVar3 & 0xffffff00, where uVar3 = baseVal - 0x1F30
}