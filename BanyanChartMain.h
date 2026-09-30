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

        BanyanChartFrame(wxWindow* parent,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size);
        virtual ~BanyanChartFrame();

    private:
        FileParser File{};

        //(*Handlers(BanyanChartFrame)
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
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
