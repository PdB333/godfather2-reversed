// FUNC_NAME: Entity::loadStatBlock
void __thiscall Entity::loadStatBlock(DataStream* stream)
{
    // Begin parsing the stream
    stream->beginParse();
    // Enter the "STAT" node (CRC32: 0xb390b11a)
    stream->beginNode(0xb390b11a);
    // Set parsing flag (maybe indicating we expect child nodes)
    stream->setParseFlag(1);
    // Enter the data block (CRC32: 0x5ade71cd)
    stream->beginNode(0x5ade71cd);

    // Loop while there are more child nodes (e.g., value elements)
    while (!stream->isEndOfChildren()) {
        // Get the type of the next child (0, 1, or 2)
        int childType = stream->getNextChildType();
        if (childType == 0) {
            // Read the value node and store the int at offset +0x8 into this+0x1b0
            DataNode* valueNode = stream->readValueNode();
            *(int*)(this + 0x1b0) = *(int*)(valueNode + 0x8);
        }
        else if (childType == 1) {
            // Store into this+0x1b4
            DataNode* valueNode = stream->readValueNode();
            *(int*)(this + 0x1b4) = *(int*)(valueNode + 0x8);
        }
        else if (childType == 2) {
            // Store into this+0x1b8
            DataNode* valueNode = stream->readValueNode();
            *(int*)(this + 0x1b8) = *(int*)(valueNode + 0x8);
        }
        // Advance to the next sibling node
        stream->endChildNode();
    }
}