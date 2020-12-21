CC = gcc
src = source/
script_names = basic_hash hash_table
prereq0 = $(foreach wrd, $(script_names), $(src)$(wrd).c)
prereq1 = $(foreach wrd, $(script_names), $(src)$(wrd).o)

hash_table.so: $(prereq1)
	$(CC) -shared -o libhash_table.so hash_table.o
	$(CC) -shared -o libbasic_hash.so basic_hash.o
	rm -f *.o

$(prereq1): $(prereq0)
	$(CC) -Wall -fPIC -c $(src)*.c

.PHONY = clean
clean:
	rm -f *.o
	rm -f hash_table.so