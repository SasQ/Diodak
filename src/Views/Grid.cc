#include "Grid.hh"

/// Constructor.
Grid::Grid(const wxPen& linePen, const wxSize& cellSize):
	linePen(linePen), gridStepX( cellSize.GetWidth() ), gridStepY( cellSize.GetHeight() )
{ }

/// Another constructor. Defaults the pen stroke width to 1.
Grid::Grid(const wxColour& lineColor, const wxSize& cellSize):
	linePen( wxPen(lineColor,1) ), gridStepX( cellSize.GetWidth() ), gridStepY( cellSize.GetHeight() )
{ }


/// Low-level grid drawing function.
void Grid::DrawOn(wxDC& dc, const wxRect& clip, const wxPoint& offset)
{
	unsigned
	  gridStartX = clip.GetX(), gridStartY = clip.GetY(),
	  gridFirstX = gridStartX + offset.x % gridStepX,           // Modular division protects the offset from getting larger than
	  gridFirstY = gridStartY + offset.y % gridStepY,           // the grid cell's width, because this looks ugly (big blanks).
	  gridEndX = clip.GetRight(), gridEndY = clip.GetBottom();
	
	dc.SetPen(linePen);
	for (int x = gridFirstX; x < gridEndX; x += gridStepX) dc.DrawLine(x,gridStartY, x,gridEndY);
	for (int y = gridFirstY; y < gridEndY; y += gridStepY) dc.DrawLine(gridStartX,y, gridEndX,y);
}