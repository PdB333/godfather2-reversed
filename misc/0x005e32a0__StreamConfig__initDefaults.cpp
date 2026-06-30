// FUNC_NAME: StreamConfig::initDefaults
void __fastcall StreamConfig::initDefaults(StreamConfig *this)
{
    this->field_0 = 0;
    this->field_4 = 0x3200000;  // 52,428,800 bytes (~50 MB)
    this->field_8 = 0x800000;   // 8,388,608 bytes (8 MB)
    this->field_c = 0x2000000;  // 33,554,432 bytes (32 MB)
    this->field_10 = 0xc0000;   // 786,432 bytes (768 KB)
    this->field_14 = 0x180000;  // 1,572,864 bytes (1.5 MB)
    this->field_28 = 1;         // enable flag
    this->field_18 = 0;
    this->field_1c = 0;
    this->field_20 = 0;
    this->field_24 = 0;
}