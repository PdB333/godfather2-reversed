// FUNC_NAME: Entity::setStateFlags  

void __thiscall Entity::setStateFlags(uint flagsToSet)  
{  
    // +0x4c: pointer to a pending event/timer, checked for validity  
    if (FUN_0040b8d0(*(uint*)(this + 0x4c)) != 0)  
    {  
        // Create a local event structure (like an empty message)  
        EventData event;  
        event.id = DAT_01206840;  // global event ID  
        event.param1 = 0;  
        event.param2 = 0;  
        FUN_00408a00(&event, 0);  // dispatch event  
    }  
    // OR the new flags into the state flags at +0x6c  
    *(uint*)(this + 0x6c) |= flagsToSet;  
    // Clear the pending event pointer  
    *(uint*)(this + 0x4c) = 0;  
}