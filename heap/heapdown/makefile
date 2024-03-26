compile:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o heapify-down heapify-down.c -lm


valgrind:
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./heapify-down

docker:
	docker build --tag heapify-down .

run:
	docker run -v "$(CURDIR)":/heapify-down -it heapify-down

clean:
	rm -f heapify-down
	docker rmi -f heapify-down
