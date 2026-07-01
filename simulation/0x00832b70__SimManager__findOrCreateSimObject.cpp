// FUNC_NAME: SimManager::findOrCreateSimObject
undefined4 __thiscall SimManager::findOrCreateSimObject(int *this, undefined4 id, int *guid, int owner)
{
  int iVar1;
  bool bCreatedNew;
  int iVar2;
  int iVar3;
  int iVar4;
  char result;
  int *newObj;
  undefined4 *allocator;
  undefined4 allocStack0;
  undefined4 allocStack4;
  int *allocStack8;
  
  // Check if this ID is valid/allowed (virtual function at vtable+0x14)
  result = (**(code **)(*this + 0x14))(id);
  if (result == '\0') {
    return 0;
  }
  
  bCreatedNew = true;
  newObj = (int *)SimObject::findByGuid(guid);  // try to find existing object
  if (newObj == (int *)0x0) {
    bCreatedNew = false;
    // Allocate new object (size 0x70 bytes)
    allocator = (undefined4 *)getMemoryManager();  // returns memory manager singleton
    allocStack0 = 2;
    allocStack4 = 0x10;
    allocStack8 = newObj;  // placeholder
    newObj = (int *)(**(code **)*allocator)(0x70, &allocStack0);
    if (newObj == (int *)0x0) {
      return 0;
    }
    // Call constructor (likely initializes vtable and fields)
    SimObject::SimObject();
    
    // Copy static data (some global values) into object
    iVar1 = _DAT_00d5780c;
    newObj[0x13] = _DAT_00d5780c;   // +0x4C
    newObj[0x14] = iVar1;              // +0x50
    *newObj = (int)&PTR_LAB_00d736c0;  // set vtable pointer to SimObject vtable
    
    newObj[0x15] = 0;                  // +0x54
    
    // Copy more static data (maybe version / flags)
    iVar4 = _UNK_00d735fc;
    iVar3 = _UNK_00d735f8;
    iVar1 = _UNK_00d735f4;
    newObj[0x18] = _DAT_00d735f0;      // +0x60
    newObj[0x19] = iVar1;              // +0x64
    newObj[0x1a] = iVar3;              // +0x68
    newObj[0x1b] = iVar4;              // +0x6C
  }
  
  // Copy GUID data (4 integers) into object
  newObj[7] = *guid;          // +0x1C
  newObj[8] = guid[1];        // +0x20
  newObj[9] = guid[2];        // +0x24
  newObj[10] = guid[3];       // +0x28
  
  // If this has some additional data (index 2), copy it
  iVar1 = this[2];
  if (iVar1 != 0) {
    newObj[0xf] = *(int *)(iVar1 + 0x24);   // +0x3C
    newObj[0x10] = *(int *)(iVar1 + 0x28);   // +0x40
    newObj[0x11] = *(int *)(iVar1 + 0x2c);   // +0x44
    newObj[0x12] = *(int *)(iVar1 + 0x30);   // +0x48
  }
  
  // If an owner is specified, call virtual function at offset 4 (setOwner)
  if (owner != 0) {
    (**(code **)(*newObj + 4))(owner);
  }
  
  // If newly created, register it with the manager
  if (!bCreatedNew) {
    SimObject::registerSimObject(newObj);
  }
  
  return 1;
}