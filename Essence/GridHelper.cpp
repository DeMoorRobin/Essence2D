#include "MiniginPCH.h"
#include "GridHelper.h"

GLuint dae::GridHelper::columns{};
GLuint dae::GridHelper::rows{};
float dae::GridHelper::tileSize{};
float dae::GridHelper::xOffset{};
float dae::GridHelper::yOffset{}; 

void dae::GridHelper::SetGridData(GLuint rowCount, GLuint columnCount, float tileS, float x, float y)
{
	rows = rowCount;
	columns = columnCount;
	tileSize = tileS;
	xOffset = x;
	yOffset = y;
}

GLuint dae::GridHelper::GetTileX(float x)
{
	return GLuint((x - xOffset) / tileSize);
}

GLuint dae::GridHelper::GetTileY(float y)
{
	return GLuint((y - yOffset) / tileSize);
}

GLuint dae::GridHelper::GetTile(float x, float y)
{
	return GetTileY(y) * columns + GetTileX(x);
}