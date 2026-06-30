// FUNC_NAME: Animated::initializeLayerWeights
void __thiscall Animated::initializeLayerWeights(float weight1, float weight2, float weight3, float weight4, float weight5)
{
    // Struct offsets (relative to this):
    // +0x4c: uint32 m_flags (bitfield)
    // +0xa0: float m_weightLayer0
    // +0xa4: byte m_activeLayer0
    // +0xb0: float m_weightLayer1
    // +0xb4: byte m_activeLayer1
    // +0xc0: float m_weightLayer2
    // +0xc4: byte m_activeLayer2
    // +0xd0: float m_weightLayer3
    // +0xd4: byte m_activeLayer3
    // +0xe0: float m_weightLayer4
    // +0xe4: byte m_activeLayer4

    this->m_weightLayer0 = weight1;
    this->m_weightLayer2 = weight3;
    this->m_weightLayer1 = weight2;
    this->m_weightLayer4 = weight5;
    this->m_weightLayer3 = weight4;

    // Zero out active flags for all layers (disable them)
    this->m_activeLayer0 = 0;
    this->m_activeLayer1 = 0;
    this->m_activeLayer2 = 0;
    this->m_activeLayer3 = 0;
    this->m_activeLayer4 = 0;

    // Clear bit 3 (value 0x8) in the flags field – possibly indicating "weights dirty" or "layers active"
    this->m_flags &= 0xfffffff7;
}