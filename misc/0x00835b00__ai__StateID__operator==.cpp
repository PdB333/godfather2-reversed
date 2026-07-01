// FUNC_NAME: ai::StateID::operator==
uint ai::StateID::operator==(ai::StateID *this, ai::StateID *other)
{
  if (((this->id0 == other->id0) &&
       (this->id1 == other->id1)) &&
      (this->id2 == other->id2) &&
      (this->id3 == other->id3) &&
      (this->id4 == other->id4) &&
      (this->id5 == other->id5)) {
    return 0x100 | (uint)(this->id5) & 0xffffff00;
  }
  return (uint)(this->id5) & 0xffffff00;
}