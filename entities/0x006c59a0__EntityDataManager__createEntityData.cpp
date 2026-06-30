// FUNC_NAME: EntityDataManager::createEntityData
undefined4 __fastcall EntityDataManager::createEntityData(int this)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_c; // size: 0x310 bytes
  undefined4 local_8; // alignment?
  undefined4 local_4; // flags?
  
  puVar1 = (undefined4 *)EntityDataManager::getSingleton();
  local_c = 2;  // entity type? 
  local_8 = 0x10; // size alignment?
  local_4 = 0;   // flags: none?
  iVar2 = (**(code **)*puVar1)(0x310, &local_c); // allocate 0x310 bytes for new entity data
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = EntityDataManager::initEntityData(this);
  }
  // +0x90 likely entity state/type field: 0 = uninitialized, 0x48 = some specific type
  if ((*(int *)(this + 0x90) == 0) || (*(int *)(this + 0x90) == 0x48)) {
    uVar4 = EntityDataManager::getDataArray(this + 0x58, 0); // +0x58: data array
    EntityDataManager::setDataValue(uVar4, 0x38523fc3, &stack0xffffffe8); // set some property
  }
  EntityDataManager::initDataList(this + 0x68); // +0x68: linked list of data chunks
  return uVar3;
}