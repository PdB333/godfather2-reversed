// FUNC_NAME: BaseVehicle::BaseVehicle

void __thiscall BaseVehicle::BaseVehicle(void *this, int unusedParam2, int param3, int param4)
{
  // Call base class constructor (likely at 0x0059b5e0)
  FUN_0059b5e0();

  // Set position or some two-component value (offset 0x70, 0x74)
  *(int *)((char *)this + 0x70) = param3;
  *(int *)((char *)this + 0x74) = param4;

  // Initialize various state fields
  *(int *)((char *)this + 0x78) = 0;           // +0x78: some int (flags?)
  *(short *)((char *)this + 0x80) = 0;        // +0x80: short (speed?)
  *(short *)((char *)this + 0x82) = 0;        // +0x82: short (something)
  *(int *)((char *)this + 0x88) = 0;           // +0x88: int
  *(short *)((char *)this + 0x86) = 0;        // +0x86: short
  *(int *)((char *)this + 0x7c) = 0;           // +0x7c: int (counter?)
  *(short *)((char *)this + 0x84) = 4;         // +0x84: short (e.g., wheel count?)

  // Initialize two vector or matrix objects at offsets 0x8c and 0x98
  // Using a global function table (DAT_012055a8) at offset 0x34 (likely a "zero" function)
  int (*zeroFunc)(int, int, int, void *) = **(int (***)(int, int, int, void *))0x012055a8;
  zeroFunc(0, 0, 0, (char *)this + 0x8c);    // +0x8c: first vector (e.g., position offset)
  zeroFunc(0, 0, 0, (char *)this + 0x98);    // +0x98: second vector (e.g., velocity?)

  // Remaining fields set to zero
  *(int *)((char *)this + 0xa4) = 0;          // +0xa4: int
  *(int *)((char *)this + 0xa8) = 0;          // +0xa8: int
  *(int *)((char *)this + 0xac) = 0;          // +0xac: int (maybe a handle or ID)
}