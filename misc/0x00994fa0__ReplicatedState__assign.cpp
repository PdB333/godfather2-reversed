// FUNC_NAME: ReplicatedState::assign
void __thiscall ReplicatedState::assign(ReplicatedState *this, ReplicatedState const *other)
{
  // Copy fields with reordering (likely for alignment/cache optimization)
  // Offsets: this[0..2], this[4..11], this[0xb], this[12..20], this[24..2d]
  // Total size approx 0xB8 bytes (46 dwords)
  this->field0 = other->field0;
  this->field1 = other->field1;
  this->field2 = other->field2;

  // Temporary variables to reduce register shuffling
  int tempB = other->fieldB;
  int temp5 = other->field5;
  int temp6 = other->field6;
  int temp7 = other->field7;
  int temp8 = other->field8;
  int temp9 = other->field9;
  int tempA = other->fieldA;

  this->field4 = other->field4;
  this->field5 = temp5;
  this->field6 = temp6;
  this->field7 = temp7;
  this->field8 = temp8;
  this->field9 = temp9;
  this->fieldA = tempA;
  this->fieldB = tempB;

  // Copy next block (C through 13)
  int tempC = other->fieldC;
  int tempD = other->fieldD;
  int tempE = other->fieldE;
  int tempF = other->fieldF;
  int temp10 = other->field10;
  int temp11 = other->field11;
  int temp12 = other->field12;
  int temp13 = other->field13;

  this->fieldC = tempC;
  this->fieldD = tempD;
  this->fieldE = tempE;
  this->fieldF = tempF;
  this->field10 = temp10;
  this->field11 = temp11;
  this->field12 = temp12;
  this->field13 = temp13;

  this->field14 = other->field14;

  // Copy block from 1F, 19-1E, 18, then 20-28 sequentially
  int temp1F = other->field1F;
  int temp19 = other->field19;
  int temp1A = other->field1A;
  int temp1B = other->field1B;
  int temp1C = other->field1C;
  int temp1D = other->field1D;
  int temp1E = other->field1E;
  int temp20 = other->field20;
  int temp21 = other->field21;
  int temp22 = other->field22;
  int temp23 = other->field23;
  int temp24 = other->field24;
  int temp25 = other->field25;
  int temp26 = other->field26;
  int temp27 = other->field27;

  this->field18 = other->field18;
  this->field19 = temp19;
  this->field1A = temp1A;
  this->field1B = temp1B;
  this->field1F = temp1F;
  this->field1C = temp1C;
  this->field1D = temp1D;
  this->field1E = temp1E;
  this->field20 = temp20;
  this->field21 = temp21;
  this->field22 = temp22;
  this->field23 = temp23;
  this->field24 = temp24;
  this->field25 = temp25;
  this->field26 = temp26;
  this->field27 = temp27;

  this->field28 = other->field28;
  this->field29 = other->field29;
  this->field2A = other->field2A;
  this->field2B = other->field2B;
  this->field2C = other->field2C;
  this->field2D = other->field2D;
}