TARGET		=  matrix_oop.a
CC 			=  g++ -g -pedantic -std=c++17
CFLAGS 		=  -fno-stack-protector  -Wall -Wextra -Werror 
TEST_FLAGS  =   $(shell pkg-config --cflags --libs gtest) 
GFLAGS      = -fprofile-arcs -coverage  -ftest-coverage 
SRC			=  $(wildcard matrix_oop.cc matrix_exception.cc)
OBJ			=  $(patsubst %.cc, $(WAY_OBJ)%.o, $(SRC))
OS		   :=  $(shell uname -s)
PATH_TEST	= ./tests/
WAY_OBJ     = ./object_files/
SKIP_D      = '*/testdemo.cpp' '*/pointer_traits.h' '*/compressed_pair.h' '*/allocator.h'\
			'*/iomanip' '*/istream' '*/stdlib.h' '*/exception' '*/sstream' '*/locale' '*/__locale'\
			'*/streambuf' '*/ios' '*/string' '*/__debug' '*/ostream' '*/cstring' '*/__iterator/ostreambuf_iterator.h'\
			'*/__memory/allocator.h''*/__memory/pointer_traits.h''*/__memory/compressed_pair.h'\
			'*/__string/char_traits.h' '*/__utility/swap.h' '*/opt/*' '*/__*'


all: clean $(TARGET) test


$(TARGET): clean $(OBJ)
	ar rc $(TARGET)  $(OBJ)

 $(WAY_OBJ)%.o: %.cc
	$(CC) $(CFLAGS) -c  $<   -o  $@ 

test: test_all
	./test

test_all:  test.o $(OBJ) 
	@$(CC)  $(WAY_OBJ)*.o  -o test  $(TEST_FLAGS) 

test.o: 
	$(CC) $(CFLAGS) -c ${PATH_TEST}testdemo.cpp -o $(WAY_OBJ)test.o

clean:
	rm -f test
	rm -rf report
	rm -f *.o *.a a.out
	@rm -f *.gcda  *.gcno *.gcov
	@rm -f ${PATH_TEST}*.gcda  ${PATH_TEST}*.gcno ${PATH_TEST}*.gcov
	rm -f $(WAY_OBJ)*.o
	rm -f *.a *.log
	rm -f ${PATH_TEST}test ${PATH_TEST}testdemo_gcov ${PATH_TEST}*.info 
	rm -rf ${PATH_TEST}testdemo_gcov*
	rm -rf ${PATH_TEST}test.* ${PATH_TEST}gcov_report.*


gcov_report: clean
	$(CC) ${GFLAGS} $(SRC)  ${PATH_TEST}testdemo.cpp   -o ${PATH_TEST}testdemo_gcov $(TEST_FLAGS) -std=c++17
	${PATH_TEST}./testdemo_gcov
	lcov -k . -b .  -d .  -c  -t "test" --output-file  ${PATH_TEST}test.info 
	lcov  -r tests/test.info '/usr/*' ${SKIP_D}   -o tests/test.info 
	genhtml -o report tests/test.info
	# @rm -f *.gcda  *.gcno

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
endif

clang:
	clang-format -n -style=google *.cc *.h

clangI:
	clang-format -i -style=google *.cc *.h

leak: test_all
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./test
endif	

test_docker: clean
	docker build  -f Dockerfile  -t test_matrix:cpp .
	docker run -t --name matrix_cpp test_matrix:cpp
	docker cp matrix_cpp:/code/report/ .
	docker cp matrix_cpp:/code/leak.log .
	docker rm matrix_cpp
	docker rmi test_matrix:cpp

docker_clean:
	docker rm matrix_cpp
	docker rmi test_matrix:cpp