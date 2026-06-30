// FUNC_NAME: PlayerF2FSM::constructor
int __fastcall PlayerF2FSM::constructor(int thisPtr)
{
  // Call base class constructors
  FUN_006da9d0();  // Likely PlayerSM::constructor or similar base
  FUN_006daa50();  // Likely another base class constructor

  // Set global flag
  DAT_00e50df6 = 1;  // Some global state flag

  // Initialize state machine fields
  *(uint8_t *)(thisPtr + 0x30) = 1;  // +0x30: currentState (initial state)
  *(uint8_t *)(thisPtr + 0x38) = 1;  // +0x38: some state flag
  *(uint32_t *)(thisPtr + 0x34) = 0; // +0x34: state timer/counter
  *(uint8_t *)(thisPtr + 0x39) = 0;  // +0x39: flag
  *(uint8_t *)(thisPtr + 0x3a) = 0;  // +0x3a: flag
  *(uint8_t *)(thisPtr + 0x3b) = 0;  // +0x3b: flag
  *(uint8_t *)(thisPtr + 0x3c) = 0;  // +0x3c: flag

  // Zero out position/velocity vectors (self-subtract to zero)
  *(float *)(thisPtr + 0x40) = *(float *)(thisPtr + 0x40) - *(float *)(thisPtr + 0x40); // +0x40: x position
  *(float *)(thisPtr + 0x44) = *(float *)(thisPtr + 0x44) - *(float *)(thisPtr + 0x44); // +0x44: y position
  *(float *)(thisPtr + 0x48) = *(float *)(thisPtr + 0x48) - *(float *)(thisPtr + 0x48); // +0x48: z position

  // Initialize more fields
  *(uint32_t *)(thisPtr + 0x4c) = 0;  // +0x4c: some pointer/ID
  *(uint32_t *)(thisPtr + 0x50) = 0;  // +0x50: some pointer/ID
  *(uint32_t *)(thisPtr + 0x54) = 0;  // +0x54: some pointer/ID
  *(uint32_t *)(thisPtr + 0x58) = 0;  // +0x58: some pointer/ID
  *(uint32_t *)(thisPtr + 0x5c) = 0;  // +0x5c: some pointer/ID
  *(uint32_t *)(thisPtr + 0x60) = 0;  // +0x60: some pointer/ID

  // Set a global reference
  *(uint32_t *)(thisPtr + 0x64) = DAT_00d5eea0; // +0x64: some global object pointer

  *(uint32_t *)(thisPtr + 0x68) = 0;  // +0x68: some pointer/ID
  *(uint32_t *)(thisPtr + 0x6c) = 0;  // +0x6c: some pointer/ID
  *(uint32_t *)(thisPtr + 0x70) = 0;  // +0x70: some pointer/ID

  return thisPtr;
}