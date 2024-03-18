EXECUTABLE = ejercicios-strings

compile:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o $(EXECUTABLE) $(EXECUTABLE).c -lm


valgrind: $(EXECUTABLE)
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXECUTABLE)

docker: $(EXECUTABLE)
	docker build --tag ejercicios-strings .

run: docker
	docker run -v "$(CURDIR)":/ejercicios-strings -it ejercicios-strings

clean:
	rm -f $(EXECUTABLE)
	docker rmi -f ejercicios-strings
