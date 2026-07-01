// FUNC_NAME: Sentient::setActiveWeapon
void __thiscall Sentient::setActiveWeapon(Sentient *this)
{
    int weaponHandle = *(int *)((char *)this + 0x5C); // +0x5C: weapon ID or handle
    CResourceMgr *resMgr = CResourceMgr::GetInstance(); // 0x00800a90 singleton getter
    if (resMgr != (CResourceMgr *)0x0) {
        resMgr->Update();                           // vtable+0x7c
        resMgr->SetResource(weaponHandle, "r_weapon", 0); // vtable+0x154
    }
    return;
}