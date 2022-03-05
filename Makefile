all: compile

compile:
	@g++ main.cpp -g -o main

run:
	@./main

clean:
	@echo "Clean executable file."
	@rm main
