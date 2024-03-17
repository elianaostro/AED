compile:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o ejercicio-tap ejercicio-tap.c -lm


valgrind:
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./ejercicio-tap

docker:
	docker build --tag ejercicio-tap .

run:
	docker run -v "$(CURDIR)":/ejercicio-tap -it ejercicio-tap

clean:
	rm -f ejercicio-tap
	docker rmi -f ejercicio-tap
