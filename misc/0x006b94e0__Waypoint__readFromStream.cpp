// FUNC_NAME: Waypoint::readFromStream
void __thiscall Waypoint::readFromStream(StreamReader* stream) {
    stream->beginRead();                       // FUN_0046c710
    stream->readVersion(0xdfb961e);             // FUN_0043aff0

    while (!stream->isEnd()) {                  // FUN_0043b120
        stream->enterNode();                    // FUN_0043b210
        uint32_t nodeType = stream->readNodeType(); // FUN_0043ab70

        switch (nodeType) {
            case 0: {
                // Read position/rotation (4 floats at +0x54..+0x60)
                stream->enterNode();            // FUN_0043b210
                float* vec = stream->readVector4(); // FUN_0043abc0 (returns pointer to 4 floats)
                this->posX = vec[0];            // +0x54
                this->posY = vec[1];            // +0x58
                this->posZ = vec[2];            // +0x5c
                this->posW = vec[3];            // +0x60
                break;
            }
            case 1: {
                // Read an integer ID / type at +0x50
                uint32_t objHandle = stream->enterNode(); // FUN_0043b210
                this->type = *(uint32_t*)(objHandle + 8); // +0x50
                break;
            }
            case 2: {
                // Read a string name (hashed or ID) into +0x64
                stream->enterNode();            // FUN_0043b210
                uint32_t stringId = stream->readStringID(); // FUN_0043ab90
                stream->setNameAt(this + 0x64, stringId);   // FUN_004089b0 (likely sets a string member)
                break;
            }
            case 3: {
                // Read a value at +0x6c
                uint32_t objHandle = stream->enterNode(); // FUN_0043b210
                this->data1 = *(uint32_t*)(objHandle + 8); // +0x6c
                break;
            }
            case 4: {
                // Read a value at +0x70
                uint32_t objHandle = stream->enterNode(); // FUN_0043b210
                this->data2 = *(uint32_t*)(objHandle + 8); // +0x70
                break;
            }
        }
        stream->leaveNode();                    // FUN_0043b1a0
    }
}