/***************************************************************
 * Name:      BanyanChartMain.h
 * Purpose:   Defines Application Frame
 * Author:    lunanerdderg ()
 * Created:   2026-09-16
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:
 **************************************************************/

#ifndef BANYANCHARTMAIN_H
#define BANYANCHARTMAIN_H

//(*Headers(BanyanChartFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class BanyanChartFrame: public wxFrame
{
    public:

        BanyanChartFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BanyanChartFrame();

    private:

        //(*Handlers(BanyanChartFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(BanyanChartFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(BanyanChartFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BANYANCHARTMAIN_H
