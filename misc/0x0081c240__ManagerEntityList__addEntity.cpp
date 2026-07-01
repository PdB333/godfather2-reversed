// FUNC_NAME: ManagerEntityList::addEntity

/**
 * Function at 0x0081c240
 * Purpose: Attempt to add an entity (param_1) to a manager's list.
 * Returns 1 on success, 0 if conditions fail.
 * Checks manager flags (+0x70) and distance/time threshold (global float vs entity +0x1c).
 */

int ManagerEntityList::addEntity(int entity, int id) // param_1 = entity, param_2 = this, param_3 = id
{
    uint flags = *(uint *)(this + 0x70); // +0x70: manager flags (bit 1,2 = availability)
    float globalThreshold = _DAT_00d577a0; // global float threshold (e.g., distance/time)
    float entityValue = *(float *)(entity + 0x1c); // +0x1c: entity field (distance, timer, etc.)

    // Condition to allow acquisition: either flags bits 1&2 clear, or threshold exceeded
    if ((flags & 6) == 0 || globalThreshold < entityValue) {
        if (canAcquire(entity, id)) { // FUN_0081b6b0: validation/check
            // Increment/start something on entity at +8
            FUN_006bf990(entity + 8); // likely reference count or state activation

            int *headPtr = (int *)(this + 0x84); // +0x84: pointer to list head
            if (*headPtr != entity) {
                if (*headPtr != 0) {
                    detachFromList(headPtr); // FUN_004daf90: remove previous head
                }
                *headPtr = entity;
                if (entity != 0) {
                    // Update tail/next fields (+0x88 in manager, +4 in entity)
                    *(int *)(this + 0x88) = *(int *)(entity + 4); // +0x88: manager's tail/previous pointer
                    *(int *)(entity + 4) = headPtr; // entity's next points to the head reference
                }
            }
            // Set a global constant at manager +0xb0
            *(undefined4 *)(this + 0xb0) = DAT_01205224; // +0xb0: timestamp or state ID
            activateEntity(entity); // FUN_0081a810: final activation
            return 1;
        }
    }
    return 0;
}