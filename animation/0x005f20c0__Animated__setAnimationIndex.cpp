// FUNC_NAME: Animated::setAnimationIndex
// Function address: 0x005f20c0
// Role: Sets the current animation index, updates animation flags, and computes frame range
// This is likely part of the EARS animation system (Animated class)

// Offsets (relative to this):
// +0x08: pAnimData - pointer to animation data table
// +0x5c: m_someInt - parameter passed to applyAnimation
// +0x64: m_someByte1 - parameter passed to applyAnimation
// +0x65: m_someByte2 - parameter passed to applyAnimation
// +0x66: m_animIndex - current animation index (byte)
// +0x6c: m_animFlags - 16-bit flags (bit 7 controlled here)
// +0x7b: m_animFlagSource - byte where bit 1 is used to set m_animFlags bit 7
// +0x84: m_frameStart - start frame index (int)
// +0x88: m_frameEnd - end frame index (int)
// +0x8c: m_frameCurrent - current frame index (int)

// Animation data table offsets (pointed to by this+0x08):
// +0x00: unused? (maybe version tag)
// +0x01: flags - if 0, animation table is valid (char, compares to '\0')
// +0x02: maxAnim - maximum animation index (byte)
// +0x03: stride - frame stride (byte, multiplied by 8 for frame step)
// +0x2c: animTableBase - base offset for frame range calculations (int)

void Animated::setAnimationIndex(byte animIdx)
{
    AnimationData* pAnimData = *(AnimationData**)(this + 0x08);

    // Update animation flag: set bit 7 of m_animFlags to value of bit 1 of m_animFlagSource
    m_animFlags = (m_animFlags & 0xFF7F) | (((m_animFlagSource >> 1) & 1) << 7);

    // Check if animation data is valid (flags == 0) and index is not 0xFF
    if ((pAnimData->flags == 0) && (animIdx != 0xFF))
    {
        // Clamp animIdx to valid range [0, maxAnim-1]
        if (pAnimData->maxAnim <= animIdx)
        {
            animIdx = pAnimData->maxAnim - 1;
        }
        m_animIndex = animIdx;
    }
    else
    {
        // Animation data invalid or index is 0xFF: reset or handle error
        resetAnimationState();  // Calls FUN_005f2d10
    }

    // Apply animation parameters (likely sets up playback state)
    applyAnimationParameters(m_someByte1, m_someInt, m_someByte2, m_animIndex);  // Calls FUN_005dbc10

    // Compute frame indices: each animation uses stride*8 bytes per frame
    int frameBase = pAnimData->animTableBase + (pAnimData->stride * m_animIndex * 8);
    m_frameStart    = frameBase;
    m_frameCurrent  = frameBase;
    m_frameEnd      = frameBase + (pAnimData->stride * 8);
}