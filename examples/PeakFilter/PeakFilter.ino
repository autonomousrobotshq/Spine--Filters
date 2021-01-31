#include "PeakFilter.hpp"

const int samplecount = 5;
const int samples[] = { 1, 1, 1, 5, 7 };

PeakFilter<int> filter(samplecount);

void setup() {
}

void loop() {
	filter.Reset();
	for (int i = 0; i < samplecount; i++)
		filter.NewReading(samples[i]);
	const int16_t f_avg = filter.GetFilteredSignal();
}
