// FUNC_NAME: EARS::Framework::Vector<0x2c>::insert
int __thiscall EARSFrameworkVector2c_insert(int *this, uint index)
{
  undefined8 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = this[2];
  if (this[1] == iVar3) {
    if (iVar3 == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = iVar3 * 2;
    }
    FUN_008d7370(iVar3); // grow capacity
  }
  uVar2 = this[1];
  if (index != uVar2) {
    // Shift elements right from index to make room
    puVar1 = (undefined8 *)(uVar2 * 0x2c + *this);
    if (puVar1 != (undefined8 *)0x0) {
      *puVar1 = *(undefined8 *)((int)puVar1 + -0x2c);
      puVar1[1] = *(undefined8 *)((int)puVar1 + -0x24);
      puVar1[2] = *(undefined8 *)((int)puVar1 + -0x1c);
      puVar1[3] = *(undefined8 *)((int)puVar1 + -0x14);
      puVar1[4] = *(undefined8 *)((int)puVar1 + -0xc);
      *(undefined4 *)(puVar1 + 5) = *(undefined4 *)((int)puVar1 + -4);
    }
    uVar2 = this[1] - 1;
    if (index < uVar2) {
      iVar4 = uVar2 * 0x2c;
      iVar3 = uVar2 - index;
      do {
        puVar1 = (undefined8 *)(*this + iVar4);
        *puVar1 = *(undefined8 *)(*this + -0x2c + iVar4);
        puVar1[1] = *(undefined8 *)((int)puVar1 + -0x24);
        puVar1[2] = *(undefined8 *)((int)puVar1 + -0x1c);
        puVar1[3] = *(undefined8 *)((int)puVar1 + -0x14);
        puVar1[4] = *(undefined8 *)((int)puVar1 + -0xc);
        iVar4 = iVar4 + -0x2c;
        iVar3 = iVar3 + -1;
        *(undefined4 *)(puVar1 + 5) = *(undefined4 *)((int)puVar1 + -4);
      } while (iVar3 != 0);
    }
    this[1] = this[1] + 1;
    if (*this + index * 0x2c != 0) {
      iVar3 = 2;
      do {
        FUN_008d5df0(); // default construct element
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    return *this + index * 0x2c;
  }
  // Append at end
  if (uVar2 * 0x2c + *this != 0) {
    FUN_008d7340(); // default construct element
  }
  iVar3 = this[1];
  this[1] = iVar3 + 1;
  return iVar3 * 0x2c + *this;
}