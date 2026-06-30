// FUNC_NAME: AsyncJob::execute
bool AsyncJob::execute(undefined4 param2, undefined4 param3)
{
    float fVar1;
    int iVar2;
    bool bVar3;
    float fVar4;
    undefined4 local_2c0;
    undefined4 local_2bc;
    undefined4 local_2b8;
    undefined4 local_2b4;
    undefined4 local_2b0;
    float local_2ac;
    undefined4 local_2a8;
    undefined4 local_2a4;
    char local_29c[20];
    undefined **local_288;
    char local_284;
    char *local_280;
    int local_27c;
    int local_278;
    char local_274[260];
    char local_170[284];
    undefined4 local_54;

    fVar1 = g_globalTime;  // DAT_01205228
    if (((this->flags & 0x40) != 0) &&
        (g_globalTime < this->lastTime + g_timeThreshold)) // _DAT_00e514c4
    {
        return true;
    }
    fVar4 = g_someFloat1;  // DAT_00d5fad8
    if (this->type == '\x01')
    {
        fVar4 = g_someFloat2;  // DAT_00d5fad4
    }
    // Compute some value
    local_2ac = (fVar4 + g_someFloat3) - g_someFloat4;  // DAT_00d5faf4, _DAT_00d5fb44
    local_2b0 = 0;
    local_2a8 = 0;
    local_2a4 = g_someVec1;  // _DAT_00d5780c
    local_2c0 = 0;
    local_2bc = g_someFloat5;  // DAT_00d5fb40
    local_2b8 = 0;
    local_2b4 = g_someVec1;   // _DAT_00d5780c
    // Transform vectors
    FUN_00a65bb0(&local_2b0, &local_2c0, g_someFloat4);  // _DAT_00d5fb44
    // Begin frame operations
    FUN_00549bf0();
    // Get some buffer
    FUN_00549cf0(local_170);
    // Post a message with event ID 0x40136 and flags 0x80000000
    FUN_00540bc0(0x40136, 0x80000000, param2, param3);
    // Get result from message?
    local_54 = FUN_00540cc0(local_29c);
    // Setup a small structure
    local_280 = local_274;
    local_288 = &g_ptrTable1;  // PTR_LAB_00e3572c
    local_278 = -0x7ffffff0;
    local_27c = 0;
    local_284 = 0;
    // Pass job data
    FUN_00549d40(this + 0x44);
    // Process network layer
    FUN_00549ea0(&local_288, 0);
    iVar2 = local_278;
    bVar3 = local_27c != 0;
    if (bVar3)
    {
        this->flags |= 0x40;
    }
    else
    {
        this->flags &= 0xbf;
    }
    this->lastTime = fVar1;
    local_288 = &g_ptrTable1;  // PTR_LAB_00e3572c
    if (-1 < local_278)
    {
        TlsGetValue(g_tlsIndex);  // DAT_01139810
        FUN_00aa26e0(local_280, iVar2 << 4, 0x17);
    }
    local_288 = &g_ptrTable2;  // PTR_LAB_00dcf968
    FUN_00549cb0();
    return bVar3;
}