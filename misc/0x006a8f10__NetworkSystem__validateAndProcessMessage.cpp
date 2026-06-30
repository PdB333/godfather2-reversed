// FUNC_NAME: NetworkSystem::validateAndProcessMessage
void NetworkSystem::validateAndProcessMessage(int *packetData)
{
    int *subData;
    char lookupResult;
    int handle; // local_4

    // Check if packetData is valid, has type 3, and contains a sub-pointer.
    // Also ensure the data size is > 15 and the sub-structure has expected magic and version.
    if ((packetData != NULL) && (packetData[0] == 3) &&
        (subData = (int *)packetData[1], subData != NULL) &&
        ((uint)packetData[2] > 0xf && (*subData == 0xCAE87732) && (subData[1] == 1)))
    {
        handle = 0;
        packetData = NULL;
        lookupResult = FUN_006a8be0(0x3596a436, &handle, &packetData);
        if (lookupResult != '\0')
        {
            FUN_006a8dd0(handle, packetData);
        }
    }
    return;
}