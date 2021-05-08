CFLAGS = -std=gnu89

bugz: main.c inst_set.c
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f bugz