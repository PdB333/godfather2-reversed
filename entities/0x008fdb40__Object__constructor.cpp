// FUNC_NAME: Object::constructor
undefined4 * __thiscall Object::constructor(Object *this, char *name, int id)
{
  // Zero out first 8 fields (32 bytes)
  this->field0 = 0;
  this->field1 = 0;
  this->field2 = 0;
  this->field3 = 0;
  this->field4 = 0;
  this->field5 = 0;
  this->field6 = 0;
  this->field7 = 0;

  // Set type field (offset +0x20) to 2
  this->type = 2; // +0x20: type identifier

  // Set id field (offset +0x24) to the provided id
  this->id = id; // +0x24: object ID

  // Use default name if none provided
  if (name == (char *)0x0) {
    name = &DAT_00e2f044; // default name string
  }

  // Store the name (or copy it) into the object
  setName(name);

  return this;
}