// Xbox PDB: EARS::Framework::System::Open
extern "C" void FUN_0040cf70()
{
    const std::uint32_t iMsgStartSystem = FUN_004dafd0("iMsgStartSystem");
    FUN_00408260(&DAT_01206950, iMsgStartSystem);

    const std::uint32_t iMsgStopSystem = FUN_004dafd0("iMsgStopSystem");
    FUN_00408260(&DAT_01206948, iMsgStopSystem);

    const std::uint32_t iMsgSystemTick = FUN_004dafd0("iMsgSystemTick");
    FUN_00408260(&DAT_01206940, iMsgSystemTick);
}