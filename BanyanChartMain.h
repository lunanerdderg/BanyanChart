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
        FileParser File;
        size_t Canvas_selectedBlock = -1, Canvas_selectedNode = -1;
        int Canvas_frameX = 0, Canvas_frameY = 0, Canvas_mousePrevX, Canvas_mousePrevY;
        unsigned int Canvas_zoom = 100;
        bool Canvas_dragging = false, unsaved = false;
        std::vector<bool> Canvas_boxDraggingList;
        std::vector<int> Canvas_boxXList, Canvas_boxYList, Canvas_boxWList, Canvas_boxHList;

        void Canvas_render(wxDC& dc);
        void Canvas_initializeBoxes(bool=true);

        void OnZoomIn(wxCommandEvent& event);
        void OnZoomOut(wxCommandEvent& event);
        //(*Handlers(BanyanChartFrame)
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnAdd(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
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
        static const wxWindowID idMenuZoomIn;
        static const wxWindowID idMenuZoomOut;
        static const wxWindowID idMenuAdd;
        static const wxWindowID idMenuDelete;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(BanyanChartFrame)
        wxMenu* Menu3;
        wxMenu* Menu4;
        wxMenu* Menu5;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem9;
        wxPanel* Canvas;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BANYANCHARTMAIN_H
