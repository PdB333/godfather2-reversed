// FUNC_NAME: BaseObject::constructorWithFlags
undefined4 __thiscall BaseObject::constructorWithFlags(byte flags)
{
  // Call the base class constructor (0x006a9080)
  baseClassConstructor();
  
  // If the lowest bit of 'flags' is set, perform additional initialization/cleanup
  // This is a common pattern in EARS object construction where a flag indicates
  // whether to allocate or finalize memory (e.g., placement new vs normal new)
  if ((flags & 1) != 0) {
    finalizeOrDeallocate(this); // 0x009c8eb0 – likely destructor or memory release
  }
  
  return this; // Always return the constructed object
}