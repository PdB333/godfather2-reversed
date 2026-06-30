// FUNC_NAME: EARS::Stream::getDataBuffer
uint Stream::getDataBuffer(Stream *this) {
    uint returnData;
    
    if (*(char *)((int)&this->m_bOpen + -0x28) != '\0') {
        returnData = 0;
        if (*(char *)((int)&this->m_bFlag + -0x20) != '\0') {
            returnData = 0x3000;
        }
        // Virtual call to get internal data pointer or buffer
        (**(code **)(*(int *)this->vtable + 0x2c))(this, 0, 0, &this->m_pData1, returnData);
        return this->m_pData1;
    }
    *(char *)((int)&this->m_bOpen + -0x17) = 1;  // Sets a flag indicating data was accessed
    return this->m_pData2;
}