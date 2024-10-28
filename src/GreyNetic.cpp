/*
 *  Copyright (C) 2004-2021 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005 Dylan Thurston (Dinomight)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

/*
 *
 * Greynetic was inspired by the Xscreensaver hack of the same name
 * This is a very basic kinda boring screen saver, but it works.
 * if you find any bugs please let me know
 * dinomight@gmail.com
 *
*/


#include <kodi/addon-instance/Screensaver.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <d3d11.h>
#else
#include <kodi/gui/gl/Shader.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#define MAX_BOXES 10000

int NumberOfBoxes = MAX_BOXES;

int MaxSizeX = 200;
int MinSizeX = 0;
int MaxSizeY = 200;
int MinSizeY = 0;
int MaxSquareSize = 200;
int MinSquareSize = 0;
int MaxAlpha = 255;
int MinAlpha = 0;
int MaxRed = 255;
int MinRed = 0;
int MaxGreen = 255;
int MinGreen = 0;
int MaxBlue = 255;
int MinBlue = 0;
int MaxJoined = 255;
int MinJoined = 0;


bool MakeSquares = false;
bool JoinedSizeX = false;
bool JoinedSizeY = false;
bool JoinedRed = false;
bool JoinedGreen = false;
bool JoinedBlue = false;
bool JoinedAlpha = false;


float m_centerx;
float m_centery;

int xa[MAX_BOXES];
int ya[MAX_BOXES];
int wa[MAX_BOXES];
int ha[MAX_BOXES];
float dwcolor[MAX_BOXES][4];

struct MYCUSTOMVERTEX
{
  float x, y, z; // The transformed position for the vertex.
  float r, g, b, a;
};

#ifdef WIN32
  ID3D11DeviceContext* g_pContext = nullptr;
  ID3D11Buffer*        g_pVBuffer = nullptr;
  ID3D11PixelShader*   g_pPShader = nullptr;

#define SAFE_RELEASE(_p) { if(_p) { _p->Release();	_p=NULL; } }

const BYTE PixelShader[] =
{
     68,  88,  66,  67,  18, 124,
    182,  35,  30, 142, 196, 211,
     95, 130,  91, 204,  99,  13,
    249,   8,   1,   0,   0,   0,
    124,   1,   0,   0,   4,   0,
      0,   0,  48,   0,   0,   0,
    124,   0,   0,   0, 188,   0,
      0,   0,  72,   1,   0,   0,
     65, 111, 110,  57,  68,   0,
      0,   0,  68,   0,   0,   0,
      0,   2, 255, 255,  32,   0,
      0,   0,  36,   0,   0,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   0,  36,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   2, 255, 255,
     31,   0,   0,   2,   0,   0,
      0, 128,   0,   0,  15, 176,
      1,   0,   0,   2,   0,   8,
     15, 128,   0,   0, 228, 176,
    255, 255,   0,   0,  83,  72,
     68,  82,  56,   0,   0,   0,
     64,   0,   0,   0,  14,   0,
      0,   0,  98,  16,   0,   3,
    242,  16,  16,   0,   1,   0,
      0,   0, 101,   0,   0,   3,
    242,  32,  16,   0,   0,   0,
      0,   0,  54,   0,   0,   5,
    242,  32,  16,   0,   0,   0,
      0,   0,  70,  30,  16,   0,
      1,   0,   0,   0,  62,   0,
      0,   1,  73,  83,  71,  78,
    132,   0,   0,   0,   4,   0,
      0,   0,   8,   0,   0,   0,
    104,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,
      3,   0,   0,   0,   0,   0,
      0,   0,  15,   0,   0,   0,
    116,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   1,   0,
      0,   0,  15,  15,   0,   0,
    122,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,   3,   0,   0,   0,
    122,   0,   0,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,  12,   0,   0,   0,
     83,  86,  95,  80,  79,  83,
     73,  84,  73,  79,  78,   0,
     67,  79,  76,  79,  82,   0,
     84,  69,  88,  67,  79,  79,
     82,  68,   0, 171,  79,  83,
     71,  78,  44,   0,   0,   0,
      1,   0,   0,   0,   8,   0,
      0,   0,  32,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   3,   0,   0,   0,
      0,   0,   0,   0,  15,   0,
      0,   0,  83,  86,  95,  84,
     65,  82,  71,  69,  84,   0,
    171, 171
};

void InitDXStuff(void)
{
  ID3D11Device* pDevice = nullptr;
  g_pContext->GetDevice(&pDevice);

  CD3D11_BUFFER_DESC vbDesc(sizeof(MYCUSTOMVERTEX) * 5, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
  pDevice->CreateBuffer(&vbDesc, nullptr, &g_pVBuffer);
  pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), nullptr, &g_pPShader);

  SAFE_RELEASE(pDevice);
}
#endif

