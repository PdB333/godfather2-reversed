// FUNC_NAME: Guid::Initialize
// Constructor/initializer for GUID object (0x004dac20)
// Fields:
//   +0x00: m_status (int)
//   +0x04: m_guidBuffer[39] (char)  // ASCII GUID string including braces (39 bytes)
//   +0x2C: m_flag (byte)            // some flag
//   +0x4C: m_generationResult (int) // result of generation

int __thiscall Guid::Initialize(Guid* this, Guid* other) {
    // Initialize with placeholder invalid GUID "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}"
    const char* invalidGuidStr = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
    char* dest = this->m_guidBuffer;  // &this[1] (offset +0x04)
    // Copy 36 bytes (9 dwords)
    for (int i = 0; i < 9; i++) {
        *(int*)dest = *(int*)invalidGuidStr;
        invalidGuidStr += 4;
        dest += 4;
    }
    // Copy remaining 2 bytes (word)
    *(short*)dest = *(short*)invalidGuidStr;
    invalidGuidStr += 2;
    dest += 2;
    // Copy last 1 byte
    *dest = *invalidGuidStr;
    
    this->m_flag = 1;                  // +0x2B? Actually offset 0x2C from start
    this->m_generationResult = 0;      // +0x4C
    
    Guid::initializeStaticData();      // FUN_004da910
    
    // Check a global state (local variable likely from a static function)
    char localBuffer[20];              // local_48
    // localBuffer[0] is set by something? Probably by initializeStaticData
    if (localBuffer[0] == 0x01) {
        // Generation from other GUID is possible
        this->m_status = 0;            // +0x00
        Guid::generateFromParams(&local_30, *other, other->m_generationResult); // FUN_004d9080
        // Copy generated GUID from local_30 into this->m_guidBuffer
        if (&this->m_guidBuffer != &local_30) {
            // Copy 36 bytes (9 dwords) + 2 bytes + 1 byte
            int* src = (int*)&local_30;
            int* dst = (int*)this->m_guidBuffer;
            for (int i = 0; i < 9; i++) {
                *dst++ = *src++;
            }
            *(short*)dst = *(short*)src;
            *(char*)(dst+2) = *(char*)(src+2);
        }
    }
    else {
        // Use random generation
        this->m_status = 1;
        Guid::getRandomBytes(localBuffer);     // FUN_004d9d60
        Guid::createGuidFromRandom();           // FUN_004d9ff0
        if (local_10 != 0) {                    // local_10 is some allocated memory
            Guid::freeGuidData();               // FUN_004da530
            free(local_10);                      // FUN_009c8eb0
        }
    }
    
    // Cleanup if necessary
    if (local_34 != 0) {
        Guid::cleanupTemporary();                // FUN_004d8be0
        free(local_34);                          // FUN_009c8eb0
    }
    
    return this;
}