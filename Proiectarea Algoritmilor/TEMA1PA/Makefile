# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: feribot nostory

run-p1:
	./feribot
run-p2:
	./nostory

# Nu uitați să modificați numele surselor și, eventual, ale executabilelor.
feribot: feribot.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
nostory: nostory.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
# Vom șterge executabilele.
clean:
	rm -f feribot nostory
