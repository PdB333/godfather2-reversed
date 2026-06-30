// FUNC_NAME: ObjectiveManager::createObjective

void ObjectiveManager::createObjective(uint objectiveId, int param2, int param3, int param4, short param5, byte param6, int param7, int param8, int param9)
{
    uint local_18[5];
    Objective* obj;

    local_18[1] = 2;
    local_18[2] = 0x10; // bucket count? or max size?
    local_18[3] = 0;    // flags?

    obj = (Objective*)__ca_new(0x2c, local_18 + 1);  // allocate 44 bytes (sizeof Objective)
    if (obj == nullptr) {
        obj = nullptr;
    }
    else {
        // Objective fields:
        // +0x00: vtable pointer (set to PTR_FUN_00e37fd4)
        // +0x04: field1 (param2)
        // +0x08: field2 (param8)
        // +0x0C: field3 (param9)
        // +0x10: field4 (set to 0)
        // +0x14: field5? (not set)
        // +0x18: field6 (param4)
        // +0x1C: field7 (param5 as short)
        // +0x1E: field8 (param6 as byte)
        // +0x20: field9 (param3)
        // +0x24: field10 (param7)
        // +0x28: field11 (set to 0)
        obj->field1 = param2;
        obj->field2 = param8;
        obj->field3 = param9;
        obj->field6 = param4;
        *(short*)&obj->field7 = param5;
        *(byte*)((int)obj + 0x1E) = param6;
        obj->field4 = 0;
        obj->vtable = &PTR_FUN_00e37fd4;  // set virtual function table
        obj->field9 = param3;
        obj->field10 = param7;
        obj->field11 = 0;
    }

    local_18[0] = objectiveId;  // used as hash key
    FUN_00423cf0(local_18, &obj, objectiveId % *(uint*)(*(int*)(DAT_01223398 + 8) + 8));  // insert into hash table
    return;
}