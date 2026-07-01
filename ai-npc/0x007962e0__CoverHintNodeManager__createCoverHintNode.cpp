// FUNC_NAME: CoverHintNodeManager::createCoverHintNode
void __thiscall createCoverHintNode(uint arg0, uint arg1, uint arg2) {
    char ready;
    int * pObj;

    ready = EARS::Framework::SimManager::isSystemInitialized(); // 0x00481640
    if (ready != '\0') {
        pObj = (int *)EARS::Framework::Memory::allocate(0x40); // 0x009c8e50
        if (pObj == (int *)0x0) {
            pObj = (int *)0x0;
        }
        else {
            pObj = (int *)EARS::Modules::CoverHintNode::initialize(pObj, arg0); // 0x00795010
        }
        pObj[0x38 / 4] = (int)arg1; // +0x38: coverDirection or animation index
        pObj[0x3c / 4] = (int)arg2; // +0x3c: coverDistance or flags
        EARS::Framework::SimManager::registerObject(pObj); // 0x00481690
    }
    return;
}