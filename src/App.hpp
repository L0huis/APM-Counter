#pragma once

#include <thread>

#include <wx/wx.h>
#include "Main.hpp"

class App : public wxApp
{
public:
	App();

private:
	Main* m_frame1 = nullptr;

public:
	virtual bool OnInit() override;
};
