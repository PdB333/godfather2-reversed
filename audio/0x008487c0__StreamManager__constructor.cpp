// FUNC_NAME: StreamManager::constructor
void __thiscall StreamManager::constructor(StreamManager *this)
{
  FUN_00596170();
  // Initialize stream container pointers to null
  // +0x94: last stream pointer
  // +0x90: active stream pointer
  // +0x8c: pending stream pointer
  // +0x88: next stream pointer
  // +0x84: base stream pointer
  this->field_0x94 = 0;  // lastStream
  this->field_0x90 = 0;  // activeStream
  this->field_0x8c = 0;  // pendingStream
  this->field_0x88 = 0;  // nextStream
  this->field_0x84 = 0;  // baseStream
  return;
}