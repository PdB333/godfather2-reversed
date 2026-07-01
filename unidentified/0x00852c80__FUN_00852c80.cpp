// FUNC_NAME: SomeClass::forwardCallWithDefaultParam
undefined4 __thiscall SomeClass::forwardCallWithDefaultParam(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13)

{
  // Forward the call to FUN_008522d0 with all parameters plus a default -1 (0xffffffff) as the last argument
  FUN_008522d0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,param_11,
               param_12,param_13,0xffffffff);
  return param_1;
}