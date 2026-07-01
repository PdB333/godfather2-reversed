// FUNC_NAME: EARS::String::formatFromInt
void __fastcall StringFormatFromInt(int this)
{
    undefined4 local_54;
    undefined1 *local_50;
    undefined1 local_4c;
    undefined1 local_48[4];
    int local_44[2];
    int local_3c[15];
    
    FUN_0084d6b0(&stack0x00000004);
    local_50 = local_48;
    local_54 = DAT_0112dd94;
    local_4c = 0;
    if (this == 0) {
        this = 0;
    }
    else {
        this = this + 0x3c;
    }
    FUN_00408bf0(&local_54, this, 0);
    if (local_3c[0] != 0) {
        FUN_004daf90(local_3c);
    }
    if (local_44[0] != 0) {
        FUN_004daf90(local_44);
    }
    return;
}