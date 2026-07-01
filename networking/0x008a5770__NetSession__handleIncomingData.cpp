// FUNC_NAME: NetSession::handleIncomingData

void __thiscall NetSession::handleIncomingData(int* packet)
{
    bool isStrict;
    int rawValue;
    int* pSession;
    int* pConnection;
    int* pStats;
    unsigned int combinedFlags;
    int localSequence;
    int lookupResult;

    // Preliminary packet processing
    processPacketHeader(packet);

    if ((*(int*)(this + 8) != 0) && (packet != (int*)0x0))
    {
        rawValue = (**(int (__thiscall**)(void*))(*packet + 0xc))();
        localSequence = rawValue;
        isStrict = false;
        if ((*(int*)(this + 8) != 0) && (lookupConnection(&lookupResult, &localSequence) != 0))
        {
            isStrict = *(int*)(lookupResult + 4) > 1;
        }
        lookupResult = rawValue;
        if (*(int*)(this + 8) != 0)
        {
            updateSequence(&localSequence, &lookupResult);
            *(int*)(localSequence + 4) = (isStrict ? 1 : 0) * 2 + 1;
        }

        pSession = (int*)getNetInterface();
        if ((pSession != (int*)0x0) &&
            (pSession = (int*)(**(int (__thiscall**)(int*))(*pSession + 0x34))(), pSession != (int*)0x0))
        {
            pConnection = (int*)(**(int (__thiscall**)(int*))(*pSession + 0x3c))();
            if (pConnection != (int*)0x0)
            {
                pStats = (int*)(**(int (__thiscall**)(int*))(*pConnection + 0x78))();
                combinedFlags = getIsStrictNATFlag();
                if ((*(byte*)(this + 0x37c) & 1) != 0)
                {
                    logNATType(combinedFlags);
                }
                (**(void (__thiscall**)(char const*, int))(*pStats + 0x2c))("IsStrictNAT", combinedFlags);
                (**(void (__thiscall**)(int*))(*pConnection + 100))();
            }
        }
    }

    // Check if we are currently in the FrontendMainLoop state
    if (((*(int*)(DAT_0112980c + 4) == getStringHash("FrontendMainLoop")) &&
         (DAT_01129930 != 0)) &&
        ((*(char*)(DAT_01129930 + 0x48) != '\0') &&
         ((*(byte*)(DAT_01129930 + 0x49) & 0xa) == 0)))
    {
        forwardToFrontend(packet);
    }
}