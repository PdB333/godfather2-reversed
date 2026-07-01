// FUNC_NAME: Mission::Initialize
void __thiscall Mission::Initialize(Mission* this, int param_2, byte missionType, int missionId)
{
    int basePtr;
    
    if (this == 0) {
        basePtr = 0;
    } else {
        basePtr = (int)this + 4; // +0x04: base class data
    }
    // Initialize base class (likely with vtable pointer or type descriptor at LAB_00991ca0)
    FUN_005c0c50(basePtr, &LAB_00991ca0);
    
    // Clear mission flags and ID
    this->m_flags = 0;          // +0x88: ushort, low 2 bits used for type
    this->m_missionId = 0;      // +0x8c: int
    
    // Secondary initialization (possibly global state or another object)
    FUN_00991ad0();
    
    // Set actual values
    this->m_missionId = missionId;           // +0x8c
    this->m_flags = (ushort)(missionType & 3); // only 2 bits used, +0x88
    
    // Final base class setup with original parameter
    FUN_005c0d50((int)this + 4, &LAB_00991ca0, param_2);
}