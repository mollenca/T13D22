all : cipher logging_cipher

cipher:
	gcc -Wall -Werror -Wextra -DCIPHER cipher.c module_io.c -o ../build/cipher

logging_cipher:
	gcc -Wall -Werror -Wextra -DLOGGING_CIPHER cipher.c logger.c module_io.c -o ../build/logging_cipher

rebuild: claen all

clean:
	-rm *.o
	-rm  ../build/*.o