# AHRS-Performance-Analysis-Optimization
This project profiles and optimizes the execution time of Madgwick's MARG filter  for Attitude and Heading Reference System (AHRS) on BeagleBone Black Wireless.

The program calculates repeatable pseudorandom input data (e.g. using the rand or random function) within the following ranges:
o a_x, a_y, a_z: [-10.0, 10.0] g
o w_x, w_y, w_z: [-1000.0, 1000.0] radians/sec
o m_x, m_y, m_z: [-100.0, 100.0] microtesla
Next it calls  optimized function with the input data, measuring its duration with clock_gettime and compares the outputs against the expected outputs (from the original function).
Optimization steps followed are:
Follow this basic optimization process for this project:
1. Use perf (or gprof) to profile the application and find the dominant instructions. Use clock_gettime to measure time durations.
2. Examine the object code and compare it with the source code.
3. Tune the compiler flags and the source code to improve the execution time.
