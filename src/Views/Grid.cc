#include "Grid.hh"
#include <iostream>

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
	unsigned
	  gridStartX = clip.GetX(), gridStartY = clip.GetY(),
	  gridEndX = clip.GetRight()+1, gridEndY = clip.GetBottom()+1,
	  gridFirstX = gridStartX + (gridStepX - gridStartX % gridStepX) % gridStepX,
	  gridFirstY = gridStartY + (gridStepY - gridStartY % gridStepY) % gridStepY;
	
	std::clog << "\nGrid in (" << gridStartX << ',' << gridStartY << ';' << gridEndX << ',' << gridEndY << ") "
	             "with first (" << gridFirstX << ',' << gridFirstY << ")\n  ";
	dc.SetPen(linePen);
	for (int x = gridFirstX; x < gridEndX; x += gridStepX) { dc.DrawLine(x,gridStartY, x,gridEndY);
		std::clog << x << ' '; }
		std::clog << '\n';
	for (int y = gridFirstY; y < gridEndY; y += gridStepY) { dc.DrawLine(gridStartX,y, gridEndX,y);
		std::clog << y << ' '; }
		std::clog << std::endl;
}