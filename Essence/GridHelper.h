#pragma once
namespace dae
{
	class GridHelper
	{
	public:
		static void SetGridData(GLuint rows, GLuint columns, float tileSize, float xOffset, float yOffset);
		static GLuint GetTileX(float x);
		static GLuint GetTileY(float y);
		static GLuint GetTile(float x, float y);

		static GLuint GetColumns() { return columns; };
		static GLuint GetRows() { return rows; };
		static float GetTileSize() { return tileSize; };

	private:
		static GLuint columns;
		static GLuint rows;
		static float tileSize;
		static float xOffset;
		static float yOffset;
	};


}
