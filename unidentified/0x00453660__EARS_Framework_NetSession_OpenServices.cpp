// Xbox PDB: EARS::Framework::NetSession::OpenServices
extern "C" void FUN_00453660()
{
    const std::uint32_t iMsgPreNetworkUpdate = FUN_004dafd0("iMsgPreNetworkUpdate");
    FUN_00408260(&DAT_0120e978, iMsgPreNetworkUpdate);

    const std::uint32_t iMsgPostNetworkUpdate = FUN_004dafd0("iMsgPostNetworkUpdate");
    FUN_00408260(&DAT_0120ea74, iMsgPostNetworkUpdate);
}