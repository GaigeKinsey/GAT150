#pragma once
#include <chrono>

template <typename TPeriod = std::chrono::high_resolution_clock::period>
class timer {
public:
	using clock = std::chrono::high_resolution_clock;
	using clock_duration = std::chrono::duration<clock::rep, TPeriod>;

public:
	timer() : m_start_point(clock::now()) {}

	void reset() { m_start_point = clock::now(); }

	clock::rep elapsed_time() const {
		clock_duration duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_start_point);
		return duration.count();
	}

	double seconds() {
		clock_duration duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_start_point);
		return duration.count() / static_cast<double>(TPeriod::den);
	}

private:
	clock::time_point m_start_point;
};

class frame_timer : public timer<> {
public:
	frame_timer() : m_dt(0.0f), m_fps(0.0f), m_frame_count(0) { m_start_frame_time = clock::now(); }

	void tick() {
		clock_duration duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_prev_frame_time);
		m_prev_frame_time = clock::now();
		m_dt = duration.count() / static_cast<double>(std::chrono::high_resolution_clock::period::den);
		m_frame_count++;

		if (m_frame_count == 100.0f) {
			duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_start_frame_time);
			m_start_frame_time = clock::now();
			float elapsed = duration.count() / static_cast<double>(std::chrono::high_resolution_clock::period::den);
			m_fps = m_frame_count / elapsed;
			m_frame_count = 0;
		}
	}

	float dt() const { return m_dt; }
	float fps() const { return m_fps; }

private:
	float m_dt;
	float m_fps;
	size_t m_frame_count;
	clock::time_point m_prev_frame_time;
	clock::time_point m_start_frame_time;
};

extern frame_timer g_timer;

using ns_timer = timer<std::nano>;
using mi_timer = timer<std::micro>;
using ms_timer = timer<std::milli>;
using s_timer = timer <std::ratio<1, 1>>;