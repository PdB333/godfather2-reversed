// FUNC_NAME: ParameterBlock::loadFromStream
void __thiscall ParameterBlock::loadFromStream(Stream& stream)
{
    // Initialize stream with magic tag 0xf550a64f
    stream.readBegin(0xf550a64f);
    // Read until end of stream
    while (stream.hasMore())
    {
        // Read field identifier (tag)
        int fieldId = stream.readFieldId(); // corresponds to FUN_0043ab70
        // Read value node (contains data at offset +0x08)
        Node* valueNode = stream.readNode(); // corresponds to FUN_0043b210
        switch (fieldId)
        {
        case 0: // field0: int at offset 0x00
            this->field0 = valueNode->getValue32(); // int32 value at node+0x08
            break;
        case 1: // field1: int at offset 0x04
            this->field1 = valueNode->getValue32();
            break;
        case 2: // field2: int at offset 0x08
            this->field2 = valueNode->getValue32();
            break;
        case 3: // field3: int at offset 0x0C
            this->field3 = valueNode->getValue32();
            break;
        case 4: // field4: int at offset 0x10
            this->field4 = valueNode->getValue32();
            break;
        case 5: // field5: int at offset 0x14
            this->field5 = valueNode->getValue32();
            break;
        case 6: // field6: int at offset 0x18
            this->field6 = valueNode->getValue32();
            break;
        case 7: // field7: int at offset 0x1C
            this->field7 = valueNode->getValue32();
            break;
        case 8: // field8: int at offset 0x20
            this->field8 = valueNode->getValue32();
            break;
        case 9: // field9: int at offset 0x24
            this->field9 = valueNode->getValue32();
            break;
        case 10: // field10: int at offset 0x28
            this->field10 = valueNode->getValue32();
            break;
        case 11: // byte at offset 0x2C (field11)
            this->byte0 = (uint8)valueNode->getValue32();
            break;
        case 12: // byte at offset 0x2D (field12)
            this->byte1 = (uint8)valueNode->getValue32();
            break;
        case 13: // byte at offset 0x2E (field13)
            this->byte2 = (uint8)valueNode->getValue32();
            break;
        case 14: // byte at offset 0x2F (field14)
            this->byte3 = (uint8)valueNode->getValue32();
            break;
        case 16: // Array index 16 - starts a sub-field
        case 17: // Array index 17
        case 18: // Array index 18
        case 19: // Array index 19
        {
            // Read inner field identifier (determines which array element to set)
            int innerFieldId = stream.readFieldId(); // corresponds to FUN_0043ab70
            Node* innerValueNode = stream.readNode(); // corresponds to FUN_0043b210
            // Compute array index: 0x20 - innerFieldId maps to indices 0x10,0x0F,0x0E,0x0D
            int arrayIndex = 0x20 - innerFieldId; // yields index in range [0x0D,0x10]
            // Write int at the computed offset (array of ints starting at offset 0x34?)
            ((int32*)this)[arrayIndex] = innerValueNode->getValue32();
            break;
        }
        default:
            // Unknown field; skip
            break;
        }
        stream.readEnd(); // corresponds to FUN_0043b1a0
    }
}