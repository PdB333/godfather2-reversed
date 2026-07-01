// FUNC_NAME: SomeClass::deserializeFromStream
void __thiscall FUN_0090e570(int this, undefined4 stream)
{
  char hasMore;
  undefined4 value;
  int node;
  
  FUN_0043b540(stream);
  FUN_0043aff0(stream,0x805cda59);
  hasMore = FUN_0043b120();
  while (hasMore == '\0') {
    FUN_0043b210();
    value = FUN_0043ab70();
    switch(value) {
    case 0:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_004089b0(this + 0x60,value); // +0x60: some float field
      break;
    case 1:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_004089b0(this + 0x68,value); // +0x68: another float field
      break;
    case 2:
      node = FUN_0043b210();
      node = *(int *)(node + 8);
      if (node == 0) {
        node = *(int *)(this + 0x80); // +0x80: some pointer field
      }
      *(int *)(this + 0x80) = node;
      break;
    case 3:
      node = FUN_0043b210();
      *(undefined4 *)(this + 0xac) = *(undefined4 *)(node + 8); // +0xac: float field
      break;
    case 5:
      node = FUN_0043b210();
      if (*(int *)(node + 8) == 0) {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) & 0xfffffffd; // +0xb0: bitfield
      }
      else {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) | 2;
      }
      break;
    case 6:
      node = FUN_0043b210();
      if (*(int *)(node + 8) == 0) {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) & 0xfffffffe;
      }
      else {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) | 1;
      }
      break;
    case 7:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_00408980(this + 0x50,value); // +0x50: some int field
      break;
    case 8:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_00408980(this + 0x58,value); // +0x58: another int field
      break;
    case 9:
      node = FUN_0043b210();
      *(undefined4 *)(this + 0xa8) = *(undefined4 *)(node + 8); // +0xa8: float field
      break;
    case 10:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_004089b0(this + 0x70,value); // +0x70: float field
      break;
    case 0xb:
      FUN_0043b210();
      value = FUN_0043ab90();
      FUN_004089b0(this + 0x78,value); // +0x78: float field
      break;
    case 0xc:
      node = FUN_0043b210();
      if (*(int *)(node + 8) == 0) {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) | 0x10;
      }
      else {
        *(uint *)(this + 0xb0) = *(uint *)(this + 0xb0) & 0xffffffef;
      }
    }
    FUN_0043b1a0();
    hasMore = FUN_0043b120();
  }
  if (*(float *)(this + 0xac) < *(float *)(this + 0xa8)) {
    *(float *)(this + 0xa8) = *(float *)(this + 0xac);
  }
  return;
}