#pragma once
#include <chrono>

namespace alg_timer {
	class Timer {
	public:
		template<typename alg>
		static auto code_timer() {
			auto start = std::chrono::high_resolution_clock::now();

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

			return duration;
		}
	};
};