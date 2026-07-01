// FUNC_NAME: DataBlock::clear
void __fastcall DataBlock::clear(DataBlock* this)
{
    this->field_0 = 0;   // +0x00
    this->field_4 = 0;   // +0x04
    this->field_8 = 0;   // +0x08
    this->field_10 = 0;  // +0x10 (offset 16 = 4*4)
    return;
}