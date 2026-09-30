/***************************************************************
 * Name:      BanyanChartApp.h
 * Purpose:   Defines Application Class
 * Author:    lunanerdderg ()
 * Created:   2026-09-19
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:
 **************************************************************/

#ifndef BANYANCHARTAPP_H
#define BANYANCHARTAPP_H

#include "wx/wx.h"
#include "wx/sizer.h"
#include <wx/app.h>


class Canvas : public wxPanel
{

public:
    Canvas(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};

class BanyanChartApp : public wxApp
{
    public:
        virtual bool OnInit();
        wxFrame *frame;
        Canvas * drawPane;};

#endif // BANYANCHARTAPP_H
