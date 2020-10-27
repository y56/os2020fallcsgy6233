ref:
https://stackoverflow.com/questions/2353371/how-to-do-an-atomic-increment-and-fetch-in-c


gcc -std=c99 -Wall -Wextra -pedantic -o test.out ./test.c -pthread && ./test.out 

gcc -o test2.out test2.c && ./test2.out

gcc -std=c99 -Wall -Wextra -pedantic -o main.out ./main.c -pthread && ./main.out

