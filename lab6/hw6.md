# a)
socket() – opens a socket (similar to pipe() )
connect() – connects to a server
bind() – assigns a particular port number to the
listen() – listens to connection requests from
accept() – accepts a connection from client
write() – writes a buffer to server, just as in file read() – reads a buffer from client, just as in file or pipe writing or pipe reading 
close() – closes the socket
## 1. 
### Which of the calls above are blocking and which are not? 

* blocking:
    * socket(): same w/ fopen
    * connect(): wait for handshake
        * ref: https://stackoverflow.com/questions/8258107/does-connect-block-for-tcp-socket
    * write(): just like pipea
    * read()
    * close()
        * ref: https://unix.stackexchange.com/questions/145526/can-close-block
    * accept():
        * ref: https://stackoverflow.com/questions/31114477/c-server-side-not-blocking-on-listen
* nonblocking:
    * listen()
        * ref: https://stackoverflow.com/questions/31114477/c-server-side-not-blocking-on-listen
* not sure:

### Explain what that means? 
blocking: wait for I/O to complete then go back to user mode
nonblocking: go to user mode first, then later on, kernel will inform that the I/O is done
### Is this a form of direct communications or indirect communications?
## 2. How would you change your program to communicate between processes in a different
machine?
