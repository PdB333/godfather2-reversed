// Xbox PDB: EARS_Apt_UIBooksExecStyles_ShowScreen
// FUNC_NAME: ExecStylesMenu::populateExecStyles
void __fastcall ExecStylesMenu::populateExecStyles(int *param_1)

{
  FUN_005a04a0("ShowScreen",0,&DAT_00d84448,1,"ExecStyles");
  *param_1 = 0;
  param_1[1] = 0;
  FUN_005a04a0("ExecStylesSetGroup",0,&DAT_00d84448,1,"$dv_menu_books_executions_environment");
  FUN_00914820(0x9bc1fb76,0x27d7677b,0x3a30f378,"Environment",0x4a347d11);
  FUN_00914820(0xd2ec8f74,0x9722d22f,0xee3576f2,"Environment",0x861308a5);
  FUN_00914820(0x29b4c84,0xe7e5e1bf,0xf7ec5502,"Environment",0xbfeee13c);
  FUN_00914820(0x1c7af0fd,0xe0b133b8,0x37c3d87b,"Environment",0x2b36ee1c);
  FUN_00914820(0xa816e6bb,0x6c4d2976,0xc35fce39,"Environment",0x911bc524);
  *param_1 = *param_1 + 1;
  param_1[1] = 0;
  FUN_005a04a0("ExecStylesSetGroup",0,&DAT_00d84448,1,"$dv_menu_books_executions_weapon");
  FUN_00914820(0x4de0e008,0x121722c3,0x6929c786,"Weapon",0x87480212);
  FUN_00914820(0x9967fefc,0x1019ca37,0xfc15837a,"Weapon",0x41798a2b);
  FUN_00914820(0x90b93e0d,0xb039f412,0x36ecba0f,"Weapon",0x34498488);
  FUN_00914820(0x70b1c20b,0x4ff53190,0x3066550d,"Weapon",0x934a7495);
  FUN_00914820(0x35451d78,0x14888cfd,0xf4f9b07a,"Weapon",0x5eadd3e8);
  FUN_00914820(0xdd0afc0c,0xbc4e6b91,0x9cbf8f0e,"Weapon",0x365c2654);
  FUN_00914820(0xa19e5779,0x80e1c6fe,0x6152ea7b,"Weapon",0x1bf85a7);
  FUN_00914820(0xe4fe4ad6,0x4d085f5b,0x41cf1fd8,"Weapon",0xfd0531d1);
  FUN_00914820(0xa991a643,0x119bbac8,0x6627b45,"Weapon",0xc8689124);
  FUN_00914820(0x9c35eda7,0xb9f40fac,0x74e861a9,"Weapon",0xa5a258e);
  FUN_00914820(0x60c94914,0x7e876b19,0x397bbd16,"Weapon",0xd5bd84e1);
  FUN_00914820(0x5dd23c91,0xf3e1b6cc,0x3372070f,"Weapon",0x23707f61);
  FUN_00914820(0x226597fe,0xb8751239,0xf805627c,"Weapon",0xeed3deb4);
  *param_1 = *param_1 + 1;
  param_1[1] = 0;
  FUN_005a04a0("ExecStylesSetGroup",0,&DAT_00d84448,1,"$dv_menu_books_executions_explosives");
  FUN_00914820(0x9049fc3a,0x26597675,0x65e9c6b8,"Explosives",0x140a3fa0);
  *param_1 = *param_1 + 1;
  param_1[1] = 0;
  FUN_005a04a0("ExecStylesSetGroup",0,&DAT_00d84448,1,"$dv_menu_books_executions_h2h");
  FUN_00914820(0xc88c4a4c,0x5c72a8d1,0x6a1ba34e,"Hand to hand",0xd6fb96e9);
  FUN_00914820(0x20e1d4f0,0xe51817ab,0x3c2abc6e,"Hand to hand",0x513e449f);
  FUN_00914820(0xc70224cc,0xc5aab5d1,0x60125ece,"Hand to hand",0xe4635a31);
  FUN_00914820(0x463b2714,0x257e9699,0x5efba16,"Hand to hand",0x1e89e327);
  FUN_00914820(0xbc4157c8,0x4856c3cd,0x5ab04fca,"Hand to hand",0x1b0fec2d);
  FUN_00914820(0x7f8a0129,0x5ecd70ae,0x3f3e942b,"Hand to hand",0x65cc9dc6);
  FUN_00914820(0x441d5c96,0x2360cc1b,0x3d1ef98,"Hand to hand",0xb1d62cb3);
  *param_1 = *param_1 + 1;
  param_1[1] = 0;
  FUN_005a04a0("ExecStylesSetGroup",0,&DAT_00d84448,1,"$dv_menu_books_executions_objects");
  FUN_00914820(0x2f655c5,0x9905d000,0xd8962043,"Objects",0x4b22db5e);
  FUN_00914820(0xc789b132,0x5d992b6d,0x9d297bb0,"Objects",0x972c6a4b);
  FUN_00914820(0x1928ffb7,0xa53e6bbc,0xb797f7b9,"Objects",0x66df4203);
  FUN_00914820(0xa4d9fc13,0xa5d5ff98,0x720b9715,"Objects",0x745af2a4);
  FUN_00914820(0xe8051c45,0x7e149680,0xbda4e6c3,"Objects",0xc55863f4);
  FUN_00914820(0xac9877b2,0x42a7f1ed,0x82384230,"Objects",0x1161f2e1);
  FUN_00914820(0xff333dd9,0x1cf15fde,0xd7e5b1db,"Objects",0xed562d3c);
  FUN_00914820(0xc3c69946,0xe184bb4b,0x9c790d48,"Objects",0x395fbc29);
  FUN_00914820(0x4c149522,0xfb14a1dd,0xf87b00a0,"Objects",0x3661217f);
  FUN_00914820(0x10a7f08f,0xbfa7fd4a,0xbd0e5c0d,"Objects",0x826ab06c);
  FUN_005a04a0("ExecStylesShowScreen",0,&DAT_00d84448,0);
  return;
}