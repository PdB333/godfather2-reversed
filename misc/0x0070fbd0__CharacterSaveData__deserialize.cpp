// FUNC_NAME: CharacterSaveData::deserialize
void __thiscall CharacterSaveData::deserialize(GameDataStream& stream) {
    // Begin deserialization of a data stream chunk
    stream.beginDeserialize();
    stream.beginChunk(0xa0294054); // chunk hash identifier

    // Main parsing loop: while there are more elements
    while (!stream.hasMoreElements()) {
        stream.beginAttribute(); // read next attribute header
        int tag = stream.readTag();

        switch (tag) {
        case 0: {
            // Read string for field at offset 0x50 (e.g., firstName)
            stream.beginAttribute(); // attribute for the string
            const char* str = stream.readString();
            setStringField(this + 0x50, str); // +0x50 : char* or String
            break;
        }
        case 1: {
            // Read string for field at offset 0x58 (e.g., lastName)
            stream.beginAttribute();
            const char* str = stream.readString();
            setStringField(this + 0x58, str); // +0x58
            break;
        }
        case 2: {
            // Read integer directly into field at offset 0x60 (e.g., health)
            int* field = (int*)(this + 0x60);
            stream.readField(field); // reads scalar directly into memory
            break;
        }
        case 3: {
            // Read string, convert to hash, store at 0x70
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x70) = hashFromString(str); // +0x70 : hash
            break;
        }
        case 4: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x74) = hashFromString(str); // +0x74
            break;
        }
        case 5: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x78) = hashFromString(str); // +0x78
            break;
        }
        case 6: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x80) = hashFromString(str); // +0x80
            break;
        }
        case 7: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x7c) = hashFromString(str); // +0x7c
            break;
        }
        case 8: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x88) = hashFromString(str); // +0x88
            break;
        }
        case 9: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x8c) = hashFromString(str); // +0x8c
            break;
        }
        case 10: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x90) = hashFromString(str); // +0x90
            break;
        }
        case 11: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x94) = hashFromString(str); // +0x94
            break;
        }
        case 12: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x84) = hashFromString(str); // +0x84
            break;
        }
        case 13: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x98) = hashFromString(str); // +0x98
            break;
        }
        case 14: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0x9c) = hashFromString(str); // +0x9c
            break;
        }
        case 15: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0xa0) = hashFromString(str); // +0xa0
            break;
        }
        case 16: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0xa4) = hashFromString(str); // +0xa4
            break;
        }
        case 17: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0xa8) = hashFromString(str); // +0xa8
            break;
        }
        case 18: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0xac) = hashFromString(str); // +0xac
            break;
        }
        case 19: {
            stream.beginAttribute();
            const char* str = stream.readString();
            *(int*)(this + 0xb0) = hashFromString(str); // +0xb0
            break;
        }
        case 0x14: {
            // Read Vector4 (4 floats) into fields at 0xb4-0xc0
            stream.beginAttribute();
            float* vec = stream.readVector4();
            *(float*)(this + 0xb4) = vec[0]; // +0x94: x
            *(float*)(this + 0xb8) = vec[1]; // +0x98: y
            *(float*)(this + 0xbc) = vec[2]; // +0x9c: z
            *(float*)(this + 0xc0) = vec[3]; // +0xa0: w
            break;
        }
        case 0x15: {
            stream.beginAttribute();
            float* vec = stream.readVector4();
            *(float*)(this + 0xc4) = vec[0]; // +0xc4
            *(float*)(this + 0xc8) = vec[1]; // +0xc8
            *(float*)(this + 0xcc) = vec[2]; // +0xcc
            *(float*)(this + 0xd0) = vec[3]; // +0xd0
            break;
        }
        case 0x16: {
            stream.beginAttribute();
            float* vec = stream.readVector4();
            *(float*)(this + 0xd4) = vec[0];
            *(float*)(this + 0xd8) = vec[1];
            *(float*)(this + 0xdc) = vec[2];
            *(float*)(this + 0xe0) = vec[3];
            break;
        }
        case 0x17: {
            stream.beginAttribute();
            float* vec = stream.readVector4();
            *(float*)(this + 0xe4) = vec[0];
            *(float*)(this + 0xe8) = vec[1];
            *(float*)(this + 0xec) = vec[2];
            *(float*)(this + 0xf0) = vec[3];
            break;
        }
        case 0x18: {
            stream.beginAttribute();
            float* vec = stream.readVector4();
            *(float*)(this + 0xf4) = vec[0];
            *(float*)(this + 0xf8) = vec[1];
            *(float*)(this + 0xfc) = vec[2];
            *(float*)(this + 0x100) = vec[3];
            break;
        }
        case 0x19: {
            // Read a string pointer directly from attribute structure (offset 8)
            int attrPtr = stream.readAttribute(); // returns pointer to attribute data
            *(int*)(this + 0x108) = *(int*)(attrPtr + 8); // +0x108: char* (string reference)
            break;
        }
        case 0x1a: {
            // Read string, compute hash, store at 0x104
            int attrPtr = stream.readAttribute();
            const char* str = *(const char**)(attrPtr + 8);
            *(int*)(this + 0x104) = hashFromString(str); // +0x104
            break;
        }
        case 0x1b: {
            // Read a string and pass to a separate function (e.g., add to dictionary)
            stream.beginAttribute();
            const char* str = stream.readString();
            processString(str); // process the string
            break;
        }
        case 0x1c: {
            // Read a string pointer directly into 0x11c
            int attrPtr = stream.readAttribute();
            *(int*)(this + 0x11c) = *(int*)(attrPtr + 8); // +0x11c
            break;
        }
        }
        stream.endAttribute();
    }
}