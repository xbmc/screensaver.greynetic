// include file for screensaver template

int	m_iWidth;
int m_iHeight;

void DrawRectangle(int x, int y, int w, int h, float* dwColour);
#ifdef WIN32
void InitDXStuff(void);
#endif

struct MYCUSTOMVERTEX
{
	float x, y, z; // The transformed position for the vertex.
	float r, g, b, a;
};
