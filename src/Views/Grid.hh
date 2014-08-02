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
 	void DrawOn(wxDC& dc, const wxRect& clip);
 	
 private:
 	wxPen linePen;
 	unsigned stepX, stepY;
};

/// ----- Header-level implementation -----

inline wxSize   Grid::CellSize() const     { return wxSize(stepX,stepY); }
inline unsigned Grid::CellWidth() const    { return stepX; }
inline unsigned Grid::CellHeight() const   { return stepY; }

#endif