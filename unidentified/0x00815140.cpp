// FUN_NAME: EARSObject::EARSObject
undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte constructFlag)
{
  EARSObject::initializeBase(); // FUN_00814fa0 - base class initialization
  if ((constructFlag & 1) != 0) {
    EARSObject::postConstruct(this); // FUN_009c8eb0 - additional construction step (e.g., register with manager)
  }
  return this;
}