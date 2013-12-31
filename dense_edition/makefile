objects = basic.o vectorization.o change_calculate_order.o divide_matrix.o generate.o
cc = g++
compile_tag = -fopenmp

main: main.cpp $(objects)
	$(cc) $(compile_tag) main.cpp $(objects) -o main

# generate matrix
generate.o: generate_random_matrix.cpp
	$(cc) $(compile_tag) -c generate_random_matrix.cpp -o generate.o
# step1: basic_method
basic.o: 1_basic_method.cpp
	$(cc) $(compile_tag) -c 1_basic_method.cpp -o basic.o
# step2: vectorization_method
vectorization.o: 2_vectorization_method.cpp
	$(cc) $(compile_tag) -c 2_vectorization_method.cpp -o vectorization.o
# step3: hange_calculate_order_method
change_calculate_order.o: 3_change_calculate_order_method.cpp
	$(cc) $(compile_tag) -c 3_change_calculate_order_method.cpp -o change_calculate_order.o
#step4: 
divide_matrix.o: 4_divide_matrix_mothod.cpp
	$(cc) $(compile_tag) -c 4_divide_matrix_mothod.cpp -o divide_matrix.o

.PHONY: clean
clean:
	rm main $(objects)
