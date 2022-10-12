#ifndef _STOPWATCHC
#define _STOPWATCHC

typedef void* stopwatch_t;

stopwatch_t stopwatch_new();
void stopwatch_free(stopwatch_t sw);

void stopwatch_start(stopwatch_t sw);
void stopwatch_stop(stopwatch_t sw);
void stopwatch_reset(stopwatch_t sw);

double stopwatch_time(stopwatch_t sw);
int stopwatch_is_running(stopwatch_t sw);

#endif