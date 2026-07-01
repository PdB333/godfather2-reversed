// FUNC_NAME: InterpolationData::parseFromStream
void __thiscall InterpolationData::parseFromStream(float param_2)
{
    float fVar1;
    bool bVar2;
    char cVar3;
    int uVar4;
    int iVar5;
    float fVar6;
    float fVar7;

    setTime(param_2, 0x2c710094);
    param_2 = 0.0f;
    cVar3 = isStreamEnd();
    fVar6 = g_currentTime;
    while (g_currentTime = fVar6, cVar3 == '\0')
    {
        nextStreamChunk();
        uVar4 = readCommandType();
        switch (uVar4)
        {
        case 0:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(0, uVar4);
            break;
        case 1:
            iVar5 = nextStreamChunk();
            iVar5 = *(int *)(iVar5 + 8);
            m_minIndex = iVar5;
            if (iVar5 < 0)
                m_minIndex = 0;
            break;
        case 2:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d5ef84;
            bVar2 = *(float *)(iVar5 + 8) <= DAT_00d5ef84;
            m_minValue1 = *(float *)(iVar5 + 8);
            if (bVar2)
                m_minValue1 = fVar6;
            break;
        case 3:
            iVar5 = nextStreamChunk();
            iVar5 = *(int *)(iVar5 + 8);
            m_maxIndex = iVar5;
            if (iVar5 < 0)
                m_maxIndex = 0;
            break;
        case 4:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d5ef84;
            bVar2 = *(float *)(iVar5 + 8) <= DAT_00d5ef84;
            m_maxValue1 = *(float *)(iVar5 + 8);
            if (bVar2)
                m_maxValue1 = fVar6;
            break;
        case 5:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(1, uVar4);
            break;
        case 6:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(2, uVar4);
            break;
        case 7:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(3, uVar4);
            break;
        case 8:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(4, uVar4);
            break;
        case 9:
            iVar5 = nextStreamChunk();
            fVar6 = *(float *)(iVar5 + 8);
            m_timeOffset = fVar6;
            if (fVar6 < 0.0f)
                m_timeOffset = 0;
            m_remainingTime = g_currentTime - m_timeOffset;
            break;
        case 10:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(5, uVar4);
            break;
        case 0xb:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d5ef84;
            bVar2 = *(float *)(iVar5 + 8) <= DAT_00d5ef84;
            m_minValue2 = *(float *)(iVar5 + 8);
            if (bVar2)
                m_minValue2 = fVar6;
            break;
        case 0xc:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d5ef84;
            bVar2 = *(float *)(iVar5 + 8) <= DAT_00d5ef84;
            m_maxValue2 = *(float *)(iVar5 + 8);
            if (bVar2)
                m_maxValue2 = fVar6;
            break;
        case 0xd:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d76300;
            if ((DAT_00d76300 < *(float *)(iVar5 + 8)) &&
                (iVar5 = nextStreamChunk(), fVar6 = DAT_00d5ddec, *(float *)(iVar5 + 8) < DAT_00d5ddec))
            {
                iVar5 = nextStreamChunk();
                fVar6 = *(float *)(iVar5 + 8);
            }
            m_minValue3 = fVar6;
            break;
        case 0xe:
            iVar5 = nextStreamChunk();
            fVar6 = DAT_00d76300;
            if ((DAT_00d76300 < *(float *)(iVar5 + 8)) &&
                (iVar5 = nextStreamChunk(), fVar6 = DAT_00d5ddec, *(float *)(iVar5 + 8) < DAT_00d5ddec))
            {
                iVar5 = nextStreamChunk();
                fVar6 = *(float *)(iVar5 + 8);
            }
            m_maxValue3 = fVar6;
            break;
        case 0xf:
            iVar5 = nextStreamChunk();
            fVar6 = 0.0f;
            if ((0.0f < *(float *)(iVar5 + 8)) &&
                (iVar5 = nextStreamChunk(), fVar6 = g_currentTime, *(float *)(iVar5 + 8) < g_currentTime))
            {
                iVar5 = nextStreamChunk();
                fVar6 = *(float *)(iVar5 + 8);
            }
            m_minValue4 = fVar6;
            break;
        case 0x10:
            iVar5 = nextStreamChunk();
            fVar6 = 0.0f;
            if ((0.0f < *(float *)(iVar5 + 8)) &&
                (iVar5 = nextStreamChunk(), fVar6 = g_currentTime, *(float *)(iVar5 + 8) < g_currentTime))
            {
                iVar5 = nextStreamChunk();
                fVar6 = *(float *)(iVar5 + 8);
            }
            m_maxValue4 = fVar6;
            break;
        case 0x11:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(6, uVar4);
            break;
        case 0x12:
            iVar5 = nextStreamChunk();
            if (0.0f < *(float *)(iVar5 + 8))
            {
                iVar5 = nextStreamChunk();
                param_2 = g_currentTime;
                if (*(float *)(iVar5 + 8) < g_currentTime)
                {
                    iVar5 = nextStreamChunk();
                    param_2 = *(float *)(iVar5 + 8);
                }
            }
            else
            {
                param_2 = 0.0f;
            }
            break;
        case 0x13:
            nextStreamChunk();
            uVar4 = readCommandValue();
            setColor(7, uVar4);
            break;
        case 0x14:
            iVar5 = nextStreamChunk();
            m_rawData1 = *(int *)(iVar5 + 8);
            break;
        case 0x15:
            iVar5 = nextStreamChunk();
            m_rawData2 = *(int *)(iVar5 + 8);
            break;
        }
        advanceStream();
        cVar3 = isStreamEnd();
        fVar6 = g_currentTime;
    }
    if (m_maxIndex <= m_minIndex)
        m_maxIndex = m_minIndex + 100;
    fVar7 = DAT_00d5c454;
    if (m_maxValue1 <= m_minValue1)
        m_maxValue1 = m_minValue1 + DAT_00d5c454;
    if (m_maxValue2 <= m_minValue2)
        m_maxValue2 = m_minValue2 + DAT_00d5d7b8;
    fVar1 = m_minValue3;
    if (m_maxValue3 <= fVar1)
        m_maxValue3 = fVar1 + fVar7;
    fVar7 = m_minValue4;
    if (m_maxValue4 <= fVar7)
        m_maxValue4 = fVar7;
    if (m_rawData2 < m_rawData1)
        m_rawData1 = m_rawData2;
    iVar5 = m_maxIndex - m_minIndex;
    m_range1 = m_maxValue1 - m_minValue1;
    if (iVar5 < 1)
        m_step1 = 0.0f;
    else
        m_step1 = fVar6 / (float)iVar5;
    if (m_step1 <= 0.0f)
        m_currentInterpolatedIndex = 0;
    else
        m_currentInterpolatedIndex = (int)((float)(m_maxIndex - m_minIndex) * param_2 + (float)m_minIndex);
    m_range2 = m_maxValue3 - m_minValue3;
    m_range4 = m_maxValue4 - m_minValue4;
    fVar7 = m_maxValue2 - m_minValue2;
    if (DAT_00e44598 < fVar7)
        m_step2 = fVar6 / fVar7;
    else
        m_step2 = 0.0f;
    return;
}