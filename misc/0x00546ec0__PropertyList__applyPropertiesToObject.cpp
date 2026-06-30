// FUNC_NAME: PropertyList::applyPropertiesToObject
void PropertyList::applyPropertiesToObject(void* obj, PropertyNode* propertyList) {
    // Function at 0x00546ec0 - Applies a set of properties to an object
    // obj: target object, with fields at +0x8 (float) and +0x10 (bool array)
    // propertyList: linked list or array of PropertyNode structures

    FUN_0043aff0(in_EAX, 0x50ab9af2); // Profiling or debug begin

    PropertyNode* currentNode = propertyList;
    bool useBitArray = false;  // local_64 flag: 0 = linked list, 1 = indexed array
    int currentIndex = 0;      // local_58
    int totalCount = 0;        // local_54
    PropertyNode* currentProperty; // local_50
    void* bitArray;             // iStack_60
    PropertyNode** propertyArray; // puStack_5c

    while (true) {
        bool loopEnd;
        if (!useBitArray) {
            loopEnd = (currentNode == nullptr);
        } else {
            loopEnd = (currentIndex == totalCount);
        }
        if (loopEnd) break;

        PropertyNode** propertyRef = &currentProperty;
        if (!useBitArray) {
            propertyRef = &currentNode;
        }

        // Check property type magic
        void* dataPtr;
        if (*(short*)((int)propertyRef + 6) == 0x25e3) {
            // Property has a short value at offset 4, read as pointer
            dataPtr = (void*)(uint)*(ushort*)(propertyRef + 1);
        } else {
            dataPtr = propertyRef[1];
        }

        if (dataPtr == nullptr) {
            // Type 0: Set float field at obj+8
            PropertyNode** prop = &currentProperty;
            if (!useBitArray) prop = &currentNode;
            *(float*)((int)obj + 8) = (float)prop[2] * DAT_00e445c8;
        } else if (dataPtr == (void*)1) {
            // Type 1: Set bool array at obj+0x10 to all true/false
            PropertyNode** prop = &currentProperty;
            if (!useBitArray) prop = &currentNode;
            void* boolValue = prop[2];
            uint count = (**(code**)(*(int*)propertyList + 0x228))(0); // Get array size
            for (uint i = 0; i < count; i++) {
                *(bool*)(i + *(int*)((int)obj + 0x10)) = (boolValue != nullptr);
            }
        } else if (dataPtr == (void*)2) {
            // Type 2: Another form of bool array set with different bounds
            PropertyNode** prop = &currentProperty;
            if (!useBitArray) prop = &currentNode;
            void* boolValue = prop[2];
            uint total = (**(code**)(*(int*)propertyList + 0x220))(); // Get total count
            uint count = (**(code**)(*(int*)propertyList + 0x228))(0); // Get initialized count
            for (uint i = count; i < total; i++) {
                *(bool*)(i + *(int*)((int)obj + 0x10)) = (boolValue != nullptr);
            }
        }

        // Advance iterator
        if (!useBitArray) {
            if ((int)currentIndex < 0) {
                // Linked list: next node is at *currentNode (offset 0)
                currentNode = (PropertyNode*)((int)currentNode + *(int*)currentNode);
                FUN_0043b140();
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex++;
                currentNode = (PropertyNode*)((int)currentNode + *(int*)currentNode);
            } else {
                currentNode = (PropertyNode*)&DAT_01163cf8; // Sentinel
            }
        } else {
            currentIndex++;
            if (currentIndex != totalCount) {
                // Bit array check: if bit is set, next property is from propertyArray
                if ((*(byte*)((currentIndex >> 3) + (int)bitArray) & (1 << (currentIndex & 7))) == 0) {
                    currentProperty = *propertyArray;
                    // Copy first element
                    // (uStack_48 = *propertyArray;)
                    propertyArray++;
                } else {
                    currentProperty = nullptr;
                }
            }
        }
    }
}