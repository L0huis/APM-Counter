#include <catch2/catch.hpp>

#include "../src/Recorder.hpp"

TEST_CASE("Starting/Stopping recording is indempotent", "[factorial]")
{
	Recorder r;

	r.start_recording();
	REQUIRE(r.is_recording() == true);
	for (int i = 0; i < 10; i++)
	{
		r.start_recording();
		REQUIRE(r.is_recording() == true);
	}

	r.stop_recording();
	REQUIRE(r.is_recording() == false);

	for (int i = 0; i < 10; i++)
	{
		r.stop_recording();
		REQUIRE(r.is_recording() == false);
	}
}
