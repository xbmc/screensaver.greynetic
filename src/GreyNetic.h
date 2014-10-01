// include file for screensaver template

int	m_iWidth;
int m_iHeight;

void DrawRectangle(int x, int y, int w, int h, float* dwColour);

struct MYCUSTOMVERTEX
{
	float x, y, z, rhw; // The transformed position for the vertex.
        float r, g, b, a;
};
