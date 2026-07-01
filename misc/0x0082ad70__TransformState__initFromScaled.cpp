// FUNC_NAME: TransformState::initFromScaled

void * TransformState::initFromScaled(TransformState *this, TransformState *source, float scale)
{
    FUN_0081f9f0(source); // likely some validation or initialization of source
    this->vtable = &PTR_LAB_00d736c0; // set vtable

    // Copy 7 floats from source at offset +0x4c into this at same offset
    // Structure layout (offsets from this):
    // +0x4c: float m_posX
    // +0x50: float m_posY
    // +0x54: float m_posZ
    // +0x58: (skipped, possibly padding or unused)
    // +0x5c: (skipped)
    // +0x60: float m_quatX
    // +0x64: float m_quatY
    // +0x68: float m_quatZ
    // +0x6c: float m_quatW
    this->m_posX = source->m_posX;
    this->m_posY = source->m_posY;
    this->m_posZ = source->m_posZ;
    this->m_quatX = source->m_quatX;
    this->m_quatY = source->m_quatY;
    this->m_quatZ = source->m_quatZ;
    this->m_quatW = source->m_quatW;

    // Scale all components by factor
    this->m_posX *= scale;
    this->m_posY *= scale;
    this->m_posZ *= scale;
    this->m_quatX *= scale;
    this->m_quatY *= scale;
    this->m_quatZ *= scale;
    this->m_quatW *= scale;

    return this;
}