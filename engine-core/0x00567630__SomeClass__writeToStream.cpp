// FUNC_NAME: SomeClass::writeToStream
// Address: 0x00567630
// Role: Writes serialized data from a child object into a stream using a temporary buffer.

class ChildObject {
public:
    virtual void writeToBuffer(char* buffer) = 0; // vtable offset 0x54
};

class SomeClass {
public:
    ChildObject* m_childObject; // +0x0C

    void writeToStream(void* stream);
};

// Forward declarations of external helper functions
void streamBeginWrite(void* stream, int arg1, int arg2, int arg3); // 0x00b11f90
void streamEndWrite(); // 0x00b11fe0

void SomeClass::writeToStream(void* stream) {
    char buffer[76]; // temporary serialization buffer

    if (m_childObject != nullptr) {
        streamBeginWrite(stream, 0, 0, 0);
        m_childObject->writeToBuffer(buffer);
        streamEndWrite();
    }
}