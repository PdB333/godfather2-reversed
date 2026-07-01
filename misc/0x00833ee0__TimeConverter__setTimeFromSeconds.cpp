// FUNC_NAME: TimeConverter::setTimeFromSeconds
void __thiscall TimeConverter::setTimeFromSeconds(int this, undefined4 *timeStruct)
{
  int totalSeconds;
  float fVar2;
  
  if ((undefined4 *)(this + 4) != timeStruct) {
    *(undefined4 *)(this + 4) = *timeStruct;          // +0x04: hours
    *(undefined4 *)(this + 8) = timeStruct[1];        // +0x08: minutes
    *(undefined4 *)(this + 0xc) = timeStruct[2];      // +0x0c: seconds
    *(undefined4 *)(this + 0x10) = timeStruct[3];     // +0x10: frames? (unused in calc)
    *(undefined4 *)(this + 0x14) = timeStruct[4];     // +0x14: unknown
    *(undefined4 *)(this + 0x18) = timeStruct[5];     // +0x18: unknown
  }
  // Convert time components to total seconds: timeStruct[5] + (timeStruct[4] + timeStruct[3] * 60) * 60
  totalSeconds = timeStruct[5] + (timeStruct[4] + timeStruct[3] * 0x3c) * 0x3c;
  fVar2 = (float)totalSeconds;
  if (totalSeconds < 0) {
    fVar2 = fVar2 + DAT_00e44578;  // Convert negative int to float properly (add 2^32 as float)
  }
  *(float *)(this + 0x4c) = fVar2;  // +0x4c: totalSeconds as float
  return;
}