// FUNC_NAME: GUIDObject::initializeFromLiteralOrExternal
// Constructor/initializer for a GUID object that sets a default UUID string or copies from an external source.
// Function address: 0x004dac20

class GUIDObject {
public:
    int m_flag;                        // +0x00: 0 = from external, 1 = generated
    char m_guidString[39];             // +0x04: 36 chars + 2-byte short + 1 char? Actually copies 36+2+1 bytes from literal
    int field_0x4c;                    // +0x4C: set to 0
};

// External functions used
void GUID_initDefault();               // 0x004da910
void GUID_parseFromExt(GUIDObject* dst, const char* src, int length); // 0x004d9080
void GUID_generateString(char* buffer); // 0x004d9d60
void GUID_finalize();                  // 0x004d9ff0
void GUID_generateBinary(int* unknown); // 0x004da530
void operator_delete(void* ptr);       // 0x009c8eb0
void GUID_freeResources();              // 0x004d8be0

GUIDObject* __thiscall GUIDObject::initializeFromLiteralOrExternal(GUIDObject* this, const char* externalGuidStr, int externalGuidLen) {
    // Default GUID string literal: "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}"
    const char* defaultGuid = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
    char* dest = this->m_guidString;
    int count = 9;
    // Copy 36 bytes (9 dwords) of the literal into m_guidString
    while (count != 0) {
        *(unsigned int*)dest = *(unsigned int*)defaultGuid;
        defaultGuid += 4;
        dest += 4;
        count--;
    }
    // Copy remaining 2 bytes and 1 byte (short + char)
    *(unsigned short*)dest = *(unsigned short*)defaultGuid;
    defaultGuid += 2;
    *(dest + 2) = *defaultGuid;

    this->field_0x4c = 0;            // +0x4C: initialize to 0
    this->m_flag = 1;                // +0x0B: set byte at offset 11? Actually param_1 + 0xb = byte, set to 1

    GUID_initDefault();              // 0x004da910: maybe initializes internal state

    char local_buffer[20];           // local_48
    int* local_10 = nullptr;        // local_10
    int* local_34 = nullptr;        // local_34
    unsigned int local_30[10];       // local_30 (enough for copy)

    if (local_buffer[0] == 1) {
        // External GUID provided
        this->m_flag = 0;
        GUID_parseFromExt((GUIDObject*)local_30, externalGuidStr, externalGuidLen);
        // Copy the parsed GUID into our m_guidString again
        if (this->m_guidString != (char*)local_30) {
            char* src = (char*)local_30;
            char* dst = this->m_guidString;
            int n = 9;
            while (n != 0) {
                *(unsigned int*)dst = *(unsigned int*)src;
                src += 4;
                dst += 4;
                n--;
            }
            *(unsigned short*)dst = *(unsigned short*)src;
            dst[2] = src[2];
        }
    } else {
        // Generate new GUID
        this->m_flag = 1;
        GUID_generateString(local_buffer);
        GUID_finalize();
        if (local_10 != nullptr) {
            GUID_generateBinary(local_10);
            operator_delete(local_10);
        }
    }

    if (local_34 != nullptr) {
        GUID_freeResources();
        operator_delete(local_34);
    }

    return this;
}