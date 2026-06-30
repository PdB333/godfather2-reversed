// FUN_0046f7b0: EARSObject::setPositionAndUpdate
void __thiscall EARSObject::setPositionAndUpdate(EARSObject* this, int* position)
{
    // Copy 3 components from source position (x, y, z)
    this->m_position[0] = position[0];                  // +0x100 (offset 0x40 * 4)
    this->m_position[1] = position[1];                  // +0x104
    this->m_position[2] = position[2];                  // +0x108
    // Set w component to a constant (likely 1.0f for homogeneous coordinates)
    this->m_position[3] = DAT_00e2b1a4;                 // +0x10C

    FUN_006101b0();                                     // Engine synchronization/lock call

    // Invoke virtual function at vtable+0x68 (probably ApplyTransform or Update)
    (*(void (__thiscall **)(EARSObject*))(*(int*)this + 0x68))(this);
}