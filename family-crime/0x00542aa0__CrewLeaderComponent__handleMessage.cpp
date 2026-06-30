// FUNC_NAME: CrewLeaderComponent::handleMessage
// Function address: 0x00542aa0
// Role: Handles incoming messages, specifically for spawning a crew member upon receiving a specific message type if slots are available.

void __thiscall CrewLeaderComponent::handleMessage(CrewLeaderComponent* this, int* msgData)
{
    // Call base message processing function
    FUN_0045e670(msgData);

    // Check message type against global constants
    if (DAT_012069c4 == *msgData)
    {
        // Dispatch to base component virtual function at vtable offset 0x208
        BaseComponent* base = reinterpret_cast<BaseComponent*>(reinterpret_cast<char*>(this) - 0x3c);
        (**(code **)(*(int*)base + 0x208))(DAT_012067e8);
        return;
    }

    // Second message type check
    if ((DAT_0120e93c == *msgData) &&
        ((*(int*)((char*)this + 0x294) == 0 || *(int*)((char*)this + 0x294) == 0x48)) &&
        (*(int*)((char*)this + 0x284) != 0 ||
         (*(int*)((char*)this + 0x288) != 0 ||
          (*(int*)((char*)this + 0x28c) != 0 ||
           *(int*)((char*)this + 0x290) != 0))))
    {
        // Check global condition
        char condition = FUN_00445250();
        if (condition != '\0')
        {
            // Try to find an empty slot in the 4-slot array at offset 0x284
            int slotIndex = FUN_00446130((int*)((char*)this + 0x284), 0);
            if (slotIndex != 0)
            {
                // Create a new component or entity
                int* newObj = (int*)FUN_005435d0();
                if (newObj != nullptr)
                {
                    BaseComponent* base = reinterpret_cast<BaseComponent*>(reinterpret_cast<char*>(this) - 0x3c);
                    // Call virtual function at 0x1a4 on the new object (likely initialization)
                    (**(code **)(*(int*)newObj + 0x1a4))(newObj);
                    // Attach new object to the base component via virtual at offset 0x1c
                    (**(code **)(*(int*)base + 0x1c))(base);
                }
            }
        }
    }
    return;
}