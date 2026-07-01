// FUNC_NAME: NetConnection::NetConnection
// Function address: 0x0098a040
// Constructor for NetConnection (EARS network connection class)
// Inherits from? Vtable at 0x00d916a8

// Known offsets (relative to this):
// +0x00: vtable pointer
// +0x04: pointer to string (password or source string)
// +0x14: port + 1
// +0x18: field (int)
// +0x1C: field (int)
// +0x20: field (int)
// +0x28: field (int)
// +0x2C: field (int)
// +0x30: field (int)
// +0x34: byte flag (password required?)
// +0x38: field (int) - result of string check
// +0x3C: field (int)
// +0x40: buffer for string copy (size unknown)

NetConnection* __thiscall NetConnection::NetConnection(
    NetConnection* this,
    const char* sourceStr,      // param_2: source string (likely connection info)
    int portValue,              // param_3: base port (stored +1)
    byte enablePasswordFlag     // param_4: initial flag byte
)
{
    char cVar1;
    undefined1* stringPtr;
    undefined4 uVar3;
    int iVar4;
    undefined1* local_10;       // Uninitialized in decompilation, likely output from string copy
    code* local_4;              // Uninitialized, likely callback from string copy

    // Set vtable
    this->vtable = &PTR_FUN_00d916a8;

    // Initialize source string (possibly construct a string object)
    sub_004d3bc0(sourceStr);

    // Store port + 1
    this->m_portPlusOne = portValue + 1;                       // +0x14
    this->m_field0x18 = 0;                                     // +0x18
    this->m_field0x20 = 0;                                     // +0x20
    this->m_field0x1C = 0;                                     // +0x1C
    this->m_field0x28 = 0;                                     // +0x28
    this->m_field0x2C = 0;                                     // +0x2C
    this->m_field0x30 = 0;                                     // +0x30
    this->m_flag = enablePasswordFlag;                         // +0x34 (byte)
    this->m_field0x38 = 0;                                     // +0x38
    this->m_field0x3C = 0;                                     // +0x3C

    // Perform network binding with port+1
    sub_004dbbb0(this->m_portPlusOne);

    // Get pointer to string stored at +0x04 (may be the same as sourceStr or modified)
    stringPtr = (undefined1*)this->m_pString;                  // +0x04
    if (stringPtr == (undefined1*)0x0) {
        stringPtr = &DAT_0120546e;                             // default empty string?
    }

    // Copy string into buffer at +0x40, returns success flag and sets local_10/local_4 (callback)
    cVar1 = sub_005a03a0(stringPtr, &this->m_buffer);         // +0x40
    if (cVar1 != '\0') {
        // Initialize the copied buffer as a string object
        sub_004d3bc0(this->m_buffer);                         // +0x40 (treated as object)
        sub_004d4c00(&DAT_00e337ec, &DAT_00e3ed40);           // static initialization?

        // Use local_10 (result from previous call?) to get another string
        stringPtr = local_10;
        if (local_10 == (undefined1*)0x0) {
            stringPtr = &DAT_0120546e;
        }
        uVar3 = sub_004dafd0(stringPtr);                       // Get some value
        this->m_field0x38 = uVar3;                             // +0x38

        // Call function pointer if local_10 was not null
        if (local_10 != (undefined1*)0x0) {
            (*local_4)(local_10);                              // Cleanup?
        }
    }

    // Check if source string contains "password"
    iVar4 = sub_004d6810(sourceStr, "password");               // Compare strings
    if (iVar4 != 0) {
        this->m_flag = 1;                                      // Enable password flag
    }

    return this;
}