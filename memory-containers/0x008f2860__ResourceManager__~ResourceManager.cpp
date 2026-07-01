// FUNC_NAME: ResourceManager::~ResourceManager

void __fastcall ResourceManager::~ResourceManager(ResourceManager* this)
{
    // Set vtable to base class for proper virtual destruction
    *(void**)this = &PTR_FUN_00d81038;

    // Release global resources (static data members or singleton pointers)
    releaseGlobalResource(&DAT_012069c4);
    releaseGlobalResource(&DAT_0112fe48);
    releaseGlobalResource(&DAT_0112fe40);
    releaseGlobalResource(&DAT_01206940);
    releaseGlobalResource(&DAT_01206a20);
    deleteObjectList(&DAT_0112fe18);
    deleteObjectList(&DAT_0112fe28);
    deleteObjectList(&DAT_0112fe48);
    deleteObjectList(&DAT_0112fe40);
    deleteObjectList(&DAT_0112fe30);
    deleteObjectList(&DAT_0112fe20);
    deleteObjectList(&DAT_0112fe38);
    deleteObjectList(&DAT_0112fe10);
    finalCleanup();
}