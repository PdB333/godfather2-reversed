// FUNC_NAME: BaseVehicle::destructor
void __fastcall BaseVehicle::destructor(undefined4 *this)

{
  *this = &PTR_FUN_00d73c50;
  this[1] = &PTR_LAB_00d73c54;
  this[0x10] = &PTR_LAB_00d73c40;
  this[0x13] = &PTR_LAB_00d73c3c;
  if (this[0x36] != 0) { // +0xD8 - vehicle physics pointer
    FUN_004df590(); // VehiclePhysics::release
    FUN_004df600(); // VehiclePhysics::release
  }
  if (this[0x37] != 0) { // +0xDC - vehicle sound pointer
    FUN_004df590(); // VehicleSound::release
    FUN_004df600(); // VehicleSound::release
  }
  FUN_004086d0(this + 0x15); // +0x54 - some list/timer destructor
  FUN_004086d0(this + 0x17); // +0x5C
  FUN_004086d0(this + 0x19); // +0x64
  FUN_004086d0(this + 0x1b); // +0x6C
  FUN_004086d0(this + 0x1d); // +0x74
  FUN_004086d0(this + 0x1f); // +0x7C
  FUN_00408310(this + 0x15); // +0x54 - some list/timer cleanup
  FUN_00408310(this + 0x17); // +0x5C
  FUN_00408310(this + 0x19); // +0x64
  FUN_00408310(this + 0x1b); // +0x6C
  FUN_00408310(this + 0x1d); // +0x74
  FUN_00408310(this + 0x1f); // +0x7C
  FUN_004086d0(&DAT_0112a5cc); // global audio data manager destructor
  FUN_004086d0(&DAT_0112a618); // global audio data manager destructor
  FUN_004086d0(&DAT_012069c4); // global stream manager destructor
  FUN_00408310(&DAT_0112dbe0); // global bullet manager cleanup
  FUN_00408310(&DAT_0112dbd0); // global physics debug cleanup
  FUN_00408310(&DAT_0112dbd8); // global audio debug cleanup
  FUN_00408310(&DAT_0112dbc4); // global object cleanup
  if (this[0x37] != 0) { // +0xDC - vehicle sound pointer
    *(undefined4 *)(this[0x37] + 8) = 0; // clear sound reference
    this[0x37] = 0;
  }
  if (this[0x36] != 0) { // +0xD8 - vehicle physics pointer
    *(undefined4 *)(this[0x36] + 8) = 0; // clear physics reference
    this[0x36] = 0;
  }
  FUN_0046c640(); // VehicleManager::unregisterVehicle
  *this = &PTR_LAB_00d73c38; // base class vtable
  DAT_0112aff4 = 0; // global vehicle count decrement
  return;
}