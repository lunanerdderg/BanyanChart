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
        wxFont font;
        FileParser File;

        bool unsaved = false;
        const int boxWidth = 200, boxHeight = 75;

        void changeText(std::string, size_t, size_t=0); void changeText(wxString, size_t, size_t=0); void changeText(const char[], size_t, size_t=0); void changeText(size_t, size_t=0);

        // Canvas
        int Canvas_frameX = 0, Canvas_frameY = 0, Canvas_mousePrevX, Canvas_mousePrevY;
        unsigned int Canvas_zoom = 100;
        bool Canvas_dragging = false, Canvas_boxMoved = false;
        std::vector<bool> Canvas_boxDraggingList, Canvas_selectedBlock, Canvas_selectedNode;
        std::vector<double> Canvas_boxXList, Canvas_boxYList, Canvas_boxWList, Canvas_boxHList;

        double Canvas_getXPosition(double);
        double Canvas_getYPosition(double);
        double Canvas_getProportions(double=1, bool=false);

        void Canvas_render(wxDC&);
        void Canvas_initializeBoxes(bool=true);

        // ///////////////////////////
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);

        void OnEditText(wxCommandEvent& event);
        void OnAddBlock(wxCommandEvent& event);
        void OnAddNode(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);

        void OnZoomIn(wxCommandEvent&);
        void OnZoomOut(wxCommandEvent&);
        //(*Handlers(BanyanChartFrame)
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
        void doubleClick(wxMouseEvent& event);
        //*)

        //(*Identifiers(BanyanChartFrame)
        static const wxWindowID ID_CANVAS;
        static const wxWindowID idMenuNew;
        static const wxWindowID idMenuOpen;
        static const wxWindowID idMenuSave;
        static const wxWindowID idMenuSaveAs;
        static const wxWindowID idMenuQuit;
        static const wxWindowID idMenuEditText;
        static const wxWindowID idMenuAddBlock;
        static const wxWindowID idMenuAddNode;
        static const wxWindowID idMenuDelete;
        static const wxWindowID idMenuZoomIn;
        static const wxWindowID idMenuZoomOut;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(BanyanChartFrame)
        wxMenu* Menu3;
        wxMenu* Menu5;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem12;
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
