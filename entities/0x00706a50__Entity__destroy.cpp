// FUNC_NAME: Entity::destroy
void __thiscall Entity::destroy(bool bDelete)
{
    if (this->m_pSomePointer != nullptr) {
        this->m_bDestroyedFlag = false;
        sendDestroyEvent(0x5beea32a,
                         this->m_pSomePointer,
                         this->m_nSomeId,
                         1);
        if ((bDelete) && (this->m_pSomePointer != nullptr)) {
            operatorDelete(this->m_pSomePointer);
            this->m_pSomePointer = nullptr;
            this->m_nSomeId = 0;
        }
    }
}