class ATTR_DLL_LOCAL CScreensaverGreyNetic
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
#ifndef WIN32
  , public kodi::gui::gl::CShaderProgram
#endif
{
public:
  CScreensaverGreyNetic();
  virtual ~CScreensaverGreyNetic();

  // kodi::addon::CInstanceScreensaver
  bool Start() override;
  void Stop() override;
  void Render() override;

private:
  int m_iWidth;
  int m_iHeight;

#ifndef WIN32
  // kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  bool OnEnabled() override { return true; }

  glm::mat4 m_projModelMatrix;

  GLuint m_vertexVBO = 0;

  GLint m_uProjModelMatLoc = -1;
  GLint m_aPositionLoc = -1;
  GLint m_aColorLoc = -1;
#endif

  void DrawRectangle(int x, int y, int w, int h, float* dwColour);
};

////////////////////////////////////////////////////////////////////////////
// Kodi has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
CScreensaverGreyNetic::CScreensaverGreyNetic()
{
  m_iWidth = Width();
  m_iHeight = Height();

  NumberOfBoxes = kodi::addon::GetSettingInt("boxes");
  MakeSquares = kodi::addon::GetSettingBoolean("square");
  MaxSizeX = kodi::addon::GetSettingInt("maxsizex");
  MaxSizeY = kodi::addon::GetSettingInt("maxsizey");
  MinSizeX = kodi::addon::GetSettingInt("minsizex");
  MinSizeY = kodi::addon::GetSettingInt("minsizey");
  MinSquareSize = kodi::addon::GetSettingInt("minsize");
  MaxSquareSize = kodi::addon::GetSettingInt("maxsize");
  MinAlpha = kodi::addon::GetSettingInt("minalpha");
  MinRed = kodi::addon::GetSettingInt("minred");
  MaxRed = kodi::addon::GetSettingInt("maxred");
  MinGreen = kodi::addon::GetSettingInt("mingreen");
  MaxGreen = kodi::addon::GetSettingInt("maxgreen");
  MinBlue = kodi::addon::GetSettingInt("minblue");
  MaxBlue = kodi::addon::GetSettingInt("maxblue");

#ifdef WIN32
  g_pContext = reinterpret_cast<ID3D11DeviceContext*>(Device());
  InitDXStuff();
#endif
}

// Kodi tells us to stop the screensaver
// we should free any memory and release
// any resources we have created.
CScreensaverGreyNetic::~CScreensaverGreyNetic()
{
#ifdef WIN32
  SAFE_RELEASE(g_pPShader);
  SAFE_RELEASE(g_pVBuffer);
#else
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
#endif
}

