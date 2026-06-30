// FUNC_NAME: SerializableData::serialize
void __thiscall SerializableData::serialize(DataStream* stream) {
    // Stream is passed in EAX, but we handle via parameter (convention workaround)
    // This function serializes two dynamic arrays from 'this'.
    // Offsets: +0x08 = TaggedValue array (8-byte entries: first int tag, second int value)
    //          +0x28 = count of tagged values
    //          +0x10 = pointer array (4-byte pointers)
    //          +0x34 = count of pointers
    //          +0x20 = some context pointer used by child serialization

    // Step 1: serialize the tagged value array
    int valueCount = *(int*)(this + 0x28);
    stream->writeInt(&valueCount, 4);  // offset? actually writes int via stream method

    for (int i = 0; i < valueCount; ++i) {
        TaggedValue* val = (TaggedValue*)(*(int*)(this + 0x08) + i * sizeof(TaggedValue));
        // Write first byte (low byte of tag)
        stream->writeByte((char)val->tag);
        if (val->tag == 3) {
            // Write the associated value as int
            stream->writeInt(&val->value, 4);
        } else if (val->tag == 4) {
            // Special case: call separate serialization for tag 4
            serializeTag4Value(/*context?*/);
        }
    }

    // Step 2: serialize the pointer array
    int ptrCount = *(int*)(this + 0x34);
    stream->writeInt(&ptrCount, 4);
    for (int i = 0; i < ptrCount; ++i) {
        void* obj = *(void**)(*(int*)(this + 0x10) + i * 4);
        serializePointer(obj, /*context from +0x20*/);
    }
}