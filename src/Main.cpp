
#include "Main.hpp"

Main::Main()
	: wxFrame(nullptr, 101, "APM", wxDefaultPosition, wxDefaultSize,
			  wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_button_startstop = new wxButton(this, 10001, wxT("Start Recording"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button_startstop, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticline = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer1->Add(m_staticline, 0, wxEXPAND | wxALL, 5);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->AddGrowableCol(0);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->SetFlexibleDirection(wxVERTICAL);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_apm = new wxStaticText(this, wxID_ANY, wxT("APM:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_apm->Wrap(-1);
	fgSizer1->Add(m_staticText_apm, 0, wxALIGN_RIGHT | wxALL, 5);

	m_staticText_apm_v = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_apm_v->Wrap(-1);
	fgSizer1->Add(m_staticText_apm_v, 0, wxALL, 5);

	m_staticText_actions = new wxStaticText(this, wxID_ANY, wxT("Actions:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_actions->Wrap(-1);
	fgSizer1->Add(m_staticText_actions, 0, wxALIGN_RIGHT | wxALL, 5);

	m_staticText_actions_v = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_actions_v->Wrap(-1);
	fgSizer1->Add(m_staticText_actions_v, 0, wxALL, 5);

	m_staticText_time = new wxStaticText(this, wxID_ANY, wxT("Minutes passed:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_time->Wrap(-1);
	fgSizer1->Add(m_staticText_time, 0, wxALIGN_RIGHT | wxALL, 5);

	m_staticText_time_v = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_time_v->Wrap(-1);
	fgSizer1->Add(m_staticText_time_v, 0, wxALL, 5);

	bSizer1->Add(fgSizer1, 1, wxEXPAND, 5);

	this->SetBackgroundColour(wxColour(0xffffff));
	this->SetSizer(bSizer1);
	this->Layout();
	this->Fit();

	this->Centre(wxBOTH);

	timer.Bind(wxEVT_TIMER, &Main::on_timer, this);
}

void Main::on_click(wxCommandEvent& evt)
{
	if (rec.is_recording())
	{
		m_button_startstop->SetLabel(wxT("Start Recording"));
		rec.stop_recording();
		timer.Stop();
	}
	else
	{
		m_button_startstop->SetLabel(wxT("Stop Recording"));
		rec.start_recording();
		timer.Start();
	}
	evt.Skip();
}

void Main::on_close(wxCloseEvent& evt)
{
	if (rec.is_recording()) rec.stop_recording();

	auto apm = double(rec.counters[0]) / rec.duration.count();

	evt.Skip();
}

void Main::on_timer(wxTimerEvent& evt)
{
	auto time = rec.get_minutes_passed();
	auto actions = rec.get_number_actions();
	m_staticText_apm_v->SetLabel(fmt::format("{:.2f}", actions / time));
	m_staticText_actions_v->SetLabel(fmt::format("{}", actions));
	m_staticText_time_v->SetLabel(fmt::format("{:.2f}", time));

	evt.Skip();
}

BEGIN_EVENT_TABLE(Main, wxFrame)
EVT_BUTTON(10001, Main::on_click)
EVT_CLOSE(Main::on_close)
END_EVENT_TABLE()
