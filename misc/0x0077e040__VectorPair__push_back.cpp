// FUNC_NAME: VectorPair::push_back
void __thiscall VectorPair::push_back(int *this, undefined4 *pair)
{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = this[2]; // +0x08: capacity
  if (this[1] == iVar2) { // +0x04: current size
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2;
    }
    growBuffer(iVar2);
  }
  puVar1 = (undefined4 *)(*this + this[1] * 8); // +0x00: array base + (size * 8)
  this[1] = this[1] + 1; // increment size
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *pair;        // store first 32-bit
    puVar1[1] = pair[1];    // store second 32-bit
  }
  return;
}