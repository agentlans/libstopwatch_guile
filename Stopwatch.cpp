#include "Stopwatch.hpp" // C++
#include <libguile.h>

extern "C" {
#include "stopwatch.h" // C header
}

#define OBJ static_cast<Stopwatch*>(sw)

stopwatch_t stopwatch_new() {
    return new Stopwatch();
}

void stopwatch_free(stopwatch_t sw) {
    delete static_cast<Stopwatch*>(sw);
}

void stopwatch_start(stopwatch_t sw) {
    OBJ->start();
}

void stopwatch_stop(stopwatch_t sw) {
    OBJ->stop();
}

void stopwatch_reset(stopwatch_t sw) {
    OBJ->reset();
}

double stopwatch_time(stopwatch_t sw) {
    return OBJ->time();
}

int stopwatch_is_running(stopwatch_t sw) {
    return OBJ->is_running();
}
