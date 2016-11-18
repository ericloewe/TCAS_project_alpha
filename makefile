all: AC_sim.cpp AC_sim.h TCAS_defs.cpp TCAS_defs.h TCAS_main.cpp TCAS_sim.h TCAS_sim.cpp
	g++ -std=c++11 -o TCAS AC_sim.cpp TCAS_defs.cpp TCAS_main.cpp TCAS_sim.cpp

memBuffTest: TCAS_comms.h TCAS_comms.cpp memBuffTest.cpp
	g++ -std=c++11 -o memBuffTest TCAS_comms.cpp memBuffTest.cpp

