// FUNC_NAME: ListManager::removeByName
void __thiscall ListManager::removeByName(void* this_ptr, ContainerDescriptor* descriptor)
{
    int* itemPtr;
    int* arrayBase;
    int currentOffset;
    void* pObject;
    int hashValue;
    const char* matchResult;

    // +0x1c in descriptor: pointer to some resource that needs cleanup
    pObject = *(void**)((char*)descriptor + 0x1c);
    if (pObject != nullptr && *(int*)((char*)pObject + 8) != 0)
    {
        releaseObject(pObject);  // FUN_009e7530
    }

    // +0x04 in descriptor: pointer to array descriptor (base, count)
    arrayBase = *(int**)((char*)descriptor + 4);
    currentOffset = *arrayBase;  // base address of array
    int count = arrayBase[1];    // number of elements
    int endOffset = currentOffset + count * 0x70;

    if (currentOffset == endOffset)
        return;

    do
    {
        // +0x40 in each 0x70-sized element: pointer to an object
        void* obj = *(void**)(currentOffset + 0x40);
        if (obj == nullptr)
        {
LAB_005587db:
            obj = *(void**)(currentOffset + 0x40);
            if (obj == nullptr)
                goto LAB_005587f1;
            if (*(int*)((char*)obj + 8) != 0)
            {
                releaseObject(obj);  // FUN_009e7530
            }
        }
        else
        {
            // Get a hash/name manager singleton via global pointer DAT_0113dfc8
            // Call method at vtable+0x14 on that manager to get a comparator
            void* comparator = (*(code**)(*(int*)DAT_0113dfc8 + 0x14))();
            // Call method at vtable+0x10 on comparator with the object to get its hash
            hashValue = (*(code**)(*(int*)comparator + 0x10))(obj);
            // Compare with the name from descriptor (first parameter)
            // FUN_00ab06f0 returns a string, non-empty indicates match?
            matchResult = (const char*)stringMatch(&descriptor, hashValue);
            if (*matchResult != '\0')
                goto LAB_005587db;

LAB_005587f1:
            obj = *(void**)(currentOffset + 0x40);
            if (obj != nullptr)
            {
                // Get the same comparator and hash
                void* comparator2 = (*(code**)(*(int*)DAT_0113dfc8 + 0x14))();
                hashValue = (*(code**)(*(int*)comparator2 + 0x10))(obj);
                // Compare with a name stored at offset 2 in this object (the class member)
                // &this_ptr + 2 is likely the class's name field (e.g., char m_name[2]? or offset)
                matchResult = (const char*)stringMatch((void*)((char*)this_ptr + 2), hashValue);
                if (*matchResult == '\0')
                    goto LAB_0055883d;
            }
            obj = *(void**)(currentOffset + 0x40);
            if (obj != nullptr && *(int*)((char*)obj + 8) != 0)
            {
                // Alternate release function for objects matching the internal name
                releaseObjectAlt((void*)((char*)this_ptr + 3), obj);  // FUN_009e71f0
            }
        }

LAB_0055883d:
        arrayBase = *(int**)((char*)descriptor + 4);
        currentOffset += 0x70;
    } while (currentOffset != *arrayBase + arrayBase[1] * 0x70);
}