// FUNC_NAME: BuildingStore::BuildingStore
undefined4 * __thiscall BuildingStore::BuildingStore(BuildingStore *this, undefined4 param_2)

{
  // Call base class constructor (likely SimObject or Entity)
  BaseClass::BaseClass(this, param_2);

  // Set virtual function tables / interface pointers
  this->vtable = &PTR_FUN_00d5e3e8;                           // +0x00
  this->vtable_iface1 = &PTR_LAB_00d5e3d8;                   // +0x3C (0x0F * 4)
  this->vtable_iface2 = &PTR_LAB_00d5e3d4;                   // +0x48 (0x12 * 4)
  this->vtable_iface3 = &PTR_LAB_00d5e3d0;                   // +0x50 (0x14 * 4)
  this->vtable_iface4 = &PTR_LAB_00d5e370;                   // +0x54 (0x15 * 4)
  this->vtable_iface5 = &PTR_LAB_00d5e308;                   // +0x58 (0x16 * 4)
  this->vtable_iface6 = &PTR_LAB_00d5e2f0;                   // +0x180 (0x60 * 4)

  this->field_0xa4 = 0;                                      // +0x290

  // If global data pointer is valid, copy 0x8000 bytes into iface1 area
  if (g_buildingStoreData != 0) {
    memcpy(&this->vtable_iface1, g_buildingStoreData, 0x8000); // +0x3C
  }

  // Set a flag on the object (offset 0x18C = 0x63 * 4)
  this->flags |= 0x20000;                                    // +0x18C

  return this;
}