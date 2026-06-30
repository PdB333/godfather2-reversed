// FUNC_NAME: BaseObject::~BaseObject
void BaseObject::~BaseObject(void)
{
  // Calls the base class destructor at 0x004d2810 (EA::BaseObject::~BaseObject)
  // This function is a simple wrapper that chains to the parent destructor.
  // In C++ derived destructor pattern: derived destructor calls base destructor.
  FUN_004d2810();
  return;
}