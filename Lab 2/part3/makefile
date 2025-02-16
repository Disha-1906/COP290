list:
	gcc -o obj/list_test.o test/list_test.c src/list.c
	./obj/list_test.o  -I include/
doc:
	doxygen Doxyfile
clean:
	rm -f obj/*
	rm -fr doc/*
test:
	gcc -g3 -o obj/main.o test/main.c src/list.c src/hm.c src/mythread.c -I include/ -pthread
	./obj/main.o data/in1.txt data/in2.txt data/in3.txt data/in4.txt

.PHONY: all test clean
