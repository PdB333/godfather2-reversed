// FUNC_NAME: registerGlobalDestructors
void registerGlobalDestructors(void)
{
    // Register destructors for global/static objects.
    // Each address points to a destructor function or cleanup callback.
    registerDestructorCallback(&destructor_GlobalObject1);   // LAB_00801750
    registerDestructorCallback(&destructor_GlobalObject2);   // LAB_0080ac50
    registerDestructorCallback(&destructor_FUN_00460d40);    // FUN_00460d40 (likely a destructor)
    registerDestructorCallback(&destructor_GlobalObject4);   // LAB_00460d80
    registerDestructorCallback(&destructor_GlobalObject5);   // LAB_00472420
    registerDestructorCallback(&destructor_GlobalObject6);   // LAB_0080b6e0
    registerDestructorCallback(&destructor_GlobalObject7);   // LAB_00472440
    registerDestructorCallback(&destructor_GlobalObject8);   // LAB_007a7d50
}