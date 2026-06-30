// FUNC_NAME: GlobalData::getInstance
undefined* GlobalData::getInstance(void)

{
  return &g_globalDataSingleton;
}