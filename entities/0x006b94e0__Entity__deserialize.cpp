// FUNC_NAME: Entity::deserialize
void __thiscall Entity::deserialize(Entity* this, BinaryArchive& archive)
{
    archive.beginRead(archive); // FUN_0046c710
    archive.readHeader(0xdfb961e); // FUN_0043aff0

    while (!archive.isEOF()) // FUN_0043b120
    {
        archive.nextToken(); // FUN_0043b210
        int tokenType = archive.getTokenType(); // FUN_0043ab70

        switch (tokenType)
        {
        case 0: // Vector4
        {
            archive.nextToken(); // skip marker
            float* vec = archive.readVector4(); // FUN_0043abc0
            this->field_0x54 = vec[0]; // +0x54: x
            this->field_0x58 = vec[1]; // +0x58: y
            this->field_0x5C = vec[2]; // +0x5C: z
            this->field_0x60 = vec[3]; // +0x60: w
            break;
        }
        case 1: // Float
        {
            int token = archive.nextToken(); // returns token handle?
            this->field_0x50 = *(float*)(token + 8); // +0x50
            break;
        }
        case 2: // String
        {
            archive.nextToken();
            const char* str = archive.readString(); // FUN_0043ab90
            archive.copyString(this->field_0x64, str); // +100 (0x64) string buffer
            break;
        }
        case 3: // Float
        {
            int token = archive.nextToken();
            this->field_0x6C = *(float*)(token + 8); // +0x6C
            break;
        }
        case 4: // Float
        {
            int token = archive.nextToken();
            this->field_0x70 = *(float*)(token + 8); // +0x70
            break;
        }
        }
        archive.nextField(); // FUN_0043b1a0
    }
}