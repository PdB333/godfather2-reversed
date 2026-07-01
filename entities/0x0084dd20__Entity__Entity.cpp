// FUNC_NAME: Entity::Entity
Entity * __thiscall Entity::Entity(Entity *this)
{
  int *pPtr1;
  int *pPtr2;

  this->vtable = (EntityVTable *)&PTR_FUN_00d6a7a8; // set vtable
  pPtr1 = &this->field_0x04; // pointer at +0x04
  *pPtr1 = 0;                // clear pointer
  this->field_0x08 = 0;
  pPtr2 = &this->field_0x0C; // pointer at +0x0C
  *pPtr2 = 0;
  this->field_0x10 = 0;
  this->flags = 0;           // field at offset 0x44? Actually +0x44 set later, but here set to 0
  // Note: the decompiled shows param_1[0x11] = 0; but then later sets bit 0. Possibly flags at +0x44.
  if (*pPtr1 != 0) {
    FUN_004daf90(pPtr1);   // free? (likely operator delete)
    *pPtr1 = 0;
  }
  if (*pPtr2 != 0) {
    FUN_004daf90(pPtr2);
    *pPtr2 = 0;
  }
  // +0x14 to +0x2C fields cleared
  this->field_0x14 = 0;
  this->field_0x18 = 0;
  this->field_0x1C = 0;
  this->field_0x20 = 0; // param_1[8]
  this->field_0x24 = 0; // param_1[9]
  this->field_0x28 = 0; // param_1[10]
  this->field_0x30 = 0; // param_1[0xc]
  this->field_0x34 = 0; // param_1[0xd]
  this->field_0x38 = 0; // param_1[0xe]
  this->field_0x3C = 0; // param_1[0xf]
  this->field_0x40 = 0; // param_1[0x10]
  this->field_0x2C = 0; // param_1[0xb]
  this->flags = this->flags | 1; // set bit 0 at +0x44 (param_1[0x11])
  return this;
}