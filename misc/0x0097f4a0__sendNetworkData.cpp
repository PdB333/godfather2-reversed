// FUNC_NAME: sendNetworkData
void sendNetworkData(void* param_1)
{
    int* netObject;
    
    if (param_1 != 0) {
        netObject = getNetObject(param_1);
        if (netObject != 0) {
            sendReliablePacket(*(void**)(netObject + 0x48), netObject + 0x10, 500, g_netSession);
        }
    }
    return;
}