// FUNC_NAME: Transform::assignFrom
void __thiscall Transform::assignFrom(Transform* this, const Transform* other)
{
  // Set vtable pointer (base class initialization)
  this->vtable = &VTable_Transform; // PTR_LAB_00e35c24

  // Copy quaternion (4 floats at offsets 0x04,0x08,0x0C,0x10)
  this->quat.x = other->quat.x;
  this->quat.y = other->quat.y;
  this->quat.z = other->quat.z;
  this->quat.w = other->quat.w;

  // Copy translation vector (3 floats at offsets 0x14,0x18,0x1C)
  this->pos.x = other->pos.x;
  this->pos.y = other->pos.y;
  this->pos.z = other->pos.z;
}