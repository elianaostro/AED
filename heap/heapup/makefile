compile:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o heapify-up heapify-up.c -lm


valgrind:
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./heapify-up

docker:
	docker build --tag heapify-up .

run:
	docker run -v "$(CURDIR)":/heapify-up -it heapify-up

clean:
	rm -f heapify-up
	docker rmi -f heapify-up

local:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o heapify-up heapify-up.c -lm
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./heapify-up

