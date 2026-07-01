// FUNC_NAME: Timer::update
void __fastcall Timer::update(int this)
{
  float fVar1;
  
  if ((*(char *)(this + 0x3c) != '\0') && // +0x3c: active flag
     (fVar1 = DAT_012067e8 + *(float *)(this + 0x38), *(float *)(this + 0x38) = fVar1, // +0x38: elapsed time
     *(float *)(this + 0x34) <= fVar1)) { // +0x34: duration
    FUN_008cf960(); // callback function
    *(undefined1 *)(this + 0x3c) = 0; // deactivate timer
  }
  return;
}