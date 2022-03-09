all: compile

compile:
	@g++ main.cpp -g -o main
	@g++ heart.cpp -g -o heart
	@g++ donuts.cpp -g -o donuts

run:
	@./main

clean:
	@echo "Clean executable file."
	@rm main heart donuts
