// FUNC_NAME: Component::GetContainer
class Component {
public:
    // Returns the container object that owns this component.
    // The container has the component embedded at offset 0x48.
    void* GetContainer() const {
        if (m_pContainerPtr != nullptr) {
            return reinterpret_cast<void*>(reinterpret_cast<char*>(m_pContainerPtr) - 0x48);
        }
        return nullptr;
    }

private:
    // +0x9c: Pointer to a member inside the container (located at container+0x48)
    void* m_pContainerPtr;
};