#include <string>
#include <chrono>

#pragma once

namespace Noted {
	class Note {
		public:
			Note();
			Note(std::string note);
			std::string contents;
			std::chrono::time_point<std::chrono::system_clock> created_at;
	};
}
