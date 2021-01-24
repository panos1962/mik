EXEC = mik
OBJS = global.o main.o mik.o

N_TEST = 90

$(EXEC): $(OBJS)
	cc -o $(EXEC) $(OBJS)

check: $(EXEC)
	bash check.sh $(EXEC)

test: $(EXEC)
	@echo -n "Straight (1-$(N_TEST) elements) " >&2
	@time -f '%E' ./$(EXEC) -m 1 $(N_TEST) -s
	@echo -n "Memoize (1-$(N_TEST) elements) " >&2
	@time -f '%E' ./$(EXEC) 1 $(N_TEST) -s

cleanup:
	@rm -f $(EXEC) $(OBJS)
