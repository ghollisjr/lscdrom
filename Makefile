lscdrom:lscdrom.cc
	g++ -std=c++14 lscdrom.cc -lOptions -o lscdrom
install: lscdrom
	cp lscdrom ${HOME}/bin
clean:
	rm -f lscdrom
