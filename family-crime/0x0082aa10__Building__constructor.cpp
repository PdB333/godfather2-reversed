// FUNC_NAME: Building::constructor
void __fastcall Building::constructor(Building *this)

{
  this->vtable = &Building_vtable_00d737d8;
  FUN_0082a9d0(); // BaseVehicle::constructor
  this[0xc] = &LAB_00e32854; // set some member (offset +0x30)
  FUN_00821f60(); // maybe BuildingStore related or EntityDataManager init
  return;
}