// FUNC_NAME: SomeClass::deserializeProperties
void __thiscall SomeClass::deserializeProperties(void* thisPtr, StreamReader* stream) {
    float fVar1;
    char isFinished;
    int propertyType;
    
    StreamReader::init(stream, 0x83c382cf); // Initialize stream with magic number
    isFinished = StreamReader::isFinished(stream);
    while (isFinished == 0) {
        StreamReader::readNext(stream); // Advance to next property? Or read property header
        propertyType = StreamReader::getPropertyType(stream);
        if (propertyType == 0) {
            // Type 0: float property
            StreamReader::readNext(stream); // Actually reads the value?
            float* valuePtr = (float*)(stream + 8);
            *(float*)(thisPtr + 0x10) = *valuePtr;
            if (*valuePtr < 0.0f) {
                *(float*)(thisPtr + 0x10) = 0.0f;
            }
        }
        else if (propertyType == 1) {
            // Type 1: uint32 property
            StreamReader::readNext(stream);
            *(uint32_t*)(thisPtr + 0x69c) = *(uint32_t*)(stream + 8);
        }
        else if (propertyType == 2) {
            // Type 2: some substructure at offset 0x67c
            void* substruct = (void*)(thisPtr + 0x67c);
            StreamReader::readNext(substruct); // Read into the substructure
            // Some processing on the substructure
            StreamReader::processSubstruct(substruct);
        }
        StreamReader::advance(stream);
        isFinished = StreamReader::isFinished(stream);
    }
    return;
}