// FUNC_NAME: TNL::Packet::clear
void __thiscall TNL::Packet::clear(TNL::Packet *this)
{
  // Zero out the 8 dword fields of the packet header/body (32 bytes)
  this->field_0 = 0;   // +0x00
  this->field_4 = 0;   // +0x04
  this->field_8 = 0;   // +0x08
  this->field_C = 0;   // +0x0C
  this->field_10 = 0;  // +0x10
  this->field_14 = 0;  // +0x14
  this->field_1C = 0;  // +0x1C (assigned before field_18)
  this->field_18 = 0;  // +0x18
}