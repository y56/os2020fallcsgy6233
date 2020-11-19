# compile and run
gcc -o server.out server.c && ./server.out
gcc -o client.out client.c && ./client.out 15 3

gcc -o  hw4_2v2_modified.out  hw4_2v2_modified.c -lrt && gcc -o  ./hw4_2v2_modified.out 

# ref

https://www.cnblogs.com/straight/articles/7660889.html

# instuctions for TA

Update 11/16 2am:

Please make sure you are connecting to 127.0.0.1, which is the local host address. Do not use your device IP since the testing environment has different IP address than yours.

-----------------------------------------

Update 11/16, 1am:

Some of you might find that sometimes the program runs fine but sometimes it fails on bind. This is because of something called TCP TIME_WAIT state. You will need to enable SO_REUSEADDR if you have this problem.

For the detail of this problem: https://hea-www.harvard.edu/~fine/Tech/addrinuse.html

For the solution of this: https://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr

-----------------------------------------

Update 11/16, 12am: Fixed a problem in the script. Please update your script if you have previously downloaded it.

-----------------------------------------

Hi all,



For assignment 6, please make sure your submission has the following format:

hw6.zip
 +-- a.producer.c
 +-- a.consumer.c
 +-- b.c
 +-- screenshot.jpg   <--- a single screenshot file. If you have multiple screenshots please make them into one.

You should submit a single zip file WITHOUT ANY internal sub-directories.

For your text answers to question (a) and (b), please use the NYU Classes text box when submitting. Do not put a text or PDF file in your zip.

Also, please make sure your programs can run with the attached script. To run the script, put it in the same directory of your source files, and then run "bash ./grader.sh". It will automatically compile and run your programs. You might need to install the "timeout" and "procps" packages if it prompts for missing something. On Ubuntu systems this can be done by simply "apt install timeout procps". Do not include the script in your submission.

If you have any trouble running the script, please let me know.



-Yang
