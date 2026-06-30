// FUNC_NAME: MessageDispatcher::dispatchMessage
int __fastcall MessageDispatcher::dispatchMessage(int this, int edxParam, int defaultReturn, int messageType, int messageData)
{
    int result;

    if ((messageData != 0) && (messageType != 0)) {
        switch (messageType) {
        case 1:
            result = handleMessageType1(edxParam, this);
            return result;
        case 2:
            result = handleMessageType2(edxParam, this, messageData);
            return result;
        case 3:
            result = handleMessageType3(edxParam, this, messageData);
            return result;
        case 4:
            result = handleMessageType4(edxParam, this, messageData);
            return result;
        case 5:
            result = handleMessageType5(edxParam, this, messageData);
            return result;
        case 6:
            result = handleMessageType6(edxParam, this, messageData);
            return result;
        case 7:
            result = handleMessageType7(edxParam, this, messageData);
            return result;
        case 8:
            defaultReturn = handleMessageType8(edxParam, this, messageData);
        }
    }
    return defaultReturn;
}