/*
 * GreyNetic Screensaver for XBox Media Center
 * Copyright (c) 2004 Team XBMC
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


#include "xbmc_scr_dll.h"

#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <d3d11.h>
#endif

#define MAX_BOXES 10000

extern "C" {
#include "GreyNetic.h"

	int		NumberOfBoxes = MAX_BOXES;

	int		MaxSizeX = 200;
	int		MinSizeX = 0;
	int		MaxSizeY = 200;
	int		MinSizeY = 0;
	int		MaxSquareSize = 200;
	int		MinSquareSize = 0;
	int		MaxAlpha = 255;
	int		MinAlpha = 0;
	int		MaxRed = 255;
	int		MinRed = 0;
	int		MaxGreen = 255;
	int		MinGreen = 0;
	int		MaxBlue = 255;
	int		MinBlue = 0;
	int		MaxJoined = 255;
	int		MinJoined = 0;


	bool	MakeSquares = false;
	bool	JoinedSizeX = false;
	bool	JoinedSizeY = false;
	bool	JoinedRed = false;
	bool	JoinedGreen = false;
	bool	JoinedBlue = false;
	bool	JoinedAlpha = false;


	int		m_width;
	int		m_height;
	float		m_centerx;
	float		m_centery;
	
	int xa[MAX_BOXES];
	int ya[MAX_BOXES];
	int wa[MAX_BOXES];
	int ha[MAX_BOXES];
	float dwcolor[MAX_BOXES][4];

#ifdef WIN32
  ID3D11DeviceContext* g_pContext = nullptr;
  ID3D11Buffer*        g_pVBuffer = nullptr;
  ID3D11PixelShader*   g_pPShader = nullptr;

#define SAFE_RELEASE(_p)		{ if(_p) { _p->Release();	_p=NULL; } }

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

////////////////////////////////////////////////////////////////////////////
// XBMC has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!props)
    return ADDON_STATUS_UNKNOWN;

  SCR_PROPS* scrprops = (SCR_PROPS*)props;

  m_iWidth = scrprops->width;
  m_iHeight = scrprops->height;
#ifdef WIN32
  g_pContext = reinterpret_cast<ID3D11DeviceContext*>(scrprops->device);
  InitDXStuff();
#endif
  return ADDON_STATUS_NEED_SETTINGS;
}




// XBMC tells us we should get ready
// to start rendering. This function
// is called once when the screensaver
// is activated by XBMC.
extern "C" void Start()
{
	return;
}


void DrawRectangle(int x, int y, int w, int h, float* dwColour)
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
    glBegin(GL_TRIANGLE_STRIP);
    for (size_t j=0;j<4;++j)
    {
      glColor4f(cvVertices[j].r, cvVertices[j].g, cvVertices[j].b, cvVertices[j].a);
      glVertex2f(cvVertices[j].x, cvVertices[j].y);
    }
    glEnd();
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

// XBMC tells us to render a frame of
// our screensaver. This is called on
// each frame render in XBMC, you should
// render a single frame only - the DX
// device will already have been cleared.
extern "C" void Render()
{
#ifdef WIN32
  g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  size_t strides = sizeof(MYCUSTOMVERTEX), offsets = 0;
  g_pContext->IASetVertexBuffers(0, 1, &g_pVBuffer, &strides, &offsets);
  g_pContext->PSSetShader(g_pPShader, NULL, 0);
#endif

	for (int i=NumberOfBoxes - 1 ; i>0; i--){
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
	

	if(MakeSquares){
		ha[0] = rand() % (MaxSquareSize - MinSquareSize) + MinSquareSize;	
		wa[0] = ha[0]; 
	}

	if(JoinedSizeY){
		ha[0] = joined;
	}
	if(JoinedSizeX){
		wa[0] = joined;
	}

	//ha[0] = wa[0];

	for (int i=NumberOfBoxes - 1 ; i>0; i--){	
		DrawRectangle(xa[i],ya[i],wa[i],ha[i], dwcolor[i]);
	}
	return;
}

// XBMC tells us to stop the screensaver
// we should free any memory and release
// any resources we have created.
extern "C" void ADDON_Stop()
{
#ifdef WIN32
  SAFE_RELEASE(g_pPShader);
  SAFE_RELEASE(g_pVBuffer);
#endif
  return;
}

void ADDON_Destroy()
{
}

ADDON_STATUS ADDON_GetStatus()
{
  return ADDON_STATUS_OK;
}

bool ADDON_HasSettings()
{
  return true;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *strSetting, const void *value)
{
  if (strcmp(strSetting,"boxes") == 0)
   NumberOfBoxes = *(int*)value;
  if (strcmp(strSetting,"square") == 0)
    MakeSquares = *(bool*)value;
  if (strcmp(strSetting,"maxsizex") == 0)
    MaxSizeX = *(int*)value;
  if (strcmp(strSetting,"maxsizey") == 0)
    MaxSizeY = *(int*)value;
  if (strcmp(strSetting,"minsizex") == 0)
    MinSizeX = *(int*)value;
  if (strcmp(strSetting,"minsizey") == 0)
    MinSizeY = *(int*)value;
  if (strcmp(strSetting,"minsize") == 0)
    MinSquareSize = *(int*)value;
  if (strcmp(strSetting,"maxsize") == 0)
    MaxSquareSize = *(int*)value;
  if (strcmp(strSetting,"minalpha") == 0)
    MinAlpha = *(int*)value;
  if (strcmp(strSetting,"maxalpha") == 0)
    MaxAlpha = *(int*)value;
  if (strcmp(strSetting,"minred") == 0)
    MinRed = *(int*)value;
  if (strcmp(strSetting,"maxred") == 0)
    MaxRed = *(int*)value;
  if (strcmp(strSetting,"mingreen") == 0)
    MinGreen = *(int*)value;
  if (strcmp(strSetting,"maxgreen") == 0)
    MaxGreen = *(int*)value;
  if (strcmp(strSetting,"minblue") == 0)
    MinBlue = *(int*)value;
  if (strcmp(strSetting,"maxblue") == 0)
    MaxBlue = *(int*)value;

  return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char *flag, const char *sender, const char *message, const void *data)
{
}

void GetInfo(SCR_INFO *info)
{
}
};
