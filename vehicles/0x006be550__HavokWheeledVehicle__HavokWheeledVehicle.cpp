// FUNC_NAME: HavokWheeledVehicle::HavokWheeledVehicle
undefined4 * __thiscall HavokWheeledVehicle::HavokWheeledVehicle(void *this, undefined4 baseObject)
{
  // Call base class constructor (probably WheeledVehicle or BaseVehicle)
  FUN_0046c590(baseObject);

  // Initialize member variables
  this->m_flags = 0;                               // +0x50 (param_1[0x14])
  this->vtable = &g_vtable_HavokWheeledVehicle;    // +0x00
  this->m_suspensionTable = &g_suspensionData;     // +0x3c (param_1[0xf])
  this->m_steeringTable = &g_steeringData;         // +0x48 (param_1[0x12])
  this->m_someFlags2 = 0;                          // +0x58 (param_1[0x16])
  *(short *)((char *)this + 0x5c) = 0;             // +0x5c
  *(short *)((char *)this + 0x5e) = 0;             // +0x5e
  this->m_field_0x60 = 0;                          // +0x60 (param_1[0x18])
  *(short *)((char *)this + 0x64) = 0;             // +0x64
  *(short *)((char *)this + 0x66) = 0;             // +0x66
  this->m_field_0x68 = 0;                          // +0x68 (param_1[0x1a])
  *(short *)((char *)this + 0x6c) = 0;             // +0x6c
  *(short *)((char *)this + 0x6e) = 0;             // +0x6e
  return (undefined4 *)this;
}