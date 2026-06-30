// FUNC_NAME: SomeManager::dispatchEvent
void __thiscall SomeManager::dispatchEvent(int this, int* message)
{
    int messageId = *message;

    if (messageId == DAT_012069c4) 
    {
        handleEventTypeA();
        return;
    }
    if (messageId == DAT_0120e93c) 
    {
        handleEventTypeB();
        globalFunction_004086d0(&DAT_0120e93c);
        return;
    }
    if (messageId != *(int*)(this + 0x14)) 
    {
        if (messageId != *(int*)(this + 0x1c)) 
        {
            if (messageId == *(int*)(this + 0x24)) 
            {
                *(undefined4*)(this + 0x80) = *(undefined4*)(message[1]); // +0x80: some data field
                goto common_label;
            }
            if (messageId != *(int*)(this + 0x2c)) 
            {
                return;
            }
            *(undefined4*)(this + 0x84) = *(undefined4*)(message[1]); // +0x84: another data field
        }
        handleEventTypeC();
        return;
    }
common_label:
    handleEventTypeB();
    return;
}