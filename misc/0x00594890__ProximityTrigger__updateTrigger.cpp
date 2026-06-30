// FUNC_NAME: ProximityTrigger::updateTrigger
 void ProximityTrigger::updateTrigger(void)
{
    uint uVar1;
    float fVar2;
    float fX_local; // from stack array
    float fY_local;
    int flags;
    int* componentPtr;

    // Update flags based on target entity (unaff_EDI) byte fields
    // Bit 4 (0x10) set if target's +0x36 is non-zero
    m_flags = m_flags ^ ((uint)(*(char *)(targetEntity + 0x36) != '\0') << 4 ^ m_flags) & 0x10;
    uVar1 = ((uint)(*(char *)(targetEntity + 0x37) != '\0') << 7 ^ m_flags) & 0x80 ^ m_flags;
    m_flags = uVar1;
    // Bit 12 (0x1000) set if target's +0x35 is non-zero
    m_flags = ((uint)(*(char *)(targetEntity + 0x35) != '\0') << 0xc ^ uVar1) & 0x1000 ^ uVar1;

    // Store squared radius from target's position magnitude
    m_radiusSq = (int)(*(float *)(targetEntity + 0x2c) * *(float *)(targetEntity + 0x2c));
    m_someField0x2d = *(int *)(targetEntity + 0x30);
    m_someField0x2e = *(int *)(targetEntity + 0x28);

    // If component pointer exists and its first byte has bit 2 set, call different virtual
    componentPtr = m_componentPtr; // this+0x14
    if ((componentPtr == (int*)0x0) || ((*(byte *)componentPtr & 4) == 0)) {
        (**(code **)(*g_globalSingleton + 0x10))();
    } else {
        (**(code **)(*g_globalSingleton + 0x18))();
    }

    // Call virtual function (likely getLocalPosition) that fills stack array
    (**(code **)(*this + 0x10))(&fX_local); // assuming first 2 floats are x,y

    fVar2 = (unaff_EBX - m_positionX) * (unaff_EBX - m_positionX) +
            (fY_local - m_positionY) * (fY_local - m_positionY);

    // If squared distance exceeds radius (and not equal), trigger callback
    if ((float)m_radiusSq <= fVar2 && fVar2 != (float)m_radiusSq) {
        (**(code **)(*this + 0x5c))
                  (*(undefined4 *)(targetEntity + 0x10),           // arg1
                   *(undefined1 *)(targetEntity + 0x34),           // byte arg2
                   *(undefined4 *)(targetEntity + 0x18),           // arg3
                   *(undefined4 *)(targetEntity + 0x1c),           // arg4
                   *(undefined4 *)(targetEntity + 0x20),           // arg5
                   *(undefined4 *)(targetEntity + 0x24));           // arg6
    }

    // Set "trigger activated" flag (bit 5)
    m_flags = m_flags | 0x20;
    return;
}