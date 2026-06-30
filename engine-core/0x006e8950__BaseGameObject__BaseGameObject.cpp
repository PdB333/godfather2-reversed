// FUNC_NAME: BaseGameObject::BaseGameObject
BaseGameObject * __fastcall BaseGameObject::BaseGameObject(BaseGameObject *this)
{
  float fVar1;
  float fVar2;
  double dVar3;

  dVar3 = DAT_00d5fb70;
  this->field_4 = 0;
  this->field_8 = 0;
  this->field_C = 0;
  this->vtable = &PTR_FUN_00d5faf8; // +0x00 vtable
  this->guard1 = 0xbadbadba;        // +0x10 debug guard
  this->guard2 = 0xbeefbeef;        // +0x14 debug guard
  this->guard3 = 0xeac15a55;        // +0x18 debug guard
  this->guard4 = 0x91100911;        // +0x1C debug guard
  this->field_60 = 0;               // +0x60
  this->field_64 = 0;               // +0x64
  *(byte *)((int)this + 0x8b) = 0; // +0x8b flag byte
  *(byte *)((int)this + 0x8a) = 2; // +0x8a flags (initial 2)
  FUN_00b99e20();                   // random seed or time?
  this->float1 = (float)dVar3;     // +0x50 (from global double)
  dVar3 = DAT_00d5f010;
  FUN_00b99e20();
  fVar1 = DAT_00d58cbc;
  this->float2 = (float)dVar3;     // +0x54
  this->int1 = DAT_00d5ddec;       // +0x58
  this->int2 = DAT_00d5fb6c;       // +0x5C
  this->field_68 = 0;              // +0x68
  this->field_70 = 0;              // +0x70
  this->field_6C = fVar1;          // +0x6C (same as +0x48)
  this->field_74 = 0;              // +0x74
  this->field_7C = 0;              // +0x7C
  this->field_78 = fVar1;          // +0x78 (same as +0x6C)
  this->field_44 = 0;              // +0x44
  this->field_4C = 0;              // +0x4C
  fVar2 = DAT_00d5ccf8;
  this->field_48 = fVar1;          // +0x48
  *(byte *)((int)this + 0x8a) = *(byte *)((int)this + 0x8a) | 8; // +0x8a flags OR 8
  *(byte *)((int)this + 0x89) = 0; // +0x89 flag
  this->field_80 = 0;              // +0x80
  *(byte *)((int)this + 0x88) = 1; // +0x88 byte flag
  this->field_84 = fVar2;          // +0x84
  return this;
}