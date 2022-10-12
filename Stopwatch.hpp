#ifndef _STOPWATCH
#define _STOPWATCH

#include <chrono>

class Stopwatch {
public:
    typedef std::chrono::steady_clock Clock;
    typedef Clock::duration Duration;
    Stopwatch() : t(Duration(0)) {}
    // Starts timing. Is idempotent.
    void start() {
    	if (!running) {
	    	t0 = Clock::now();
    		running = true;
    	}
    }
    // Stops timing. Is idempotent.
    void stop() {
    	if (running) {
	    	auto t1 = Clock::now();
    		auto delta_t = t1 - t0;
    		t += delta_t;
	    	running = false;
	    }
    }
    // Resets the total time to 0.
    // Doesn't affect stopwatch running state.
    void reset() {
    	t = Duration(0);
    }
    // Returns how much time has elapsed.
    double time() {
    	return convert_to_seconds(t);
    }
    // Whether stopwatch is running.
    bool is_running() const {
    	return running;
    }
private:
    double convert_to_seconds(const Duration& d) {
        typedef std::chrono::duration<double> DDuration;
        DDuration ts = std::chrono::duration_cast<DDuration>(d);
        return ts.count();
    }
    Clock::duration t;
    std::chrono::time_point<Clock> t0;
    bool running = false;
};

#endif