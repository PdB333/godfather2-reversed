// FUNC_NAME: EARSObject::setTransform
void EARSObject::setTransform(int *this, undefined4 transform)
{
  (**(code **)(*this + 0x48))(transform); // vtable call: setTransformInternal (likely updates world matrix)
  FUN_008b8cf0(this, transform); // update bounding volume / spatial hash
  return;
}