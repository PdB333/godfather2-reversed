// FUNC_NAME: SubComponentManager::releaseComponents
void SubComponentManager::releaseComponents() {
    // Release first subcomponent
    if (m_pObj1 != nullptr) {
        // Call release method (vtable offset 4) on component1 interface with obj1 and 0
        void (*releaseFunc)(void*, int) = reinterpret_cast<void (*)(void*, int)>(*(int*)m_pInterface1 + 4);
        releaseFunc(m_pObj1, 0);
        m_pObj1 = nullptr;
    }
    // Call shutdown method (vtable offset 12) on component1 interface
    void (*shutdownFunc)() = reinterpret_cast<void (*)()>(*(int*)m_pInterface1 + 12);
    shutdownFunc();

    // Release second subcomponent
    if (m_pObj2 != nullptr) {
        void (*releaseFunc2)(void*, int) = reinterpret_cast<void (*)(void*, int)>(*(int*)m_pInterface2 + 4);
        releaseFunc2(m_pObj2, 0);
        m_pObj2 = nullptr;
    }
    // Call shutdown method on component2 interface
    void (*shutdownFunc2)() = reinterpret_cast<void (*)()>(*(int*)m_pInterface2 + 12);
    shutdownFunc2();
}