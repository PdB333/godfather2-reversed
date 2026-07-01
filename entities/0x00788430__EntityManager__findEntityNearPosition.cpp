// FUNC_NAME: EntityManager::findEntityNearPosition
int * __thiscall EntityManager::findEntityNearPosition(
    int *entityList,           // param_1: linked list head pointer (contains this pointer in context)
    int entityType,            // param_2: entity type ID to match
    float *position,           // param_3: XYZ position to check distance against
    float timeThreshold,       // param_4: time threshold for matching (if not -1.0f)
    int requiredData           // param_5: required extra data value (e.g., subtype)
)
{
    int *currentNode;
    int entityDataPtr;
    
    entityDataPtr = FUN_007856f0(entityType);  // get entity type data (likely from a type registry)
    currentNode = (int *)*entityList;           // dereference this pointer to get list head
    
    if (currentNode == (int *)0x0) {
        return (int *)0x0;
    }
    
    do {
        // param_1[1] appears to be entity type ID stored in node
        if (currentNode[1] == entityType) {
            // Check if entity has extra data; offset +0x6 holds some flag/pointer
            if (currentNode[6] == 0) {
                // No extra data, use 0 as comparison value
                // (requiredData must be 0 to match)
            }
            else {
                // Subtract 0x48 to get data offset, likely adjusting for object header
                // +0x6 holds a pointer to some data structure, subtracting 0x48 gets to comparison field
            }
            
            // Check required data matches (currentNode[6] adjusted)
            int dataCheck = (currentNode[6] == 0) ? 0 : (currentNode[6] - 0x48);
            
            if ((requiredData == dataCheck) &&
                // Check time threshold condition: if entity type's time value equals sentinel (-1.0f), skip time check
                // Otherwise require current entity's time + threshold > type's time
                ((*(float *)(entityDataPtr + 0x18) == DAT_00d5ccf8) ||
                 (timeThreshold <= (float)currentNode[2] + *(float *)(entityDataPtr + 0x18))) &&
                // Check distance condition: if type's max distance equals sentinel, skip distance check
                // Otherwise entity position must be within type's max distance from given position
                ((*(float *)(entityDataPtr + 0x1c) == DAT_00d5ccf8) ||
                 ((float)currentNode[5] - position[2]) * ((float)currentNode[5] - position[2]) +
                 ((float)currentNode[4] - position[1]) * ((float)currentNode[4] - position[1]) +
                 ((float)currentNode[3] - position[0]) * ((float)currentNode[3] - position[0]) <=
                 *(float *)(entityDataPtr + 0x1c)))) {
                return currentNode;  // Found matching entity
            }
        }
        
        currentNode = (int *)*currentNode;  // Advance to next node in linked list
        if (currentNode == (int *)0x0) {
            return (int *)0x0;
        }
    } while (true);
}
/* 
Entity node structure (offsets from node pointer):
+0x00: Next node pointer (linked list)
+0x04: Entity type ID
+0x08: Time/age field
+0x0C: Position X
+0x10: Position Y
+0x14: Position Z
+0x18: Extra data pointer (or zero if none)

Entity type data structure (obtained from FUN_007856f0):
+0x18: Time threshold value (compared against entity time)
+0x1C: Max distance squared for position matching
DAT_00d5ccf8 appears to be -1.0f sentinel value meaning "ignore this check"
*/