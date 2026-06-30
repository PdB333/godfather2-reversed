// FUN_NAME: CombatPerception::canAttackTarget
bool __thiscall CombatPerception::canAttackTarget(int* otherObject, Entity* entity)
{
    int* basePtr = nullptr;
    bool bVar2 = false; // initialized to false default
    bool bVar3 = false;

    // entity->somePtr at offset +0x8 might be a component pointer
    int* componentPtr = reinterpret_cast<int*>(entity->field_0x8);

    if (componentPtr != nullptr)
    {
        // Get the base object by subtracting 0x48 from the component pointer
        // (componentPtr is +0x48 into some object)
        basePtr = reinterpret_cast<int*>(componentPtr - 0x48); // offset subtraction: componentPtr - 0x48

        // Check if componentPtr is not a sentinel value (0x48 is likely a null-like constant)
        // Also check a global singleton condition
        if (componentPtr != reinterpret_cast<int*>(0x48))
        {
            // Get global manager (e.g., CombatManager)
            int* globalMgr = reinterpret_cast<int*>(0x0043b870)(DAT_01131014);
            if (globalMgr != nullptr)
            {
                // Call a virtual function on the manager at vtable offset 0x38
                bool isEnabled = reinterpret_cast<bool (__thiscall*)(int*)>(*(int*)(*globalMgr + 0x38))(globalMgr);
                if (isEnabled)
                {
                    bVar2 = true;
                    goto afterBaseCheck;
                }
            }
        }
    }

    // Perform line-of-sight or distance check via base pointer's virtual function
    if (basePtr != nullptr)
    {
        // Call virtual function at vtable offset 0xC0 (slot 48) on basePtr
        // Returns a float (likely distance or visibility factor)
        float value = reinterpret_cast<float (__thiscall*)(int*)>(*(int*)(*basePtr + 0xC0))(basePtr);
        bVar2 = (value > 0.0f) ? false : true;
    }
    else
    {
        bVar2 = true; // If no base pointer, assume hostile? (fallback)
    }

afterBaseCheck:
    // Check if target/otherObject is valid and within range
    if (basePtr == nullptr)
    {
        bVar3 = false;
    }
    else
    {
        // Call a virtual function on otherObject at vtable offset 0xBC
        // This likely checks if the target is still valid/visible
        float otherValue = reinterpret_cast<float (__thiscall*)(int*)>(*(int*)(*otherObject + 0xBC))(otherObject);
        bVar3 = (otherValue != 0.0f);
    }

    if (!bVar2)
    {
        // If not hostile, check further conditions
        // entity flags at offset +0x3c
        uint16_t flags = static_cast<uint16_t>(entity->field_0x3c);
        bool notInCover = (flags >> 2) & 1; // bit2: is entity in cover?
        bool notSelf = (entity != reinterpret_cast<Entity*>(this->field_0x14)); // this +0x14 is current target?
        bool notInVehicle = (flags >> 3) & 1; // bit3: is entity in vehicle?

        if (!bVar3 && !notInCover && notSelf && !notInVehicle)
        {
            return false;
        }
        if (bVar3)
        {
            return true;
        }
        if (notInVehicle) // bit3 set means in vehicle
        {
            return true;
        }
    }
    return false;
}