// FUNC_NAME: EntityDataManager::loadEntitiesFromStream
void __thiscall EntityDataManager::loadEntitiesFromStream(EntityDataManager* this, Stream* stream)
{
    char isDone;
    uint token;
    int nodePtr;

    Stream::readString(stream); // skip header or version
    Stream::readUint32(stream, 0x634b8404); // magic number check

    isDone = Stream::isEndOfStream(stream);
    while (isDone == '\0') {
        Stream::readUint32(stream); // probably token length
        token = Stream::readUint32(stream);
        switch(token) {
        case 0: // entity creation token
            Stream::readUint32(stream); // skip length
            token = Stream::readUint32(stream); // entity type
            Entity::addToBelongsList(this->entities + 0x60, token); // +0x60 is entity list offset
            break;
        case 1: // some data block
            nodePtr = Stream::readUint32(stream);
            *(uint32_t*)(this + 0x50) = *(uint32_t*)(nodePtr + 8); // +0x50 is some field
            break;
        case 2:
            nodePtr = Stream::readUint32(stream);
            *(uint32_t*)(this + 0x54) = *(uint32_t*)(nodePtr + 8); // +0x54
            break;
        case 3:
            nodePtr = Stream::readUint32(stream);
            *(uint32_t*)(this + 0x58) = *(uint32_t*)(nodePtr + 8); // +0x58
            break;
        case 4:
            nodePtr = Stream::readUint32(stream);
            *(uint32_t*)(this + 0x5c) = *(uint32_t*)(nodePtr + 8); // +0x5c
        }
        Stream::readUint32(stream); // skip end token or similar
        isDone = Stream::isEndOfStream(stream);
    }
    return;
}