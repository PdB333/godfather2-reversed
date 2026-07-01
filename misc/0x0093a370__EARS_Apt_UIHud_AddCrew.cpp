// Xbox PDB: EARS_Apt_UIHud_AddCrew
// FUNC_NAME: CrewLeaderComponent::addCrewMember
void __thiscall CrewLeaderComponent::addCrewMember(int this, int crewMember)
{
    int *component;
    int gameManager;
    float currentHealth;
    float maxHealth;
    float healthFraction;

    // Check if this crew leader is alive (byte at +0x48 non-zero)
    // and not in a special state (byte at +0x49 bit 1 and 3 clear)
    // and not in a certain flag (bit 21 of uint at +0x5c clear)
    if (((*(char *)(this + 0x48) != '\0') && ((*(byte *)(this + 0x49) & 10) == 0)) &&
        ((*(uint *)(this + 0x5c) >> 0x15 & 1) == 0) &&
        // crewMember must be valid and have a specific component (hash 0xa0d329d6)
        (crewMember != 0 && (component = (int *)FUN_007115e0(crewMember, 0xa0d329d6), component != (int *)0x0)))
    {
        // Update crew state (likely adds member to list)
        FUN_00939520(crewMember);

        // Get game manager singleton (DAT_01131040)
        gameManager = FUN_0043b870(DAT_01131040);

        // Set flags at +0x7c based on byte at gameManager+0x44 (clear bottom 2 bits)
        *(uint *)(this + 0x7c) = *(byte *)(gameManager + 0x44) & 0xfc;

        // Call virtual functions on the component to get current and max health
        // vtable at *component, method at +0xc0 and +0xc4
        currentHealth = (**(code **)(*component + 0xc0))();
        maxHealth = (**(code **)(*component + 0xc4))();

        // Compute health fraction, clamp between 0 and DAT_00d5e288
        if ((float)0.0 < (currentHealth / maxHealth) * (float)DAT_00d5e288)
        {
            currentHealth = (**(code **)(*component + 0xc0))();
            maxHealth = (**(code **)(*component + 0xc4))();
            healthFraction = DAT_00d5e288;
            if ((currentHealth / maxHealth) * (float)DAT_00d5e288 < (float)DAT_00d5e288)
            {
                currentHealth = (**(code **)(*component + 0xc0))();
                maxHealth = (**(code **)(*component + 0xc4))();
                healthFraction = (currentHealth / maxHealth) * (float)DAT_00d5e288;
            }
        }
        else
        {
            healthFraction = 0.0f;
        }

        // Store health fraction at +0x78
        *(float *)(this + 0x78) = healthFraction;

        // Log "AddCrew" event
        FUN_005a04a0("AddCrew", 0, &DAT_00d8a64c, 0);
    }
    return;
}