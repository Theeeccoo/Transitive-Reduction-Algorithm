CFLAGS = -Wall -Wextra -Werror

.PHONY: dir
.PHONY: graph
	

all: graph run clean

graph:
	gcc $(CFLAGS) $(CURDIR)/*.c -o out

run:
	@./out

clean:
	@rm -f out

