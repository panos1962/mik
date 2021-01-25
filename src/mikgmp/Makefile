EXEC = mik.exe
OBJS = global.o main.o mik.o

$(EXEC): $(OBJS)
	cc -o $(EXEC) $(OBJS) -lgmp

test: $(EXEC)
	@bash test.sh ./$(EXEC)

check: $(EXEC)
	@bash check.sh ./$(EXEC)

cleanup:
	@rm -f $(EXEC) $(OBJS)
