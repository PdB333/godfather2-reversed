// FUNC_NAME: GOGameObject::GOGameObject
undefined4 __thiscall GOGameObject::GOGameObject(GOGameObject* this, byte flags)
{
  // Call base class constructor (presumably at offset 0 from this)
  GOGameObject::BaseConstructor(this);  // FUN_006aace0

  // If the lowest bit of flags is set, initialize a sub-object at offset 0x3CC
  if ((flags & 1) != 0) {
    // Construct a member of type? at offset 0x3CC within this object
    // FUN_0043b960 is likely a placement constructor or an initializer function
    GOGameObject::initSubObject(this + 0x3CC);  // FUN_0043b960(this, 0x3CC)
  }

  return (undefined4)this;
}