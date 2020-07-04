#pragma once

#include <string>

#include <fmt/format.h>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/statline.h>

#include "Recorder.hpp"

class Main : public wxFrame
{
private:
	Recorder rec {};
	wxTimer timer {};

private:
	wxButton* m_button_startstop;
	wxStaticLine* m_staticline;
	wxStaticText* m_staticText_apm;
	wxStaticText* m_staticText_apm_v;
	wxStaticText* m_staticText_actions;
	wxStaticText* m_staticText_actions_v;
	wxStaticText* m_staticText_time;
	wxStaticText* m_staticText_time_v;

public:
	Main();

private:
	void on_click(wxCommandEvent& evt);
	void on_close(wxCloseEvent& evt);
	void on_timer(wxTimerEvent& evt);

public:
	DECLARE_EVENT_TABLE()
};