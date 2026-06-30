// FUNC_NAME: PacketHeader::initDefaults
void PacketHeader::initDefaults(void)
{
  uint32_t const1 = DAT_00e2eff4; // global constant
  uint32_t const2 = DAT_00e2b1a4; // global constant

  // +0x00: first three dwords same constant
  this->field_00 = const1;   // +0x00
  this->field_04 = const1;   // +0x04
  this->field_08 = const1;   // +0x08
  // +0x0C: next two dwords second constant
  this->field_0C = const2;   // +0x0C
  this->field_10 = const2;   // +0x10
  // +0x14 and +0x18: zeros
  this->field_14 = 0;        // +0x14
  this->field_18 = 0;        // +0x18
  // +0x34: packet timeout / size? (index 0xd)
  this->field_34 = 96000;    // +0x34
  // +0x1C: version or flags?
  this->field_1C = 1;        // +0x1C
  // +0x20..+0x2C: magic numbers
  this->field_20 = 0xBADBADBA; // +0x20
  this->field_24 = 0xBEEFBEEF; // +0x24
  this->field_28 = 0xEAC15A55; // +0x28
  this->field_2C = 0x91100911; // +0x2C
  // +0x30: single byte zero
  this->field_30 = 0;        // +0x30
  return;
}