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
void Grid::DrawOn(wxDC& dc, const wxRect& clip)
{
	unsigned gridStartX = clip.GetX(), gridStartY = clip.GetY(),
	         gridEndX = clip.GetRight(), gridEndY = clip.GetBottom();
	
	dc.SetPen(linePen);
	for (int x = gridStartX; x < gridEndX; x += gridStepX) dc.DrawLine(x,gridStartY, x,gridEndY);
	for (int y = gridStartY; y < gridEndY; y += gridStepY) dc.DrawLine(gridStartX,y, gridEndX,y);
}