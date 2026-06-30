// FUNC_NAME: EntityFactory::createEntity
int EntityFactory::createEntity(int param_2, int param_3) {
    int result = 0;
    if (this != nullptr && param_2 != 0) {
        int subObjPtr = *(int *)(this + 0x10) + (int)this; // +0x10: offset to sub-object
        if (subObjPtr != 0 && this != (EntityFactory*)-0x18) {
            int outParam = 0;
            int outLocal = 0;
            if (parseParameters(&outParam, &outLocal)) { // FUN_005e5d90
                int newId = generateUniqueId(); // FUN_005e5e00
                int alloc = operatorNew(0x20); // FUN_009c8e50
                if (alloc != 0) {
                    int obj = initializeObject(outParam); // FUN_005e4220
                    if (obj != 0) {
                        outParam = obj;
                        // Virtual call on global singleton (DAT_01223510)
                        bool success = ((int (__thiscall*)(int, int, int, int, int, int))(*DAT_01223510 + 0x10))(
                            subObjPtr,
                            *(int *)(this + 0xc),  // +0x0C: some field
                            *(int *)(this + 0x14), // +0x14: some field
                            outLocal,
                            obj,
                            param_3
                        );
                        if (success) {
                            registerObject(&outParam); // FUN_005e6ce0
                            return newId;
                        }
                        operatorDelete(alloc); // FUN_009c8eb0
                    }
                }
            }
        }
    }
    return result;
}