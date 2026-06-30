// FUNC_NAME: SomeClass::initSomeComponent
void __fastcall SomeClass::initSomeComponent(int this)
{
  FUN_006daa50(); // likely some base initialization or global setup
  DAT_00e50df6 = 1; // global flag set to 1
  *(uint8_t *)(this + 0x30) = 1; // +0x30: some bool/flag
  *(uint8_t *)(this + 0x38) = 1; // +0x38: another bool/flag
  *(int *)(this + 0x34) = 0;     // +0x34: some int
  *(uint8_t *)(this + 0x39) = 0; // +0x39: bool
  *(uint8_t *)(this + 0x3a) = 0; // +0x3a: bool
  *(uint8_t *)(this + 0x3b) = 0; // +0x3b: bool
  *(uint8_t *)(this + 0x3c) = 0; // +0x3c: bool
  *(float *)(this + 0x40) = 0.0f; // +0x40: float (zeroed via subtraction)
  *(float *)(this + 0x44) = 0.0f; // +0x44: float
  *(float *)(this + 0x48) = 0.0f; // +0x48: float
  *(int *)(this + 0x4c) = 0;      // +0x4c: int
  *(int *)(this + 0x50) = 0;      // +0x50: int
  *(int *)(this + 0x54) = 0;      // +0x54: int
  *(int *)(this + 0x58) = 0;      // +0x58: int
  *(int *)(this + 0x5c) = 0;      // +0x5c: int
  *(int *)(this + 0x60) = 0;      // +0x60: int
  *(int *)(this + 0x64) = DAT_00d5eea0; // +0x64: some global value
  *(int *)(this + 0x68) = 0;      // +0x68: int
  *(int *)(this + 0x6c) = 0;      // +0x6c: int
  *(int *)(this + 0x70) = 0;      // +0x70: int
  return;
}