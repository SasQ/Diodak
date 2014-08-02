#include "Grid.hh"

/// Constructor.
Grid::Grid(const wxPen& linePen, const wxSize& cellSize):
	linePen(linePen), stepX( cellSize.GetWidth() ), stepY( cellSize.GetHeight() )
{ }

/// Another constructor. Defaults the pen stroke width to 1.
Grid::Grid(const wxColour& lineColor, const wxSize& cellSize):
	linePen( wxPen(lineColor,1) ), stepX( cellSize.GetWidth() ), stepY( cellSize.GetHeight() )
{ }


/// Low-level grid drawing function.
void Grid::DrawOn(wxDC& dc, const wxRect& clip)
{
	// http://docs.wxwidgets.org/trunk/classwx_d_c.html#a12f2c236d4d320acec0bc6fe20e8399d
	// "Note that the point (x2, y2) is not part of the line and is not drawn by this function
	//  (this is consistent with the behaviour of many other toolkits)."
	
	const unsigned
		startX = clip.GetX(), startY = clip.GetY(),
		endX = clip.GetRight(), endY = clip.GetBottom(),
		firstX = startX + (stepX - startX % stepX) % stepX,  // FIXME: Try reducing these equations some more.
		firstY = startY + (stepY - startY % stepY) % stepY;
	
	dc.SetPen(linePen);
	for (int x = firstX; x <= endX; x += stepX)  dc.DrawLine(x,startY, x,endY+1);
	for (int y = firstY; y <= endY; y += stepY)  dc.DrawLine(startX,y, endX+1,y);
}