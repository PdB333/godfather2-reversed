// FUNC_NAME: MetaModelInstance::MetaModelInstance
undefined4 * __thiscall MetaModelInstance::MetaModelInstance(MetaModelInstance *this, EARSObject *baseParam, undefined4 param3)
{
  uint index;
  undefined4 assetId;
  int *entryIter;
  
  // Call base class constructor with the two parameters
  EARSObject::Constructor(baseParam, param3);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7c6c8; // vtable for MetaModelInstance
  
  // Default asset ID (7 = unknown/missing asset)
  this->field_0x34 = 7;
  
  index = 0;
  
  // Check if asset database has entries
  if (*(ushort *)(baseParam + 0x20) != 0) {
    // Iterate through asset entry list
    entryIter = *(int **)(baseParam + 0x1c);
    while ( ((undefined4 *)*entryIter)[4] != 0x9DB0F806 ) { // magic type identifier
      index = index + 1;
      entryIter = entryIter + 1;
      if (*(ushort *)(baseParam + 0x20) <= index) {
        // Not found, return with default
        return (undefined4 *)this;
      }
    }
    // Found matching entry, extract asset ID
    assetId = *(undefined4 *)*entryIter;
    this->field_0x34 = assetId;
    
    // Get resource pointer from asset manager using asset ID
    undefined4 resourcePtr = thunk_FUN_0042a990(assetId);
    this->field_0x28 = resourcePtr;
    this->field_0x2c = resourcePtr;
  }
  
  return (undefined4 *)this;
}