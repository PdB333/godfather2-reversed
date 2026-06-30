// FUNC_NAME: SomeClass::accumulateValues
void SomeClass::accumulateValues() {
    int i;
    // +0x28: m_numElements (number of elements to sum)
    // +0x38: m_accumulatedSum (running total)
    if (this->m_numElements > 0) {
        for (i = 0; i < this->m_numElements; i++) {
            this->m_accumulatedSum += getNextElementValue();
        }
    }
}