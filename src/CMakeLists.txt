
add_executable(
	APM-Counter WIN32
	App.hpp
	App.cpp
	Main.hpp
	Main.cpp
	Recorder.hpp
	Recorder.cpp
)

target_link_libraries(
	APM-Counter PRIVATE 
	project_options
	project_warnings
	CONAN_PKG::docopt.cpp
	CONAN_PKG::fmt
	CONAN_PKG::spdlog
	CONAN_PKG::wxwidgets
)


