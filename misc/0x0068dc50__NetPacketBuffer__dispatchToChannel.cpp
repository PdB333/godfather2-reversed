// FUNC_NAME: NetPacketBuffer::dispatchToChannel
undefined4 __thiscall NetPacketBuffer::dispatchToChannel(int this, undefined8 *data, undefined4 dataLen, uint channelIndex)
{
  undefined4 result;
  undefined8 buffer[3]; // 24 bytes on stack for intermediate storage
  uint local_8;
  undefined1 local_4;
  
  buffer[0] = *data;
  buffer[1] = data[1];
  buffer[2] = data[2];
  local_c = dataLen;  // +0x0C offset
  result = 0xffffffff;
  local_8 = channelIndex;
  local_4 = 1;
  
  if (channelIndex < 6) {
    // Channel 0-5: use first channel buffer at +0x14
    data = (undefined8 *)0x6;
    result = FUN_0068d790(this + 0x14, &data, (undefined8 *)buffer);
    return result;
  }
  if (channelIndex < 0x10) {
    // Channel 6-15: use second channel buffer at +0x29c
    data = (undefined8 *)0x10;
    result = FUN_0068d790(this + 0x29c, &data, (undefined8 *)buffer);
    return result;
  }
  if (channelIndex < 0x1f) {
    // Channel 16-30: use third channel buffer at +0x95c
    data = (undefined8 *)0x1f;
    result = FUN_0068d790(this + 0x95c, &data, (undefined8 *)buffer);
  }
  return result;
}