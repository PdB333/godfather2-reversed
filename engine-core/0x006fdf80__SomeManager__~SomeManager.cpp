// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager(SomeManager* this)
{
    int i;

    // Set vtable pointer to base class's destructor vtable (likely for virtual function calls during destruction)
    *(int*)this = (int)&PTR_FUN_00d60c6c;  // +0x00 vtable
    this->field_3 = (int)&PTR_LAB_00d60c68; // +0x0C secondary vtable or manager-specific pointer

    // Release references to three static global objects (likely singletons or shared resources)
    FUN_004086d0(&DAT_012069e4);  // Release global object A
    FUN_004086d0(&DAT_012069dc);  // Release global object B
    FUN_004086d0(&DAT_012069d4);  // Release global object C

    // If a registered callback handle is not -1, unregister it
    if (this->field_0x82 != -1) {
        this->field_0x82 = -1;
        FUN_005e6640(&LAB_006fd640);  // Unregister or remove callback
    }

    // Run internal clean-up loops: two iterations of routine A
    i = 1;
    do {
        FUN_006fbda0();  // Subroutine A (cleanup for two internal components)
        i--;
    } while (i >= 0);

    // Then three iterations of routine B
    i = 2;
    do {
        FUN_006fd830();  // Subroutine B (cleanup for three internal components)
        i--;
    } while (i >= 0);

    // Switch vtable to another base class (or null) to finalize destruction
    this->field_3 = (int)&PTR_LAB_00d60c5c; // +0x0C vtable change

    // Clear a global flag indicating this manager is active
    DAT_0112a9f4 = 0;

    // Call global destructor / shutdown routine
    FUN_004083d0();
}