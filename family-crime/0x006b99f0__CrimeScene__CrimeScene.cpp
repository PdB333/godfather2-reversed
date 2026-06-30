// FUNC_NAME: CrimeScene::CrimeScene
void __thiscall CrimeScene::CrimeScene(CrimeScene* this)
{
    // +0x00: vtable pointer
    *reinterpret_cast<void**>(this) = &CrimeScene_vtable;
    // +0x3C (offset 0x0F * 4): secondary vtable 1
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x3C) = &CrimeScene_secondaryVtable1;
    // +0x48 (offset 0x12 * 4): secondary vtable 2
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x48) = &CrimeScene_secondaryVtable2;
    // +0x98 (offset 0x26 * 4): initialize embedded CrimeSceneData member
    CrimeSceneData* sceneData = reinterpret_cast<CrimeSceneData*>(reinterpret_cast<char*>(this) + 0x98);
    CrimeSceneData::CrimeSceneData(sceneData);  // FUN_004086d0
    CrimeSceneData::Init(sceneData);            // FUN_00408310
    // Register this crime scene with the global manager
    CrimeSceneManager::RegisterScene(this);     // FUN_006bcd70
}