## Compiler and flags
CC = gcc
CFLAGS = -I/opt/local/include/ -g
GSL_LDFLAGS = -L/opt/local/lib/ -lgsl -lgslcblas -lm
FORTRAN_LDFLAGS = -lgfortran

# Fortran compiler and flags
FC = gfortran
FFLAGS = -g

## PATHS
INCLUDES = -I../source
vpath %.c .:..:../source
vpath %.f90 .:..:../source
vpath %.f .:..:../source
vpath %.o .:..:../source

## Implicit rules
%.o:  %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $*.o
%.o:  %.f90
	$(FC) $(FFLAGS) $(INCLUDES) -c $< -o $*.o
%.o:  %.f
	$(FC) $(FFLAGS) $(INCLUDES) -c $< -o $*.o

## Executables
TEST_3J_M_F77 = test_3j_m.o slatec_3j_f77.o slatec_3j_C.o
TEST_3J_M_F90 = test_3j_m.o slatec_3j_f90.o slatec_3j_C.o
TEST_3J_L = test_3j_l.o slatec_3j_f90.o slatec_3j_C.o
TEST_3J_L_CWRAPPER = test_3j_l_wrapper.o slatec_c_interface.o slatec_3j_f90.o
TEST_3J_GSL = test_3j_gsl.o
TEST_6J = test_6j.o slatec_3j_f90.o slatec_3j_C.o
TEST_DBES = test_dbes.o slatec_3j_f90.o
TEST_BES = test_bes.o slatec_3j_f90.o

## Rules
all: test_3j_m_f77 test_3j_m_f90 test_3j_l test_3j_l_cwrapper test_3j_gsl test_6j test_dbes test_bes
default: test_3j_l

test_3j_m_f77: $(TEST_3J_M_F77)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_3j_m_f90: $(TEST_3J_M_F90)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_3j_l: $(TEST_3J_L)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_3j_l_cwrapper: $(TEST_3J_L_CWRAPPER)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_3j_gsl: $(TEST_3J_GSL)
	$(CC) $(GSL_LDFLAGS) -o $@ $^
test_6j: $(TEST_6J)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_dbes: $(TEST_DBES)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
test_bes: $(TEST_BES)
	$(CC) $(FORTRAN_LDFLAGS) -o $@ $^
clean:
	rm -rf *.o


