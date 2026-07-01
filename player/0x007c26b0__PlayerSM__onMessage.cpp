// FUNC_NAME: PlayerSM::onMessage
bool PlayerSM::onMessage(undefined4 param2, undefined4 param3, int msgId, undefined4 param5)
{
    if (msgId == 0x13) // Activate
    {
        int result = isSomethingAllowed(); // FUN_007abe90
        if (result == 0)
        {
            return false;
        }
        this->activeFlag = 1; // +0x7c
    }
    else if (msgId == 0x14) // Update
    {
        // If we have a valid state index (not 0 and not 0x48)
        if ((this->someStateIndex != 0) && (this->someStateIndex != 0x48))
        {
            int base = (this->someStateIndex == 0) ? 0 : (this->someStateIndex - 0x48);
            this->someOtherFlag = *(byte *)(base + 0x9a); // Copy flag from state data
        }
        if (this->someOtherFlag != 0x01) // If flag is not set
        {
            if (this->someFloat <= g_timeThreshold) // +0x30 vs global
            {
                return false;
            }
            // Allocate an action object (size 0x34)
            void *action = allocateAction(0x34); // FUN_00798f50
            byte check = checkAllocation(action); // FUN_0079e970
            if (check == 0)
            {
                return false;
            }
            return true;
        }
    }
    else if (msgId == 0x15) // Deactivate
    {
        if (this->activeFlag == 0)
        {
            return false;
        }
        this->activeFlag = 0;
        return true;
    }
    else
    {
        // Default handler for other message types
        return BaseClass::handleMessage(param2, param3, msgId, param5); // FUN_007ab790
    }
    return true;
}