// FUNC_NAME: EARSObject::EARSObject

undefined4 __thiscall EARSObject::EARSObject(undefined4 thisPointer, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  EARSObject::baseConstructor(thisPointer);
  
  // If the low bit of 'flags' is set, call an additional initializer
  // This might indicate a temporary or dynamically allocated object requiring extra setup
  if ((flags & 1) != 0) {
    EARSObject::extraInit(thisPointer);
  }
  
  return thisPointer;
}