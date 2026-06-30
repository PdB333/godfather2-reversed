// FUNC_NAME: ObjectHandle::setDataField
// Address: 0x004df8b0 - Sets an integer field at offset 0x84 of the object pointed to by the handle.
class ObjectHandle {
public:
    void* m_pObject; // +0x00: pointer to the underlying object

    void __thiscall setDataField(unsigned int value) {
        if (m_pObject != nullptr) {
            *(unsigned int*)((char*)m_pObject + 0x84) = value;
        }
    }
};