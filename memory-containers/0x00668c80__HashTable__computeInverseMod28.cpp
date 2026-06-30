// FUNC_NAME: HashTable::computeInverseMod28
int HashTable::computeInverseMod28(uint *outInverse)
{
  uint uVar1 = **(uint **)(this + 0xC); // dereference pointer at this+0xC to get the odd number
  if ((uVar1 & 1) == 0)                // require odd number (inverse exists for odd modulo 2^28)
  {
    return 0xfffffffd;                  // error: invalid input
  }
  // Newton-Raphson approximation of modular inverse modulo 2^28
  uint iVar2 = (uVar1 * 2 + 4 & 8) + uVar1;  // initial guess (1/a*2? ~ approximate)
  iVar2 = (2 - iVar2 * uVar1) * iVar2;       // first iteration: x = x*(2 - a*x)
  iVar2 = (2 - iVar2 * uVar1) * iVar2;       // second iteration
  *outInverse = (uint)(-(int)((2 - iVar2 * uVar1) * iVar2)) & 0xFFFFFFF; // compute final inverse mod 2^28
  return 0;
}