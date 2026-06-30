// FUNC_NAME: Sentient::constructor
void Sentient::constructor() {
    // Call base class constructor (FUN_0059c2e0) – likely initializes core fields
    BaseObject::constructor();

    // Clear upper 16 bits of some field at offset +2 (m_state) – possibly a state variable
    *(uint16*)((uint8*)this + 2) = 0; // +0x02

    // Set flag bit 15 (0x8000) in the flags at offset +0 – marks object as active/initialized
    *(uint32*)this |= 0x8000; // +0x00

    // Debug/log call with severity 4 (FUN_005ba620)
    debugPrint(4);
}