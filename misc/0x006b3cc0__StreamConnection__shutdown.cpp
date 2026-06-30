// FUNC_NAME: StreamConnection::shutdown
void __fastcall StreamConnection::shutdown(StreamConnection* thisPtr)
{
    // +0x40 and +0x3c are likely type IDs or flags; constant 0x637b907 is a class magic.
    if (thisPtr->m_nativeObject != 0x637b907) {   // +0x40: m_nativeObject
        if (thisPtr->m_altObject == 0x637b907) { // +0x3c: m_altObject
            // Log "SPGP FLIP" with an extra parameter from +0x38 (maybe a sub-type)
            Debug::log(0x53504750, 0x464c4950, thisPtr->m_someParam); // +0x38: m_someParam
            Debug::popMessage(0x20);
            ResourceManager::release(thisPtr->m_resource, 2); // +0xd8: m_resource
        }
        goto exit;
    }

    // Normal shutdown path
    Debug::log(0x53504750, 0x464c4950, thisPtr->m_someParam); // +0x38: m_someParam
    switch (thisPtr->m_shutdownState) { // +0xc4: m_shutdownState
    case 0:
        Debug::popMessage(0x1a);
        break;
    case 1:
        Debug::popMessage(0x1b);
        break;
    case 2:
        Debug::popMessage(0x1c);
        break;
    // default case falls through, no popMessage
    case 5:
        Debug::popMessage(0x22);
        break;
    }
    ResourceManager::releaseAsync(thisPtr->m_resource, 2); // +0xd8: m_resource
    globalCleanup(); // FUN_006b2b00 - static cleanup
exit:
    if (thisPtr->m_hasPendingRelease) { // +0xd4: m_hasPendingRelease
        finalizeRelease(); // FUN_006ae2b0 - final cleanup
    }
}