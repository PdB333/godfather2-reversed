// FUNC_NAME: TNLConnection::getNextSequenceNumber
int __thiscall TNLConnection::getNextSequenceNumber(TNLConnection* this) {
    // +0x24: sequence number (uint32), incremented and returned
    this->mSequenceNumber += 1;
    return this->mSequenceNumber;
}