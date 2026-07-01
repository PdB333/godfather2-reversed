// FUNC_NAME: NetObject::unpackUpdate
void __thiscall NetObject::unpackUpdate(int *this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  FUN_008d8680(param_2); // BitStream::readBegin
  FUN_0043aff0(param_2,0x1ea6b19a); // BitStream::readInt with mask
  cVar1 = FUN_0043b120(); // BitStream::readBool - more data available?
  while (cVar1 == '\0') {
    FUN_0043b210(); // BitStream::readInt - field ID
    uVar2 = FUN_0043ab70(); // BitStream::readInt - field type?
    switch(uVar2) {
    case 0: // int field
      iVar3 = FUN_0043b210(); // read value
      this[0x6f] = *(int *)(iVar3 + 8); // this->field_0x1BC
      break;
    case 1:
      iVar3 = FUN_0043b210();
      this[0x70] = *(int *)(iVar3 + 8); // this->field_0x1C0
      break;
    case 2:
      iVar3 = FUN_0043b210();
      this[0x71] = *(int *)(iVar3 + 8); // this->field_0x1C4
      break;
    case 3:
      iVar3 = FUN_0043b210();
      this[0x72] = *(int *)(iVar3 + 8); // this->field_0x1C8
      break;
    case 4: // float[4] field (quaternion?)
      FUN_0043b210();
      piVar4 = (int *)FUN_0043abc0(); // read float array
      this[0x73] = *piVar4; // this->field_0x1CC
      this[0x74] = piVar4[1]; // this->field_0x1D0
      this[0x75] = piVar4[2]; // this->field_0x1D4
      this[0x76] = piVar4[3]; // this->field_0x1D8
      break;
    case 5:
      FUN_0043b210();
      piVar4 = (int *)FUN_0043abc0();
      this[0x78] = *piVar4; // this->field_0x1E0
      this[0x79] = piVar4[1]; // this->field_0x1E4
      this[0x7a] = piVar4[2]; // this->field_0x1E8
      this[0x7b] = piVar4[3]; // this->field_0x1EC
      break;
    case 6:
      FUN_0043b210();
      piVar4 = (int *)FUN_0043abc0();
      this[0x7d] = *piVar4; // this->field_0x1F4
      this[0x7e] = piVar4[1]; // this->field_0x1F8
      this[0x7f] = piVar4[2]; // this->field_0x1FC
      this[0x80] = piVar4[3]; // this->field_0x200
      break;
    case 7: // string field
      FUN_0043b210();
      uVar2 = FUN_0043ab90(); // read string
      FUN_004089b0(this + 0x65,uVar2); // StringTable::insert(this->field_0x194, string)
      break;
    case 8:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x67,uVar2); // this->field_0x19C
      break;
    case 9:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408240(this + 0x69,uVar2); // this->field_0x1A4 (different string copy?)
      break;
    case 10: // boolean field
      iVar3 = FUN_0043b210();
      if (*(int *)(iVar3 + 8) == 0) {
        (**(code **)(*this + 0x19c))(); // call virtual function at vtable+0x19c
      }
      else {
        (**(code **)(*this + 0x198))(); // call virtual function at vtable+0x198
      }
      break;
    case 0xb: // enum field
      FUN_0043b210();
      uVar2 = FUN_0043ab90(); // read enum value
      iVar3 = FUN_004dafd0(uVar2); // convert to int
      this[0x6c] = iVar3; // this->field_0x1B0
      break;
    case 0xc:
      iVar3 = FUN_0043b210();
      this[0x6d] = *(int *)(iVar3 + 8); // this->field_0x1B4
      break;
    case 0xd:
      iVar3 = FUN_0043b210();
      this[0x6e] = (int)(*(float *)(iVar3 + 8) * DAT_00e445c8); // this->field_0x1B8, scaled float to int
    }
    FUN_0043b1a0(); // BitStream::readEnd
    cVar1 = FUN_0043b120(); // check for more data
  }
  return;
}