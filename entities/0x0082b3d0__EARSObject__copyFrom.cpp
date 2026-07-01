// FUNC_NAME: EARSObject::copyFrom
int __thiscall EARSObject::copyFrom(int this, int other)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (this != other) {
    // Call base copy or cleanup function
    FUN_00820830(other);
    
    // Copy transform/position data (likely a 4x4 matrix or quaternion + translation)
    // +0x60: first component of transform block
    // +0x64: second component (100 decimal)
    // +0x68: third component
    // +0x6c: fourth component
    uVar1 = *(undefined4 *)(other + 100);
    uVar2 = *(undefined4 *)(other + 0x68);
    uVar3 = *(undefined4 *)(other + 0x6c);
    *(undefined4 *)(this + 0x60) = *(undefined4 *)(other + 0x60);
    *(undefined4 *)(this + 100) = uVar1;
    *(undefined4 *)(this + 0x68) = uVar2;
    *(undefined4 *)(this + 0x6c) = uVar3;
    
    // Copy second transform block (likely rotation quaternion)
    // +0x70 to +0x7c: 4 floats for quaternion w,x,y,z
    uVar1 = *(undefined4 *)(other + 0x74);
    uVar2 = *(undefined4 *)(other + 0x78);
    uVar3 = *(undefined4 *)(other + 0x7c);
    *(undefined4 *)(this + 0x70) = *(undefined4 *)(other + 0x70);
    *(undefined4 *)(this + 0x74) = uVar1;
    *(undefined4 *)(this + 0x78) = uVar2;
    *(undefined4 *)(this + 0x7c) = uVar3;
    
    // Copy third block (likely scale or velocity)
    // +0x50 to +0x5c: 4 floats
    uVar1 = *(undefined4 *)(other + 0x54);
    uVar2 = *(undefined4 *)(other + 0x58);
    uVar3 = *(undefined4 *)(other + 0x5c);
    *(undefined4 *)(this + 0x50) = *(undefined4 *)(other + 0x50);
    *(undefined4 *)(this + 0x54) = uVar1;
    *(undefined4 *)(this + 0x58) = uVar2;
    *(undefined4 *)(this + 0x5c) = uVar3;
  }
  return this;
}