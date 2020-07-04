#pragma once

#include <array>
#include <thread>
#include <atomic>
#include <numeric>
#include <chrono>

#include <Windows.h>

using f_minutes = std::chrono::duration<double, std::ratio<60>>;

class Recorder
{
private:
	std::chrono::high_resolution_clock::time_point start;
	std::atomic<bool> recording { false };
	std::array<bool, 0xFF> previous_state { false };
	std::thread recorder {};

public:
	f_minutes duration { 0.0 };
	std::array<int, 0xFF> counters { 0 };

private:
	void recorder_worker();

public:
	bool is_recording() const;
	void start_recording();
	void stop_recording();
	double get_minutes_passed() const;
	int get_number_actions() const;
};
