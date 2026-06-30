// FUNC_NAME: MotionBlurEffect::initialize
void __fastcall MotionBlurEffect::initialize(MotionBlurEffect *this)
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0060a380(); // Get post-processing manager
  this->m_ppManager = iVar1; // +0x10
  iVar2 = FUN_0060a2e0(&PTR_DAT_0110a39c); // Get shader manager (likely)
  this->m_shaderManager = iVar2; // +0x14
  
  FUN_006127d0(); // Some initialization function
  
  // Get shader parameters
  this->m_velocityScaleParam = FUN_0060a580(this->m_ppManager, "g_VelocityScale"); // +0xA4
  this->m_velocityXYZParam = FUN_0060a580(this->m_ppManager, "g_VelocityXYZ"); // +0xA8
  this->m_colorTextureParam = FUN_0060a580(this->m_shaderManager, "ColorTexture"); // +0xAC
  this->m_depthTextureParam = FUN_0060a580(this->m_shaderManager, "DepthTexture"); // +0xB0
  this->m_psVelocityParamsParam = FUN_0060a580(this->m_shaderManager, "g_PSVelocityParams"); // +0xB4
  this->m_prevModelParam = FUN_0060a580(this->m_ppManager, "g_PrevModel"); // +0xB8
  return;
}