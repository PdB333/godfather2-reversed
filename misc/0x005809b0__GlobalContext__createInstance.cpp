// FUNC_NAME: GlobalContext::createInstance
void GlobalContext::createInstance(int param1) {
    // Allocate 0x14 bytes for a GlobalContext object
    GlobalContext* obj = (GlobalContext*)operator new(0x14);
    if (obj) {
        // Set vtable pointer (unaff_EDI is a static vtable for this class)
        obj->vtable = g_pClassVTable;  // unaff_EDI
        // Store the parameter at +0x10
        obj->field4 = param1;

        // Prepare initialization parameters
        struct InitParams params;
        params.version = 2;
        params.bufferSize = 0x10;
        params.flags = 0;

        // Call the first virtual function via the vtable
        // This function returns a value used for fields at +0x08 and +0x0C
        int result = obj->vtable->virtualFunc0(param1, &params);
        obj->field2 = result;
        obj->field3 = result;
        obj->field1 = 0; // Set field at +0x04 to zero

        // Store the created object globally
        g_pGlobalContext = obj;
    } else {
        g_pGlobalContext = nullptr;
    }
}