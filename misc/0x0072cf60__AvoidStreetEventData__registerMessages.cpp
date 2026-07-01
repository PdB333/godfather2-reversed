// FUNC_NAME: AvoidStreetEventData::registerMessages
// Function at 0x0072cf60: Registers all message types for the avoid street event system.
// Called from initialization to populate static event string IDs.

void AvoidStreetEventData::registerMessages()
{
    // Each call to registerMessage stores the hash/ID of the string into the given static storage.
    // The first call registers the type name itself, the rest are message names.
    registerMessage(&DAT_0112adb8, "AvoidStreetEventData*");
    registerMessage(&DAT_0112ade8, "iMsgHearDamage");
    registerMessage(&DAT_0112ada8, "iMsgHearHijack");
    registerMessage(&DAT_0112adc0, "iMsgHitByCar");
    registerMessage(&DAT_0112ade0, "iMsgSeeDeath");
    registerMessage(&DAT_0112adc8, "iMsgHearCar");
    registerMessage(&DAT_0112adf8, "iMsgPoliceBribed");
    registerMessage(&DAT_0112ad9c, "iMsgMerchantNPCH2HDamagedByPlayer");
    registerMessage(&DAT_0112e0fc, "iMsgFuelTruckExploded");
    registerMessage(&DAT_0112adf0, "iMsgNpcUsePhone");
    registerMessage(&DAT_0112ae00, "iMsgCrewDownButNotDead");
    registerMessage(&DAT_0112add8, "iMsgMobDefenderFromPlayerArrival");
}