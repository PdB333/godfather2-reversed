// FUNC_NAME: PointerHolder::setPointer
// Address: 0x006f0c20
// Role: Sets a member pointer to a new child object. Releases the previous child (if any) via FUN_004daf90,
// and updates the child's back-pointer (at offset +0x04) to point to the parent's slot. The old back-pointer
// is saved at the parent's offset +0x10.

class PointerHolder {
public:
    int* m_pChild;           // +0x0C: Pointer to the managed child object
    int m_preservedBackPtr;  // +0x10: Saved back-pointer from the previous child (used for cleanup)
    // Other fields (vtable, etc.) not shown
};

void __thiscall PointerHolder::setPointer(int* newChild) {
    if (m_pChild == newChild) {
        return;
    }
    if (m_pChild != nullptr) {
        FUN_004daf90(&m_pChild);          // Release old child (frees and detaches)
    }
    m_pChild = newChild;
    if (newChild != nullptr) {
        // Save the child's current back-pointer (offset +0x04) into this->m_preservedBackPtr
        m_preservedBackPtr = *reinterpret_cast<int*>(reinterpret_cast<char*>(newChild) + 4);
        // Redirect the child's back-pointer to point to this parent's m_pChild field
        *reinterpret_cast<int**>(reinterpret_cast<char*>(newChild) + 4) = &m_pChild;
    }
}