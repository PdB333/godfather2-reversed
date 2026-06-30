// FUNC_NAME: GameDataBlock::copyFrom
void __thiscall GameDataBlock::copyFrom(GameDataBlock *this, const GameDataBlock *source)
{
  // Copy fields at offsets +0x00 through +0x10 (5 dwords)
  this->field_0x00 = source->field_0x00;
  this->field_0x04 = source->field_0x04;
  this->field_0x08 = source->field_0x08;
  this->field_0x0C = source->field_0x0C;
  this->field_0x10 = source->field_0x10;

  // Skip fields at +0x14, +0x18, +0x1C (indices 5,6,7)
  // Copy fields at +0x20 through +0x4C (12 dwords)
  this->field_0x20 = source->field_0x20;
  this->field_0x24 = source->field_0x24;
  this->field_0x28 = source->field_0x28;
  this->field_0x2C = source->field_0x2C;
  this->field_0x30 = source->field_0x30;
  this->field_0x34 = source->field_0x34;
  this->field_0x38 = source->field_0x38;
  this->field_0x3C = source->field_0x3C;
  this->field_0x40 = source->field_0x40;
  this->field_0x44 = source->field_0x44;
  this->field_0x48 = source->field_0x48;
  this->field_0x4C = source->field_0x4C;
}