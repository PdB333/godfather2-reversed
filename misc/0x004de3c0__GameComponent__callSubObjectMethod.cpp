// FUNC_NAME: GameComponent::callSubObjectMethod
// Address: 0x004de3c0
// Role: Calls the first virtual function on a sub-object interface, passing a stack buffer.
// The virtual function is expected to fill the buffer (3 ints), but the result is not used here.
// This likely serves as a generic dispatch or query wrapper.

struct DataBuffer {
    int data[3];
};

class IDataProvider {
public:
    // +0x00: vtable
    // index 0: virtual void getData(int param, DataBuffer* out)
    virtual void getData(int param, DataBuffer* out) = 0;
};

class GameComponent {
    // +0x00: vtable (if any)
    // +0x04: pointer to sub-object interface
    IDataProvider* m_pSubObject;

public:
    void callSubObjectMethod(int param);
};

void GameComponent::callSubObjectMethod(int param) {
    if (m_pSubObject != nullptr) {
        DataBuffer buffer = {}; // zero-initialized stack buffer
        m_pSubObject->getData(param, &buffer);
        // buffer is not used further; side-effect only
    }
}