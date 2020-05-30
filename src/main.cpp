#include <iostream>
#include <array>

#include <spdlog/spdlog.h>

#include <docopt/docopt.h>

static constexpr auto USAGE = R"(
C++ Weekly Game.
    Usage:
          game [options]

  Options:
          -h --help         Show this screen.
          --width=WIDTH     Screen width in pixels [default: 1024].
          --height=HEIGHT   Screen height in pixels [default: 768].
          --scale=SCALE     Scaling factor [default: 1].
)";

int main(int argc, const char **argv)
{
	std::map<std::string, docopt::value> args = docopt::docopt(USAGE, { std::next(argv), std::next(argv, argc) },
															   true,		 // show help if requested
															   "Game 0.0");	 // version string

	const auto width = args["--width"].asLong();
	const auto height = args["--height"].asLong();
	const auto scale = args["--scale"].asLong();


	return 0;
}
