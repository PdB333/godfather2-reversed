// FUNC_NAME: AudioEmitter::tick

void __thiscall AudioEmitter::tick(int thisPtr)
{
    // Call base update (FUN_00490b20)
    baseUpdate();

    // If we have a sound handle, update its 3D position
    if (*(int*)(thisPtr + 0x1C0) != 0) {
        // Arguments: sound channel (from +0x14), sound handle, position vector (at +0x1D0)
        setSoundPosition(
            *(int*)(thisPtr + 0x14),      // m_channel (or audio channel index)
            *(int*)(thisPtr + 0x1C0),     // m_soundHandle
            (float*)(thisPtr + 0x1D0)     // m_position (likely 3 floats: x, y, z)
        );
    }

    // If we have an effect handle and the audio type matches the global ambient type
    if ( (*(int*)(thisPtr + 0x1E0) != 0) && (*(int*)(thisPtr + 0x10) == DAT_01205458) ) {
        // Arguments: audio type, effect handle, effect parameter
        setEffectParameter(
            *(int*)(thisPtr + 0x10),      // m_audioType
            *(int*)(thisPtr + 0x1E0),     // m_effectHandle
            *(int*)(thisPtr + 0x1E4)      // m_effectParam
        );
    }

    return;
}