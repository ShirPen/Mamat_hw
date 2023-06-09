CXX=g++
CXXLINK=$(CXX)
CXXFLAGS= -g -Wall -std=c++11
OBJS= port.o ip.o string.o
RM= rm -rf

firewall.exe: main.o libfirewall.so 
	$(CXXLINK) $(CCFLAGS) main.o -o firewall.exe -lfirewall -linput -L.

libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so 

port.o: port.cpp port.h string.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic port.cpp 

ip.o: ip.h ip.cpp string.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic ip.cpp

string.o: string.h string.cpp
	$(CXXLINK) $(CXXFLAGS) -c -fpic string.cpp 

main.o: main.cpp string.h ip.h port.h input.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic main.cpp 

clean:
	$(RM) *.o libfirewall.so