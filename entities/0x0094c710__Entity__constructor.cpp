// FUNC_NAME: Entity::constructor
undefined4 * __thiscall Entity::constructor(undefined4 *this, undefined4 id, undefined4 type, int parent, int flags, undefined4 *position, undefined4 rotation, undefined4 scale, float radius, float height, undefined4 modelData)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  
  *this = id;
  this[1] = type;
  this[0x47] = rotation;
  this[0x48] = 0;
  this[0x49] = height * height;
  this[0x55] = 0;
  this[0x56] = 0;
  if (parent == 0) {
    parent = 0;
  }
  else {
    parent = parent + 0x48;
  }
  this[0x57] = parent;
  this[0x58] = 0;
  if (parent != 0) {
    this[0x58] = *(undefined4 *)(parent + 4);
    *(undefined4 **)(parent + 4) = this + 0x57;
  }
  this[0x5a] = 0;
  this[0x5b] = 0;
  this[0x5c] = 0;
  FUN_005c0a30(); // likely some engine initialization
  uVar1 = _DAT_00d5780c;
  this[100] = 0;
  this[0x65] = 0;
  this[0x66] = 0;
  this[0x67] = 0;
  this[0x68] = 0;
  this[0x69] = 0;
  this[0x6a] = 0;
  this[0x6b] = 0;
  this[0x6c] = 0;
  this[0x6d] = 0;
  this[0x6e] = 0;
  this[0x6f] = 0;
  this[0x70] = 0;
  this[0x71] = 0;
  this[0x72] = 0;
  this[0x73] = 0;
  this[0x74] = 0;
  this[0x75] = 0;
  this[0x76] = uVar1;
  uVar1 = DAT_00d5ccf8;
  *(undefined1 *)(this + 0x77) = 1;
  *(undefined1 *)((int)this + 0x1dd) = 0;
  this[0x78] = 0;
  this[0x79] = uVar1;
  this[0x7a] = uVar1;
  FUN_00949110(flags); // likely setFlags or similar
  this[0x84] = 0;
  this[0x85] = 0;
  this[0x86] = 0;
  this[0x87] = 0;
  if (flags == 0) {
    this[0x46] = 4; // entity type enum: 4 = something
  }
  else {
    this[0x46] = 5; // entity type enum: 5 = something else
    this[0x47] = this[0x47] | 0x20000000;
    if (((uint)this[0x47] >> 1 & 1) != 0) {
      radius = (float)this[0x80];
    }
  }
  __snprintf((char *)(this + 2),0x10,"%s%u",PTR_s_marker__00e56a54,id);
  *(undefined1 *)(this + 6) = 0;
  this[0x4f] = 0;
  this[0x4e] = 0;
  this[0x4d] = 0;
  this[0x4c] = 0;
  if (position == (undefined4 *)0x0) {
    this[0x53] = 0;
    this[0x52] = 0;
    this[0x51] = 0;
    this[0x50] = 0;
  }
  else {
    uVar1 = position[1];
    uVar2 = position[2];
    uVar3 = position[3];
    this[0x50] = *position;
    this[0x51] = uVar1;
    this[0x52] = uVar2;
    this[0x53] = uVar3;
  }
  FUN_0094b290(scale); // likely setScale
  FUN_00948b20(modelData); // likely setModelData
  if ((float)this[0x48] != radius) {
    this[0x48] = radius;
    this[0x47] = this[0x47] | 0x200000;
  }
  if (((uint)this[0x47] >> 7 & 1) == 0) {
    cVar4 = FUN_0094b9b0(); // likely some check
    if (cVar4 == '\0') {
      this[0x47] = this[0x47] | 0x40000;
    }
  }
  *(undefined1 *)((int)this + 0x153) = 0;
  *(undefined1 *)((int)this + 0x152) = 0;
  *(undefined1 *)((int)this + 0x151) = 0;
  *(undefined1 *)(this + 0x54) = 0;
  return this;
}