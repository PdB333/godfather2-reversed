// FUNC_NAME: SomeManager::FindNearestInteractiveObject
void __thiscall SomeManager::FindNearestInteractiveObject(float targetX, float targetY, int actionIndex)
{
    // List head at this + 0x10 (intrusive doubly linked list of nodes)
    int* currentNode = *(int**)(this + 0x10);
    int* closestObject = nullptr;
    float minDistSq = DAT_00d5f6f0; // large initial value (maybe INF)

    // Iterate over all nodes in the list
    while (currentNode != (int*)(this + 0x10))
    {
        int* objectBase = nullptr;

        // Node layout: +0: next, +4: prev, +8: ownerPointer (offset from object base)
        if (currentNode[2] != 0)
        {
            // objectBase = ownerPointer - 0x48 (the object's embedded node offset)
            objectBase = (int*)(currentNode[2] - 0x48);
        }
        // else: object not valid

        if (objectBase != nullptr)
        {
            float objectPos[2];
            // Virtual call at vtable+0x24 (index 9): GetPosition(pos)
            (**(code**)(*objectBase + 0x24))(objectPos);

            // Compute squared distance to target
            float dx = objectPos[0] - targetX;
            float dy = objectPos[1] - targetY;
            float distSq = dx*dx + dy*dy;

            if (distSq < minDistSq)
            {
                minDistSq = distSq;
                if (currentNode[2] != 0)
                {
                    closestObject = objectBase;
                }
                else
                {
                    closestObject = nullptr;
                }
            }
        }

        currentNode = (int*)*currentNode; // move to next node
    }

    // If we found a closest object
    if (closestObject != nullptr)
    {
        FUN_006ceda0(actionIndex); // some preprocessing/validation

        // Check global debug/trigger flag (byte at DAT_01129914 + 0xd3)
        if (*(char*)(DAT_01129914 + 0xd3) != '\0')
        {
            // Call virtual function at vtable+0x38 (index 14): DoAction?
            // Parameter is an offset into global resource table (DAT_0112a878)
            if (actionIndex == 0)
            {
                (**(code**)(*closestObject + 0x38))(DAT_0112a878 + 0x204);
            }
            else if (actionIndex == 1)
            {
                (**(code**)(*closestObject + 0x38))(DAT_0112a878 + 0x214);
            }
            else
            {
                (**(code**)(*closestObject + 0x38))(DAT_0112a878 + 500); // 500 = 0x1f4
            }
        }
    }
    return;
}