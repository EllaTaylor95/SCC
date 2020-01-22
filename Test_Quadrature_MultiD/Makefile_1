CXX = g++
RM = rm -f
INC  = -I../ODESolvers
CPPFLAGS = -std=c++11 -g $(INC)
LDFLAGS = -g 
# -L../ODESolvers
# LDLIBS = -lode 

SRCS = Vector.cpp \
       AbstractQuadrature.cpp \
       Trapezium.cpp \
       Driver.cpp 

OBJS = $(subst .cpp,.o,$(SRCS))

all: Driver

Driver: $(OBJS) 
	$(CXX) $(LDFLAGS) -o Driver $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) $(INC) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
