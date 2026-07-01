// FUNC_NAME: Entity::loadFromStream

void __thiscall Entity::loadFromStream(void* this, DataStream* stream)
{
    char isStreamEnd;
    uint dataType;
    int handle;
    uint value;
    float time;

    stream->beginRead(); // thunk_FUN_008dab90 - initialize stream reading
    stream->readHeader(0x617f1a1b); // FUN_0043aff0 - verify magic number
    isStreamEnd = stream->isStreamEnd(); // FUN_0043b120 - returns 0 if more data
    while (isStreamEnd == 0) {
        stream->readHandle(); // FUN_0043b210 - read and discard a handle (possibly key/tag)
        dataType = stream->readDataType(); // FUN_0043ab70 - determine data type
        switch(dataType) {
        case 0:
            // Set field at +0x234 to the object referenced by the next handle
            handle = stream->readHandle(); // FUN_0043b210
            *(void**)((char*)this + 0x234) = *(void**)(handle + 8);
            break;
        case 1:
            // Set field at +0x238 to the object referenced by the next handle
            handle = stream->readHandle();
            *(void**)((char*)this + 0x238) = *(void**)(handle + 8);
            break;
        case 2:
            // Read a value and store at +0x248
            stream->readHandle(); // discard handle
            value = stream->readValue(); // FUN_0043ab90
            setFieldValue((char*)this + 0x248, value); // FUN_00408240
            break;
        case 3:
            // Read a value and store at +0x250
            stream->readHandle();
            value = stream->readValue();
            setFieldValue((char*)this + 0x250, value);
            break;
        case 4:
            // Read a value and store at +0x258 (600 decimal)
            stream->readHandle();
            value = stream->readValue();
            setFieldValue((char*)this + 0x258, value);
            break;
        case 5:
            // Read a string ID and store at +0x260
            stream->readHandle();
            value = stream->readValue();
            setFieldString((char*)this + 0x260, value); // FUN_004089b0
            break;
        case 6:
            // Create a child object and store at +0x240
            handle = stream->readHandle();
            *(void**)((char*)this + 0x240) = createObject(*(void**)(handle + 8), this, 0, 5, 0, 1, 1, 0, 2, 0, 0, 0, 0); // FUN_0094cc00
            postLoadCallback(); // FUN_008dfd20
            if (*(void**)((char*)this + 0x240) != 0) {
                initObject(*(void**)((char*)this + 0x240)); // FUN_00949dd0
                *(char*)((char*)this + 0x244) = 1; // set flag indicating object is active
            }
            break;
        }
        stream->advance(); // FUN_0043b1a0 - move to next data block
        isStreamEnd = stream->isStreamEnd();
    }
    time = getCurrentTime(); // FUN_008dab60 - get current game time
    setAnimationTime(*(void**)((char*)this + 0x234), time); // FUN_008de620 - set animation time on object at +0x234
}