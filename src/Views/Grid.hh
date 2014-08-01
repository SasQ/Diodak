#ifndef GRID_HH
#define GRID_HH

// wxWidgets library classes.
#include <wx/dc.h>
#include <wx/gdicmn.h>   // wxSize, wxRect, wxPoint
#include <wx/pen.h>
#include <wx/colour.h>


/// A helper class for drawing grids.
class Grid
{
 public:
 	Grid(const wxPen& linePen, const wxSize& cellSize);
 	Grid(const wxColour& lineColor, const wxSize& cellSize);
 	wxSize CellSize() const;
 	unsigned CellWidth() const;
 	unsigned CellHeight() const;
 	void DrawOn(wxDC& dc, const wxRect& clip, const wxPoint& offset=wxPoint(0,0) );
 	
 private:
 	wxPen linePen;
 	unsigned gridStepX, gridStepY;
};

/// ----- Header-level implementation -----

inline wxSize   Grid::CellSize() const     { return wxSize(gridStepX,gridStepY); }
inline unsigned Grid::CellWidth() const    { return gridStepX; }
inline unsigned Grid::CellHeight() const   { return gridStepY; }

#endif