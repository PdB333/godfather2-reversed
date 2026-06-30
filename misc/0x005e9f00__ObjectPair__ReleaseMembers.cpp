// FUNC_NAME: ObjectPair::ReleaseMembers

void __thiscall ObjectPair::ReleaseMembers() {
    // +0x08: first pointer member (m_pObject1)
    // +0x14: second pointer member (m_pObject2)
    if (m_pObject1 != nullptr) {
        ReleaseObject(m_pObject1);  // Free/release resource at 0x009c8f10
    }
    if (m_pObject2 != nullptr) {
        ReleaseObject(m_pObject2);
    }
}