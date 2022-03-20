#include "proc.hpp"

#include <array>
#include <memory>
#include <sstream>
#include <stdexcept>

std::string proc::exec(const std::string& cmd)
{
	std::array<char, 256> buf{};
	std::stringstream stream;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe)
		throw std::runtime_error("failed to run popen()");
	while (fgets(buf.data(), buf.size(), pipe.get()) != nullptr)
		stream << buf.data();
	return stream.str();
}
std::string proc::avrdude(const std::string& port, const std::string& file)
{
	std::stringstream stream;
	stream << "avrdude -p m8 -c avrispv2 -P " << port << " -U flash:w:" << file;
	return exec(stream.str());
}
