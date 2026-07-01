//FUNC_NAME: Entity::processEvent
void __thiscall Entity::processEvent(int thisPtr, int eventParam)
{
    // Call function with the event parameter (likely a message or input)
    FUN_004d3d90(eventParam);
    
    // Read a byte from offset +0xB8 (likely a state flag or identifier)
    // and pass it to another handler
    FUN_0094dc50(*(byte *)(thisPtr + 0xB8));
    
    return;
}