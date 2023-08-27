#include <sys/socket.h>

main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    return 0; 
}