// FUNC_NAME: NetSession::constructor
undefined4 * __thiscall NetSession::NetSession(NetSession *this)
{
  undefined4 *vtableBase2;
  
  vtableBase2 = (undefined4 *)((char *)this + 4);
  g_pNetSession = this;
  *vtableBase2 = &PTR_FUN_00e2f19c;
  this->field_08 = 1;
  this->field_0C = 0;
  *(undefined4 *)this = &PTR_FUN_00d74dd8;
  *vtableBase2 = &PTR_LAB_00d74dc8;
  this->field_10 = 0;
  this->field_1C = 0;
  allocateNetworkBuffer(0x20,1);
  this->field_20 = 0;
  this->field_24 = 0;
  this->field_28 = 0;
  this->field_2C = 0;
  this->field_30 = 0;
  this->field_34 = 0;
  this->field_38 = 0;
  this->field_3C = 0;
  this->field_40 = 0;
  this->field_44 = 0;
  this->field_48 = 0;
  this->field_4C = 0;
  this->field_50 = 0;
  this->field_54 = 0;
  this->field_58 = 0;
  this->field_18 = 0;
  this->field_14 = 0;
  if (g_pInitializationData != 0) {
    memcpyLarge(vtableBase2,g_pInitializationData,0x8000);
  }
  return this;
}