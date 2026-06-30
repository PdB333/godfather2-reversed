// FUNC_NAME: GameObject::readFromStream

class Stream {
public:
    void beginRead();
    void setMagic(unsigned int magic);
    bool isEndOfStream();
    void* readObject(void* dest = nullptr); // if dest is null, allocates and returns pointer; else reads into dest and returns dest
    int readClassID(); // actually reads int
    int readUint32(); // reads uint32
    void readElement(void* obj); // reads sub-element into obj
    void readEnd();
};

class GameObject {
public:
    void readFromStream(Stream* stream);

private:
    // Member offsets based on decompilation:
    int field_0x50;      // +0x50
    void* field_0x58;    // +0x58
    void* field_0x68;    // +0x68
    void* field_0x78;    // +0x78
    int field_0x88;      // +0x88 (stored from read object +8)
};

void GameObject::readFromStream(Stream* stream)
{
    stream->beginRead();
    stream->setMagic(0xa4272fd9);

    while (!stream->isEndOfStream())
    {
        int classID = stream->readClassID();

        switch (classID)
        {
        case 0:
        {
            int value = stream->readUint32();
            field_0x50 = value; // set some field at +0x50
            break;
        }
        case 1:
        {
            void* obj = stream->readObject(reinterpret_cast<void*>(&field_0x58));
            stream->readElement(obj); // reads subobject into field_0x58
            break;
        }
        case 2:
        {
            void* obj = stream->readObject(); // allocates and returns pointer
            field_0x88 = *(int*)(static_cast<char*>(obj) + 8); // store value from obj+8
            break;
        }
        case 3:
        {
            void* obj = stream->readObject(reinterpret_cast<void*>(&field_0x68));
            stream->readElement(obj);
            break;
        }
        case 4:
        {
            void* obj = stream->readObject(reinterpret_cast<void*>(&field_0x78));
            stream->readElement(obj);
            break;
        }
        }

        stream->readEnd();
    }
}