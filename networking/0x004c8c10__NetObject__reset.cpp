// FUNC_NAME: NetObject::reset
void NetObject::reset(void)
{
  // Starting at this pointer (in EAX)
  // Struct layout: (offsets in bytes)
  // +0x00: m_field0 (int32)
  // +0x04: m_field1 (int32)
  // +0x08: padding or unused? (8 bytes, not zeroed here)
  // +0x10: m_data[0] (int64)  (first of 17 64-bit fields)
  // +0x18: m_data[1]
  // ...
  // +0x90: m_data[16] (last)

  this->field0 = 0;           // *in_EAX = 0
  this->field1 = 0;           // in_EAX[1] = 0

  // Zero the 64-bit array starting at offset 0x10
  this->data[0] = 0LL;       // *(undefined8 *)(in_EAX + 4) = 0
  this->data[1] = 0LL;       // *(undefined8 *)(in_EAX + 6) = 0
  this->data[2] = 0LL;       // *(undefined8 *)(in_EAX + 8) = 0
  this->data[3] = 0LL;       // *(undefined8 *)(in_EAX + 0xa) = 0
  this->data[4] = 0LL;       // *(undefined8 *)(in_EAX + 0xc) = 0
  this->data[5] = 0LL;       // *(undefined8 *)(in_EAX + 0xe) = 0
  this->data[6] = 0LL;       // *(undefined8 *)(in_EAX + 0x10) = 0
  this->data[7] = 0LL;       // *(undefined8 *)(in_EAX + 0x12) = 0
  this->data[8] = 0LL;       // *(undefined8 *)(in_EAX + 0x14) = 0
  this->data[9] = 0LL;       // *(undefined8 *)(in_EAX + 0x16) = 0
  this->data[10] = 0LL;      // *(undefined8 *)(in_EAX + 0x18) = 0
  this->data[11] = 0LL;      // *(undefined8 *)(in_EAX + 0x1a) = 0
  this->data[12] = 0LL;      // *(undefined8 *)(in_EAX + 0x1c) = 0
  this->data[13] = 0LL;      // *(undefined8 *)(in_EAX + 0x1e) = 0
  this->data[14] = 0LL;      // *(undefined8 *)(in_EAX + 0x20) = 0
  this->data[15] = 0LL;      // *(undefined8 *)(in_EAX + 0x22) = 0
  this->data[16] = 0LL;      // *(undefined8 *)(in_EAX + 0x24) = 0
  // Note: Last store at offset 0x2a (0x2a*4 = 168 bytes) writes 8 bytes, total size 176 bytes.
}