bool CScreensaverGreyNetic::Start()
{
#ifndef WIN32
  if (!LoadShaderFiles(kodi::addon::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/vert.glsl"),
                       kodi::addon::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/frag.glsl")))
  {
    kodi::Log(ADDON_LOG_ERROR, "Failed to load GL shaders");
    return false;
  }

  if (!CompileAndLink())
  {
    kodi::Log(ADDON_LOG_ERROR, "Failed to compile GL shaders");
    return false;
  }

  glGenBuffers(1, &m_vertexVBO);

  m_projModelMatrix = glm::ortho(0.0f, float(Width()), 0.0f, float(Height()));
#endif
  return true;
}

void CScreensaverGreyNetic::Stop()
{
}

// Kodi tells us to render a frame of
// our screensaver. This is called on
// each frame render in Kodi, you should
// render a single frame only - the DX
// device will already have been cleared.
void CScreensaverGreyNetic::Render()
{
#ifdef WIN32
  ID3D11RenderTargetView* renderTargetView;
  g_pContext->OMGetRenderTargets(1, &renderTargetView, nullptr);
  float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
  g_pContext->ClearRenderTargetView(renderTargetView, clearColor);
  SAFE_RELEASE(renderTargetView);

  g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  UINT strides = sizeof(MYCUSTOMVERTEX), offsets = 0;
  g_pContext->IASetVertexBuffers(0, 1, &g_pVBuffer, &strides, &offsets);
  g_pContext->PSSetShader(g_pPShader, NULL, 0);
#else
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);

  glVertexAttribPointer(m_aPositionLoc, 3, GL_FLOAT, 0, sizeof(MYCUSTOMVERTEX), BUFFER_OFFSET(offsetof(MYCUSTOMVERTEX, x)));
  glVertexAttribPointer(m_aColorLoc, 4, GL_FLOAT, 0, sizeof(MYCUSTOMVERTEX), BUFFER_OFFSET(offsetof(MYCUSTOMVERTEX, r)));

  glEnableVertexAttribArray(m_aPositionLoc);
  glEnableVertexAttribArray(m_aColorLoc);

  glEnable(GL_BLEND);
#endif

  for (int i=NumberOfBoxes - 1 ; i>0; i--)
  {
    xa[i] = xa[i-1] ;
    ya[i] = ya[i-1] ;
    ha[i] = ha[i-1] ;
    wa[i] = wa[i-1] ;
    dwcolor[i][0] = dwcolor[i-1][0] ;
    dwcolor[i][1] = dwcolor[i-1][1] ;
    dwcolor[i][2] = dwcolor[i-1][2] ;
    dwcolor[i][3] = dwcolor[i-1][3] ;
  }

  double red = rand() %(MaxRed - MinRed) + MinRed;
  double green = rand() %(MaxGreen - MinGreen) + MinGreen;
  double blue = rand() %(MaxBlue - MinBlue) + MinBlue;
  double alpha = rand() %(MaxAlpha - MinAlpha) + MinAlpha;
  double joined = rand() %(MaxJoined - MinJoined) + MinJoined;

  if(JoinedRed){
    red = joined;
  }
  if(JoinedGreen){
    green = joined;
  }
  if(JoinedBlue){
    blue = joined;
  }
  if(JoinedAlpha){
    alpha = joined;
  }

  dwcolor[0][0] = (float)red   / 255.0f;
  dwcolor[0][1] = (float)green / 255.0f;
  dwcolor[0][2] = (float)blue  / 255.0f;
  dwcolor[0][3] = (float)alpha / 255.0f;

  xa[0] = rand()%m_iWidth;
  ya[0] = rand()%m_iHeight;

  if (!MakeSquares)
  {
    if (MaxSizeY != MinSizeY)
      ha[0] = rand() % (MaxSizeY - MinSizeY) + MinSizeY;
    else
      ha[0] = MaxSizeY;

    if (MaxSizeX != MinSizeX)
      wa[0] = rand() % (MaxSizeX - MinSizeX) + MinSizeX;
    else
      wa[0] = MaxSizeX;
  }
  else
  {
    if (MaxSquareSize != MinSquareSize)
      wa[0] = ha[0] = rand() % (MaxSquareSize - MinSquareSize) + MinSquareSize;
    else
      wa[0] = ha[0] = MaxSquareSize;
  }

  if(JoinedSizeY)
  {
    ha[0] = joined;
  }
  if(JoinedSizeX)
  {
    wa[0] = joined;
  }

  //ha[0] = wa[0];

  for (int i=NumberOfBoxes - 1 ; i>0; i--)
  {
    DrawRectangle(xa[i],ya[i],wa[i],ha[i], dwcolor[i]);
  }

#ifndef WIN32
  glDisableVertexAttribArray(m_aPositionLoc);
  glDisableVertexAttribArray(m_aColorLoc);
#endif
  return;
}

void CScreensaverGreyNetic::DrawRectangle(int x, int y, int w, int h, float* dwColour)
{
#ifndef WIN32
  MYCUSTOMVERTEX vertex[4] = {{(float)   x, (float)   y, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float) x+w, (float)   y, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float) x+w, (float) y+h, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float)   x, (float) y+h, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]}};

  EnableShader();
  glUniformMatrix4fv(m_uProjModelMatLoc, 1, GL_FALSE, glm::value_ptr(m_projModelMatrix));
  glBufferData(GL_ARRAY_BUFFER, sizeof(MYCUSTOMVERTEX)*4, &vertex[0], GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  DisableShader();
#else
  //Store each point of the triangle together with it's colour
  MYCUSTOMVERTEX vertex[4] = {{(float)   x, (float) y+h, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float)   x, (float)   y, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float) x+w, (float) y+h, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                              {(float) x+w, (float)   y, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]}};

  D3D11_MAPPED_SUBRESOURCE res = {};
  if (SUCCEEDED(g_pContext->Map(g_pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
  {
    memcpy(res.pData, vertex, sizeof(vertex));
    g_pContext->Unmap(g_pVBuffer, 0);
  }
  g_pContext->Draw(4, 0);
#endif
}

#ifndef WIN32
void CScreensaverGreyNetic::OnCompiledAndLinked()
{
  m_uProjModelMatLoc = glGetUniformLocation(ProgramHandle(), "u_projModelMat");
  m_aPositionLoc = glGetAttribLocation(ProgramHandle(), "a_position");
  m_aColorLoc = glGetAttribLocation(ProgramHandle(), "a_color");
}
#endif

ADDONCREATOR(CScreensaverGreyNetic);
