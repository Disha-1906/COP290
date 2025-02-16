list:
	gcc -o obj/list_test.o test/list_test.c src/list.c -I include/
	./obj/list_test.o
hashmap:
	gcc -o obj/hashmap_test.o test/hashmap_test.c src/list.c src/hm.c src/mythread.c -I include/
	./obj/hashmap_test.o
clean:
	rm -f obj/*
main:
	gcc -g3 -o obj/main.o test/main.c src/list.c src/hm.c src/mythread.c -I include/
	./obj/main.o data/in1.txt data/in2.txt data/in3.txt data/in4.txt



