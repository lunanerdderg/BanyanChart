/***************************************************************
 * Name:      BanyanChartMain.h
 * Purpose:   Defines Application Frame
 * Author:    lunanerdderg ()
 * Created:   2026-09-19
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:
 **************************************************************/

#ifndef BANYANCHARTMAIN_H
#define BANYANCHARTMAIN_H

#include "FileParser.h"

//(*Headers(BanyanChartFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

class FileParser;
class BanyanChartFrame: public wxFrame
{
    public:

        BanyanChartFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BanyanChartFrame();

    private:
        const int WIDTH = 100; // BOOKMARK
        const int HEIGHT = 100;

        FileParser File{};
        bool Canvas_dragging;
        int Canvas_mouseX, Canvas_mouseY, Canvas_mousePrevX, Canvas_mousePrevY;

        void Canvas_render(wxDC& dc);

        //(*Handlers(BanyanChartFrame)
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);

        void mouseMoved(wxMouseEvent& event);
        void mouseDown(wxMouseEvent& event);
        void mouseReleased(wxMouseEvent& event);
        void rightClick(wxMouseEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void mouseWheelMoved(wxMouseEvent& event);
        void paintEvent(wxPaintEvent& event);
        //*)

        //(*Identifiers(BanyanChartFrame)
        static const wxWindowID ID_CANVAS;
        static const wxWindowID idMenuNew;
        static const wxWindowID idMenuOpen;
        static const wxWindowID idMenuSave;
        static const wxWindowID idMenuSaveAs;
        static const wxWindowID idMenuQuit;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(BanyanChartFrame)
        wxMenu* Menu3;
        wxMenu* Menu4;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxPanel* Canvas;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BANYANCHARTMAIN_H
