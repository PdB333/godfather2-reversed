// FUNC_NAME: SoundInstance::setEventAndPlay
// Address: 0x006b5df0
// Role: Sets the event ID for a sound instance, handles playback start/stop, manages looping,
//       and updates internal state (position, volume, etc.). Called when a sound event is triggered.

// Offsets:
// +0x34: flags (bit 29 = fast update, bit 0 = something)
// +0x38: unknown (used with FUN_008c0b10)
// +0x40: current event ID
// +0x58: totalPlayedSamples (or position)
// +0x5c: unknown, set to 0
// +0x60: current sample offset
// +0x68: unknown, set to 0
// +0x6c: pitch or playback rate
// +0x74: samplesRemaining (or accumulated offset)
// +0x80: volume or threshold float
// +0x84: (through external object) bit field used for 3D check
// +0xC0: linked sound instance pointer
// +0xC8: repeat count (set to 1 for music)
// +0x19c: callback object (Lua function or manager)

// External globals:
// _DAT_00d577a0 : master volume threshold (float)

void __thiscall SoundInstance::setEventAndPlay(
    bool restart,
    uint eventId,
    void* owner,
    SoundPlaybackParams* playParams,
    char isMusic
)
{
    uint uVar1;
    bool bWasDifferentOrNoCallback;
    float fVolumeOrThreshold;
    int iVar4;
    uint uVar2;
    uint uVar3;

    // Check if the event ID changed or if there is no callback
    if ((m_eventId == eventId) || (m_callback == NULL)) {
        bWasDifferentOrNoCallback = false;
    } else {
        bWasDifferentOrNoCallback = true;
    }

    // Set new event ID and reset playback state
    m_eventId = eventId;
    m_field68 = 0;
    m_field74 = 0;
    m_field5c = 0;

    // If restart requested, stop any current playback
    if (restart) {
        SoundInstance::reset(this); // FUN_008c4250
    }

    // Special case for the music event (0x637b907) – set infinite loop if flagged
    if ((m_eventId == 0x637b907) && (isMusic != 0)) {
        SoundInstance::setRepeatCount(m_repeatCount, 1); // FUN_008c29a0 – set to loop once? Actually indefinite?
    }

    // Prepare playback if no custom playParams
    if (playParams == NULL) {
        SoundInstance::prepareToPlay(owner); // FUN_006b3cc0
    }

    // Update any linked sound instance
    if (m_linkedSound != NULL) {
        SoundInstance::updateLinked(m_eventId); // FUN_0084a910 (passes event ID)
    }

    // Set playback parameters from either internal state or playParams structure
    if (playParams == NULL) {
        // Use internal sample offset
        m_sampleOffset = m_field60;
        m_samplesRemaining += m_sampleOffset;
        m_field6c = m_sampleOffset;
        m_totalPlayedSamples = m_sampleOffset;

        fVolumeOrThreshold = _DAT_00d577a0;
        if ((fVolumeOrThreshold < m_volumeThreshold) || ((m_flags & 0x20000000) != 0)) {
            SoundInstance::updateLoop(); // FUN_006b2f70
        } else {
            SoundInstance::updateOnce(); // FUN_006b59f0
        }
    } else {
        // Use parameters from playParams structure
        m_sampleOffset = playParams->sampleOffset; // +0x20
        m_field64 = playParams->field40;           // +0x40
        m_field6c = playParams->playbackRate;      // +0x28
        m_samplesRemaining += m_sampleOffset;
        m_totalPlayedSamples = m_sampleOffset;

        fVolumeOrThreshold = _DAT_00d577a0;
        if ((fVolumeOrThreshold < m_volumeThreshold) || ((m_flags & 0x20000000) != 0)) {
            SoundInstance::updateLoop();
        } else {
            SoundInstance::updateOnce();
        }

        if (restart) {
            // Clear fast update bit and call some setup function
            m_flags |= 0x20000000;
            SoundInstance::setupWithParams(m_field38, playParams->field1c, 0); // FUN_008c0b10
            m_flags &= 0xdfffffff;
        }

        // Handle samples remaining overflow (e.g., for looping)
        uVar1 = m_samplesRemaining;
        if (playParams->maxSamples < uVar1) {
            uVar3 = uVar1 - playParams->maxSamples; // overshoot
            uVar2 = (uVar1 < uVar3) ? uVar1 : uVar3; // min(remaining, overshoot)
            m_samplesRemaining = uVar1 - uVar2;
            SoundInstance::updateLoop();
            for (; uVar3 != 0; uVar3--) {
                SoundInstance::releaseSample(); // FUN_006b4da0
            }
        }
    }

    // Notify if event changed, no callback, and the new event's sound object is 3D (bit 5 of flags at +0x84)
    if (bWasDifferentOrNoCallback &&
        ((m_flags & 1) == 0) &&
        (m_eventId != 0))
    {
        iVar4 = SoundManager::getSoundObject(m_eventId); // FUN_008c74d0
        if ((iVar4 != 0) && (((*(uint*)(iVar4 + 0x84) >> 5) & 1) != 0)) {
            SoundInstance::notify3DUpdate(); // FUN_006b5170
        }
    }

    // Callback to script (if present) with event ID converted to string
    if (m_callback != NULL) {
        char fourCC[4];
        SoundManager::eventIdToFourCC(fourCC, m_eventId); // FUN_008c76a0
        ScriptManager::executeCallback(m_callback, fourCC, ...); // FUN_0094ac00 – simplified
    }

    // Finalize playback if no custom playParams
    if (playParams == NULL) {
        SoundInstance::finalizePlayback(owner); // FUN_006b4910
    }
}