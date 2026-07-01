//FUNC_NAME: Marker::constructor
undefined4 * __thiscall Marker::constructor(Marker *this, uint id, undefined4 param3, float *position, float *rotation, uint flags, undefined4 param7, float radius, float param9, undefined4 param10, char *name)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  
  this->field_0x04 = param3;
  this->field_0x118 = 0;
  this->id = id;
  this->flags = flags;
  this->field_0x120 = 0;
  this->field_0x124 = param9 * param9;
  this->field_0x154 = 0;
  this->field_0x158 = 0;
  this->field_0x15c = 0;
  this->field_0x160 = 0;
  this->field_0x164 = 0;
  this->field_0x168 = 0;
  this->field_0x16c = 0;
  this->field_0x170 = 0;
  FUN_005c0a30();
  uVar1 = _DAT_00d5780c;
  this->field_0x190 = 0;
  this->field_0x194 = 0;
  this->field_0x198 = 0;
  this->field_0x19c = 0;
  this->field_0x1a0 = 0;
  this->field_0x1a4 = 0;
  this->field_0x1a8 = 0;
  this->field_0x1ac = 0;
  this->field_0x1b0 = 0;
  this->field_0x1b4 = 0;
  this->field_0x1b8 = 0;
  this->field_0x1bc = 0;
  this->field_0x1c0 = 0;
  this->field_0x1c4 = 0;
  this->field_0x1c8 = 0;
  this->field_0x1cc = 0;
  this->field_0x1d0 = 0;
  this->field_0x1d4 = 0;
  this->field_0x1d8 = uVar1;
  uVar1 = DAT_00d5ccf8;
  this->field_0x1dc = 1;
  this->field_0x1dd = 0;
  this->field_0x1e0 = 0;
  this->field_0x1e4 = uVar1;
  this->field_0x1e8 = uVar1;
  this->field_0x200 = 0;
  this->field_0x1fc = 0;
  this->field_0x1f8 = 0;
  this->field_0x1f4 = 0;
  this->field_0x1f0 = 0;
  this->field_0x210 = 0;
  this->field_0x214 = 0;
  this->field_0x218 = 0;
  this->field_0x21c = 0;
  if ((name != (char *)0x0) && (*name != '\0')) {
    FUN_004d3d90(name);
  }
  __snprintf((char *)(this->name), 0x10, "%s%u", PTR_s_marker__00e56a54, id);
  this->field_0x18 = 0;
  uVar1 = position[1];
  uVar2 = position[2];
  uVar3 = position[3];
  this->position.x = *position;
  this->position.y = uVar1;
  this->position.z = uVar2;
  this->position.w = uVar3;
  if (rotation == (float *)0x0) {
    this->rotation.x = 0;
    this->rotation.y = 0;
    this->rotation.z = 0;
    this->rotation.w = 0;
  }
  else {
    uVar1 = rotation[1];
    uVar2 = rotation[2];
    uVar3 = rotation[3];
    this->rotation.x = *rotation;
    this->rotation.y = uVar1;
    this->rotation.z = uVar2;
    this->rotation.w = uVar3;
  }
  FUN_0094b290(param7);
  FUN_00948b20(param10);
  if ((float)this->field_0x120 != radius) {
    this->field_0x120 = radius;
    this->flags = this->flags | 0x200000;
  }
  if (((uint)this->flags >> 7 & 1) == 0) {
    cVar4 = FUN_0094b9b0();
    if (cVar4 == '\0') {
      this->flags = this->flags | 0x40000;
    }
  }
  this->field_0x153 = 0;
  this->field_0x152 = 0;
  this->field_0x151 = 0;
  this->field_0x150 = 0;
  return this;
}