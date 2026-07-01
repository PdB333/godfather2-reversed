// FUNC_NAME: Weapon::updateBurstFire
void __thiscall Weapon::updateBurstFire(uint param_2, uint param_3)
{
    float currentTime = *reinterpret_cast<float*>(0x01205228); // global game time
    Sentient* owner = reinterpret_cast<Sentient*>(this->ownerPtr); // this+0x5C (index 0x17)
    // owner flags at offset 0x8e0
    byte ownerFlags = *reinterpret_cast<byte*>(reinterpret_cast<uint>(owner) + 0x8e0);
    uint ownerFlagsWord = *reinterpret_cast<uint*>(reinterpret_cast<uint>(owner) + 0x8e0);
    // global manager (likely EntityManager or SimManager)
    int* entityManager = reinterpret_cast<int*>(FUN_00800a90());

    bool bVar3 = false;
    if (((ownerFlagsWord >> 10) & 1) != 0 && // bit 10: e.g., "weapon raised"?
        *reinterpret_cast<char*>(reinterpret_cast<uint>(owner) + 0x1b8c) == '\0' && // not reloading?
        *reinterpret_cast<int*>(reinterpret_cast<uint>(entityManager) + 0x328) != 0) // manager valid?
    {
        bool canFire = FUN_0076c380(owner); // check ammo, fire conditions
        if (canFire && ((*(uint*)(reinterpret_cast<uint>(owner) + 0x249c) >> 2) & 1) != 0)
        {
            if (FUN_00719fb0() != 0) // likely player authority check
            {
                bVar3 = true;
            }
        }
    }

    if ((ownerFlags & 1) == 0) // not currently in burst fire?
    {
        if (bVar3 &&
            (static_cast<float>(this->burstTimer) <= currentTime - static_cast<float>(this->lastBurstTime)))
        {
            // Fire one burst shot
            FUN_00624ca0(1); // play sound? (argument 1)
            int* vtable = reinterpret_cast<int*>(this); // first int is vtable pointer
            const char* stateName = reinterpret_cast<const char*>(thunk_FUN_004dafd0("BurstFireNoAnimST"));
            // call virtual method at vtable+0x20 (likely "setState" or "triggerAnimation")
            (*reinterpret_cast<void(__thiscall*)(Weapon*, uint, uint, const char*)>(
                vtable[0x20]))(this, param_2, param_3, stateName);
            return;
        }
    }
    else // (ownerFlags & 1) != 0 (burst in progress)
    {
        if (!bVar3)
        {
            // Initialize/restart burst timing
            float randomDelay = static_cast<float>(FUN_00716490()); // random float 0..1?
            this->burstTimer = randomDelay;
            // Get weapon parameter from owner at +0x24bc (e.g., burst interval)
            int weaponParam = *reinterpret_cast<int*>(reinterpret_cast<uint>(owner) + 0x24bc);
            float adjustedParam = static_cast<float>(weaponParam);
            if (weaponParam < 0)
            {
                adjustedParam += *reinterpret_cast<float*>(0x00e44578); // adjust negative values
            }
            this->lastBurstTime = static_cast<int>(adjustedParam * (*reinterpret_cast<float*>(0x00d5efb8)));
            FUN_00624bd0(0x211bc9c1); // likely debug/log or audio event
            FUN_00624d00(); // reset some state
        }
    }
}