/*
 * GreyNetic Screensaver for XBox Media Center
 * Copyright (c) 2004 Team Kodi
 *
 * Ver 1.0 26 Fed 2005	Dylan Thurston (Dinomight)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2  of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
#include "shaders/GUIShader.h"
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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

class ATTRIBUTE_HIDDEN CScreensaverGreyNetic
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
{
public:
  CScreensaverGreyNetic();
  virtual ~CScreensaverGreyNetic();

  virtual void Render() override;

private:
  int m_iWidth;
  int m_iHeight;
#ifndef WIN32
  CGUIShader* m_shader;
  GLuint m_vertexVBO;
  GLuint m_indexVBO;
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

  NumberOfBoxes = kodi::GetSettingInt("boxes");
  MakeSquares = kodi::GetSettingBoolean("square");
  MaxSizeX = kodi::GetSettingInt("maxsizex");
  MaxSizeY = kodi::GetSettingInt("maxsizey");
  MinSizeX = kodi::GetSettingInt("minsizex");
  MinSizeY = kodi::GetSettingInt("minsizey");
  MinSquareSize = kodi::GetSettingInt("minsize");
  MaxSquareSize = kodi::GetSettingInt("maxsize");
  MinAlpha = kodi::GetSettingInt("minalpha");
  MinRed = kodi::GetSettingInt("minred");
  MaxRed = kodi::GetSettingInt("maxred");
  MinGreen = kodi::GetSettingInt("mingreen");
  MaxGreen = kodi::GetSettingInt("maxgreen");
  MinBlue = kodi::GetSettingInt("minblue");
  MaxBlue = kodi::GetSettingInt("maxblue");

#ifdef WIN32
  g_pContext = reinterpret_cast<ID3D11DeviceContext*>(Device());
  InitDXStuff();
#else
  m_shader = new CGUIShader("vert.glsl", "frag.glsl");
  m_shader->CompileAndLink();
  glGenBuffers(1, &m_vertexVBO);
  glGenBuffers(1, &m_indexVBO);
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
  delete m_shader;
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_indexVBO);
#endif
}

// Kodi tells us to render a frame of
// our screensaver. This is called on
// each frame render in Kodi, you should
// render a single frame only - the DX
// device will already have been cleared.
void CScreensaverGreyNetic::Render()
{
#ifdef WIN32
  g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  UINT strides = sizeof(MYCUSTOMVERTEX), offsets = 0;
  g_pContext->IASetVertexBuffers(0, 1, &g_pVBuffer, &strides, &offsets);
  g_pContext->PSSetShader(g_pPShader, NULL, 0);
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

  ha[0] = rand() % (MaxSizeY - MinSizeY) + MinSizeY;
  wa[0] = rand() % (MaxSizeX - MinSizeX) + MinSizeX;

  if(MakeSquares)
  {
    ha[0] = rand() % (MaxSquareSize - MinSquareSize) + MinSquareSize;
    wa[0] = ha[0];
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
  return;
}

void CScreensaverGreyNetic::DrawRectangle(int x, int y, int w, int h, float* dwColour)
{
    //Store each point of the triangle together with it's colour
    MYCUSTOMVERTEX cvVertices[] =
    {
        {(float)   x, (float) y+h, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
        {(float)   x, (float)   y, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
        {(float) x+w, (float) y+h, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
        {(float) x+w, (float)   y, 0.0f, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
    };
#ifndef WIN32
    m_shader->PushMatrix();
    m_shader->Enable();

    GLfloat x1 = -1.0 + 2.0*x/m_iWidth;
    GLfloat y1 = -1.0 + 2.0*y/m_iHeight;
    GLfloat x2 = -1.0 + 2.0*(x+w)/m_iWidth;
    GLfloat y2 = -1.0 + 2.0*(y+h)/m_iHeight;

    struct PackedVertex
    {
      GLfloat x, y, z;
      GLfloat r, g, b, a;
    } vertex[4] = {{x1, y1, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                   {x2, y1, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                   {x2, y2, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]},
                   {x1, y2, 0.0, dwColour[0], dwColour[1], dwColour[2], dwColour[3]}};

    GLubyte idx[] = {0, 1, 2, 2, 3, 0};

    GLint posLoc = m_shader->GetPosLoc();
    GLint colLoc = m_shader->GetColLoc();

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PackedVertex)*4, &vertex[0], GL_STATIC_DRAW);

    glVertexAttribPointer(posLoc, 3, GL_FLOAT, 0, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, x)));
    glVertexAttribPointer(colLoc, 4, GL_FLOAT, 0, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, r)));

    glEnableVertexAttribArray(posLoc);
    glEnableVertexAttribArray(colLoc);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*6, idx, GL_STATIC_DRAW);
    glEnable(GL_BLEND);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(posLoc);
    glDisableVertexAttribArray(colLoc);

    m_shader->Disable();
    m_shader->PopMatrix();
#else
    D3D11_MAPPED_SUBRESOURCE res = {};
    if (SUCCEEDED(g_pContext->Map(g_pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
    {
      memcpy(res.pData, cvVertices, sizeof(cvVertices));
      g_pContext->Unmap(g_pVBuffer, 0);
    }
    g_pContext->Draw(4, 0);

#endif
}

ADDONCREATOR(CScreensaverGreyNetic);
