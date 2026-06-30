// FUNC_NAME: AICharacter::setTargetID
void AICharacter::setTargetID(int id) {
    // this->m_target (offset +0x58) points to target data
    // Setting field at offset +0x34 within target data (target ID)
    m_target->targetId = id;
}