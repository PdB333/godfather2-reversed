// FUNC_NAME: TNLConnectionConfig::setDefaults
void __thiscall TNLConnectionConfig::setDefaults(TNLConnectionConfig* this)
{
  // offset +0x00: initialRetryCount = 4
  this->initialRetryCount = 4;
  // offset +0x04: baseSendSequence = 0xFFFFFFFF (invalid)
  this->baseSendSequence = 0xFFFFFFFF;
  // offset +0x08: baseRecvSequence = 0
  this->baseRecvSequence = 0;
  // offset +0x0C: ackMask = 0
  this->ackMask = 0;
  // offset +0x10: lastAcked = 0
  this->lastAcked = 0;
  // offset +0x14: sequenceOne = 0xFFFFFFFF
  this->sequenceOne = 0xFFFFFFFF;
  // offset +0x18: sequenceTwo = 0
  this->sequenceTwo = 0;
  // offset +0x1C: sequenceThree = 0xFFFFFFFF
  this->sequenceThree = 0xFFFFFFFF;
  // offset +0x20: sequenceFour = 0
  this->sequenceFour = 0;
  // offset +0x24: sequenceFive = 0
  this->sequenceFive = 0;
  // offset +0x28: sequenceSix = 0
  this->sequenceSix = 0;
  // offset +0x2C: windowSize = 32
  this->windowSize = 32;
  // offset +0x30 to +0x4C: zero (unused or padding)
  this->field_0x30 = 0;
  this->field_0x34 = 0;
  this->field_0x38 = 0;
  this->field_0x3C = 0;
  this->field_0x40 = 0;
  this->field_0x44 = 0;
  this->field_0x48 = 0;
  this->field_0x4C = 0;
}