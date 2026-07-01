// FUNC_NAME: AudioStream::update
void __thiscall AudioStream::update(void)
{
    float invRate;
    int i;
    uint j;

    if (g_fGlobalTime < this->m_fThreshold) {
        invRate = 1.0f / this->m_fThreshold;
        processSubA(invRate);
        for (i = 0; i < this->m_iCountA; i++) {
            processSubA(invRate);
            processSubA(invRate);
        }
        for (j = 0; j < this->m_iCountB; j++) {
            processSubB(invRate);
        }
        for (int k = 0; k < 4; k++) {
            processSubB(invRate);
        }
        processSubB(invRate);
    }
}