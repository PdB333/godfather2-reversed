// FUNC_NAME: DataBlock::getDataPointer

class DataBlock {
public:
    int m_directData;       // +0x04: direct pointer to data, 0 if not used
    // +0x08, +0x0C: padding or other fields
    int m_bufferBase;       // +0x10: base address of a buffer; data starts at base+0x10 if direct data is null
};

int DataBlock::getDataPointer() {
    int result = this->m_directData;
    if (result == 0) {
        result = this->m_bufferBase + 0x10;
    }
    return result;
}