// FUNC_NAME: PropertyDeserializer::readProperties
// Function address: 0x006be5f0
// Reads a stream of property-value pairs and populates the object's fields.
// Fields: +0x50 (property0), +0x54 (property1), +0x58 (stringProperty0), +0x60 (intOrFloatProperty2), +0x68 (intOrFloatProperty3)
// Stream format: magic, then loop of property ID + data until end condition.

void __thiscall PropertyDeserializer::readProperties(void* thisObj, StreamReader* stream)
{
    // Initialize the stream for reading
    stream->beginRead();
    // Validate the stream magic/signature
    stream->readSignature(0x34deb5cb);

    bool isDone = stream->isFinished();
    do {
        if (isDone) {
            return;
        }
        // Read a dummy value (maybe terminator or alignment)
        stream->readNextValue();
        // Read the property identifier
        int propId = stream->readPropertyId();

        switch (propId) {
        case 0:
        {
            // Property 0: read from a lookup table at offset +0x50
            int tableEntry = stream->readTableIndex();
            *(int*)((char*)thisObj + 0x50) = *(int*)(tableEntry + 8);
            break;
        }
        case 1:
        {
            // Property 1: similar, offset +0x54
            int tableEntry = stream->readTableIndex();
            *(int*)((char*)thisObj + 0x54) = *(int*)(tableEntry + 8);
            break;
        }
        case 2:
        {
            // Property 2: string property at +0x58
            stream->readNextValue(); // skip padding?
            void* stringHandle = stream->readStringHandle();
            assignStringProperty((char*)thisObj + 0x58, stringHandle);
            break;
        }
        case 3:
        {
            // Property 3: integer/vector property at +0x60 (falls through to case 4 handler)
            stream->readNextValue();
            void* valHandle = stream->readStringHandle();
            assignIntOrVectorProperty((char*)thisObj + 0x60, valHandle);
            break;
        }
        case 4:
        {
            // Property 4: integer/vector property at +0x68
            stream->readNextValue();
            void* valHandle = stream->readStringHandle();
            assignIntOrVectorProperty((char*)thisObj + 0x68, valHandle);
            break;
        }
        default:
            break;
        }

        // Advance to the next property in the stream
        stream->advanceToNextProperty();
        isDone = stream->isFinished();
    } while (true);
}