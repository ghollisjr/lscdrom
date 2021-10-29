lscdrom:lscdrom.cc
	g++ -std=c++14 lscdrom.cc -lOptions -o lscdrom
clean:
	rm -f lscdrom
