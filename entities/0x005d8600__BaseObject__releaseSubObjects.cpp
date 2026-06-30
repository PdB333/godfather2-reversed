// FUNC_NAME: BaseObject::releaseSubObjects
void __fastcall BaseObject::releaseSubObjects(BaseObject* this) {
    // this: pointer to object with vtable at offset 0
    int subObj1 = this->subObj1; // offset +0x10 (param_1[4])
    this->vtable = &g_BaseObjectVtable; // PTR_FUN_00e3edfc, set to base vtable during destruction

    if (subObj1 != 0) {
        // Add subObj1 pointer to global allocation tracker
        int* trackerPtr = (int*)(g_ObjectTracker + 0x14); // DAT_01206880 + 0x14
        **(int**)(g_ObjectTracker + 0x14) = &g_SubObj1Tag; // PTR_LAB_01126ed8
        *trackerPtr = *trackerPtr + 4;
        *(int*)(*trackerPtr) = subObj1;
        *trackerPtr = *trackerPtr + 4;
    }

    if (this->subObj2 != 0) { // offset +0x0C (param_1[3])
        int subObj2Data = this->subObj2Data; // offset +0x14 (param_1[5])
        int* trackerPtr = (int*)(g_ObjectTracker + 0x14);
        **(int**)(g_ObjectTracker + 0x14) = &g_SubObj2Tag; // PTR_LAB_01126ec4
        *trackerPtr = *trackerPtr + 4;
        *(int*)(*trackerPtr) = subObj2Data;
        *trackerPtr = *trackerPtr + 4;
        // Call destructor/release function for subObj2
        (*g_SubObjDestructor)(this->subObj2); // DAT_0119caf4
    }
}