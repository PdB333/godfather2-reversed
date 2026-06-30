// FUNC_NAME: EngineConfig::initDefaults
struct EngineConfig {
    void* field0;      // +0x00: pointer to some global data
    int elementSize;   // +0x04: element size (0x14 = 20)
    int elementCount;  // +0x08: element count (0x14 = 20)
    void* field3;      // +0x0C: another global pointer
    int flags;         // +0x10: flags (2)
    int zeroField;     // +0x14: initialized to 0
    void* field6;      // +0x18: global pointer
    void* field7;      // +0x1C: global pointer
    void* field8;      // +0x20: global pointer
};

// __fastcall: first parameter (this) in ECX
void __fastcall EngineConfig::initDefaults(EngineConfig* this) {
    this->field0 = (void*)DAT_00e44618;
    this->elementSize = 0x14;
    this->elementCount = 0x14;
    this->field3 = (void*)DAT_0110a440;
    this->flags = 2;
    this->zeroField = 0;
    this->field6 = (void*)DAT_0110ae38;
    this->field7 = (void*)DAT_00e2fc48;
    this->field8 = (void*)DAT_00e2b04c;
}