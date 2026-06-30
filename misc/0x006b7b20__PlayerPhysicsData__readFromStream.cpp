// FUNC_NAME: PlayerPhysicsData::readFromStream

void __thiscall PlayerPhysicsData::readFromStream(InputStream *stream) {
    bool bVar1 = false;               // Tracks if the speed field was zero/negative

    stream->beginRead();               // Start reading from stream
    stream->beginChunk(0xF3244A61);    // Read chunk header (probably a chunk of physics data)

    while (!stream->isChunkEnd()) {
        stream->advance();             // Move to next field in chunk
        DataNode *node = stream->readNext();  // Read the next field node
        int nodeType = node->getType(); // 0 = int, 1 = float

        if (nodeType == 0) {
            // Field storing an integer (e.g., collision flags or something at +0x60)
            this->field_0x60 = node->getUint32();
        } else if (nodeType == 1) {
            // Field storing a float (speed) – square it and store at +0x5c
            float speed = node->getFloat();
            if (speed <= 0.0f) {
                bVar1 = true;  // Remember if speed was zero/negative
            }
            this->field_0x5c = speed * speed;
        }
    }

    // Begin reading a second chunk (likely velocity/force data)
    stream->beginChunk(0xB390B11A);
    stream->readInt(1);                // Read an extra integer (e.g., sub-chunk size or flag)

    if (!stream->isChunkEnd()) {
        // Read a 3D vector into local stack (velocity, force, or something)
        Vector3 vec;
        float initVal = _DAT_00d5780c; // Global constant (e.g., gravity or wind component)
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = 0.0f;

        stream->readNext(&vec);        // Read vector components from stream
        stream->processVector(&vec);   // Possibly transform or normalize the vector

        if (bVar1) {
            // If previous speed was zero/negative, compute a scaled magnitude
            float magnitude = fsqrte(vec.x * vec.x + _DAT_00d577a0 + vec.y * vec.y + vec.z * vec.z);
            float scaled = magnitude * _DAT_00d5c458; // Global multiplier
            this->field_0x5c = scaled * scaled;       // Store squared scaled magnitude
        }

        // Read two more values from the stream (legacy data – e.g., 8+4 bytes)
        // These are stored at offsets +0x50 and +0x58
        this->field_0x50 = stream->readUint64();  // 8 bytes (maybe quaternion part)
        this->field_0x58 = stream->readUint32();  // 4 bytes (e.g., extra float)
    }
}