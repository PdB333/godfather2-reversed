// FUNC_NAME: SomeStruct::init
void SomeStruct::init()
{
    // +0x00: some flag or type, set to 0
    this->field0 = 0;
    // +0x04: pointer to global static data (DAT_00d5e288)
    this->staticData1 = reinterpret_cast<SomeType*>(DAT_00d5e288);
    // +0x08: pointer to another global static (DAT_00d5efd0)
    this->staticData2 = reinterpret_cast<SomeOtherType*>(DAT_00d5efd0);
    // +0x10..+0x2c: clear 8 consecutive int fields (counters, flags, etc.)
    this->field10 = 0;
    this->field14 = 0;
    this->field18 = 0;
    this->field1c = 0;
    this->field20 = 0;
    this->field24 = 0;
    this->field28 = 0;
    this->field2c = 0;
}