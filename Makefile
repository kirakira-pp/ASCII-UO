all: compile run

compile:
	@g++ main.cpp -o main

run:
	@./main

clean:
	@echo "Clean executable file."
	@rm main
