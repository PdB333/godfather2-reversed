// FUNC_NAME: SimManager::reset
void __thiscall SimManager::reset(SimManager* this, int aFlag) {
    int iVar;
    int count;

    if (aFlag != 0) {
        this->clearAllObjects(); // FUN_008c6ab0(this)
    }
    if (this->m_extraPtr != 0) { // +0xc0
        this->releaseHashTable(this->m_typeId); // FUN_0084a730(this->m_typeId)
    }
    this->m_state = 0; // +0x74
    this->someUpdate(); // FUN_006b2f70

    if (this->m_useArrayFlag == 0) { // +0x78
        // Loop using simple count
        for (count = this->m_count; count != 0; count--) {
            this->removeObject(0); // FUN_006b5c50(0)
        }
    } else {
        // Loop using dynamic array
        for (iVar = this->m_arrayCount - 1; iVar >= 0; iVar--) { // +0xac
            int objId = this->m_objectArray[iVar]; // +0xa8 (array of ints)
            char isActive = this->isObjectActive(); // FUN_00791230
            if (isActive == 0) {
                this->removeObjectByIndex(iVar); // FUN_006b56a0(iVar)
            } else {
                this->removeObject(objId); // FUN_006b5c50(objId)
            }
        }
    }

    this->m_currentIndex = 0; // +0x6c
    this->someUpdate(); // FUN_006b2f70

    int oldId = this->m_typeId; // +0x40
    this->m_oldId = oldId; // +0x3c
    this->m_typeId = 0; // +0x40
    if (oldId == 0x637b907) { // Hash/type constant
        if (this->m_subType == 0) { // +0xc4
            int data = this->getDataFromType0(this->m_dataSource); // FUN_0084b430(this->m_dataSource +0x38)
            this->m_baseValue = *(int*)(data + 0x14); // +0x60
        } else if (this->m_subType == 1) {
            int data = this->getDataFromType1(this->m_dataSource); // FUN_0084b400(this->m_dataSource +0x38)
            this->m_baseValue = *(int*)(data + 0x18); // +0x60
        }
    }
    this->m_currentIndex = this->m_baseValue; // +0x6c = +0x60
    this->m_currentValue = this->m_baseValue; // +0x58 = +0x60
    this->m_count = 0; // +0x68
    this->m_otherCount = 0; // +0x80
    this->m_timestamp = 0; // +0xcc
    this->m_flags &= 0xf7ffffff; // +0x34 clear bit 27 (0x08000000)
}