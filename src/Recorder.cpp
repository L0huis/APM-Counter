#include "Recorder.hpp"

bool Recorder::is_recording() const
{
	return recording;
}

void Recorder::start_recording()
{
	stop_recording();
	counters = std::array<int, 0xFF> { 0 };
	recording = true;
	start = std::chrono::high_resolution_clock::now();
	recorder = std::thread([this] { recorder_worker(); });
}

void Recorder::stop_recording()
{
	recording = false;
	if (recorder.joinable()) recorder.join();
	duration = std::chrono::duration_cast<f_minutes>(std::chrono::high_resolution_clock::now() - start);
	counters[0] = std::accumulate(counters.begin(), counters.end(), 0);
}

void Recorder::recorder_worker()
{
	while (recording)
		for (int i = 1; i < 0xFF; i++)
		{
			counters[i] += !!GetAsyncKeyState(i) && !previous_state[i];
			counters[0] += !!GetAsyncKeyState(i) && !previous_state[i];
			previous_state[i] = !!GetAsyncKeyState(i);
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
}

double Recorder::get_minutes_passed() const
{
	return std::chrono::duration_cast<f_minutes>(std::chrono::high_resolution_clock::now() - start).count();
}

int Recorder::get_number_actions() const
{
	return counters[0];
}
