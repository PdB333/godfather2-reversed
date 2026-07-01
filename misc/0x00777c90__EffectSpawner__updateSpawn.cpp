// FUNC_NAME: EffectSpawner::updateSpawn

void __thiscall EffectSpawner::updateSpawn(int iBaseValue, int eType)
{
    float fTemp, fRand, fScaled;
    int iState;
    bool bFlag;
    float vDirection[4];
    float vPosition[4];

    iState = *(int *)(*(int *)(this + 0x5c) + 0x24c4);  // m_pContext->stateId
    if ((iState == 0) || (iState == 0x48))
    {
        // State is idle or special
        if (*(float *)(this + 0x9c) == 0.0f)  // m_fSpawnTimer == 0
        {
            iState = _rand();
            fTemp = (float)iBaseValue;
            if (iBaseValue < 0)
                fTemp += 4294967296.0f;  // treat as unsigned
            *(float *)(this + 0x9c) =
                fTemp * DAT_00d5efb8 + ((float)iState * DAT_00e44590 + DAT_00d5780c) * DAT_00d68188;
        }
        else
        {
            fTemp = (float)iBaseValue;
            if (iBaseValue < 0)
                fTemp += 4294967296.0f;
            fScaled = fTemp * DAT_00d5efb8;
            if (fScaled < *(float *)(this + 0x9c))
            {
                bFlag = false;
                if (*(float *)(this + 0xa8) == 0.0f) goto LAB_00777eba;  // m_fSpawnInterval
            }
            else
            {
                bFlag = true;
            }

            iState = getSomePositionSource();  // returns pointer
            getRandomDirectionVector(vDirection, iState + 0x20);  // get direction

            if (bFlag)
            {
                iState = _rand();
                fRand = (float)iState * DAT_00e44590 * DAT_00d68330 * DAT_00e445c8;
                *(float *)(this + 0xa8) = fRand;  // set random interval
                if ((eType == 1) || (eType == 3))
                {
                    *(float *)(this + 0xa8) = fRand * 0.0f;  // immediate for types 1,3
                }

                iState = _rand();
                *(float *)(this + 0x9c) =
                    ((float)iState * DAT_00e44590 + DAT_00d5780c) * DAT_00d68188 + fScaled;
            }

            iState = getSomePositionSource();
            transformVectorByMatrix(vDirection, vDirection, iState + 0x10, *(float *)(this + 0xa8));
            // Compute spawn position: origin + scaled direction
            iState = getSomePositionSource();
            vPosition[0] = vDirection[0] * DAT_00d5779c + *(float *)(iState + 0x30);
            vPosition[1] = vDirection[1] * DAT_00d5779c + *(float *)(iState + 0x34);
            vPosition[2] = vDirection[2] * DAT_00d5779c + *(float *)(iState + 0x38);
            spawnEffect(eType, vPosition, 1);
        }
    }
    else
    {
        // State is active (non-idle)
        iState = getSomePositionSource();
        spawnEffect(eType, (float *)(iState + 0x30), 0);  // spawn at source directly
        *(float *)(this + 0x9c) = 0.0f;
        *(float *)(this + 0xa8) = 0.0f;
    }

LAB_00777eba:
    if ((*(int *)(this + 0xac) >> 5 & 1) != 0)  // m_nFlags bit 5
    {
        iState = _rand();
        fTemp = (float)iBaseValue;
        if (iBaseValue < 0)
            fTemp += 4294967296.0f;
        *(float *)(this + 0xa0) =
            fTemp * DAT_00d5efb8 + ((float)iState * DAT_00e44590 + DAT_00d5780c) * DAT_00d6826c;
    }
    return;
}