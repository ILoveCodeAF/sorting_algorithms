#include <stdio.h>
#include "sort_algorithms.h"
#include "utils.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define MAX_LINE 1024

void handle_http_request(int fd) {
	printf("call in handle func\n");
	char buff[MAX_LINE] = {0};
	char recvline[MAX_LINE] = {0};

	int n = read(fd, recvline, MAX_LINE);
	fprintf(stdout, "\n%s\n", recvline);
		
	snprintf(buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");
	
	printf("%s\n", buff);
	write(fd, buff, strlen(buff));
	//send(fd, buff, strlen(buff), 0);
	printf("done.\n");
}


int main(int argc, char **argv) {
	int listenfd, connfd;
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	int opt = 1;


	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket error");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        fprintf(stderr, "setsockopt");
        exit(EXIT_FAILURE);
    }

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (bind(listenfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(listenfd, 3) < 0) {
		fprintf(stderr, "listen error");
		exit(EXIT_FAILURE);
	}

	while(1) {
		connfd = accept(listenfd, (struct sockaddr *) &addr, (socklen_t*)&addrlen);
		
		if (connfd < 0) {
			fprintf(stderr, "accept");
			continue;
		}

		printf("handle request\n");

		handle_http_request(connfd);
		close(connfd);
	}



	return 0;
}

/*int main(int argc, char **argv) {
	int len = 20000;
	char **str = (char**)malloc(len*sizeof(char*));
	random_value_array(str, len);
	print_array(str, len);
	
	char **str3 = to_clone(str, len);
	//quick_sort(str3, len);
	printf("%s time taken: %f \n", "quick sort", time_taken(&quick_sort, str3, len));
	//print_array(str3, len);

	char **str4 = to_clone(str, len);
	//merge_sort(str4, len);
	printf("%s time taken: %f \n", "merge sort", time_taken(&merge_sort, str4, len));
	//print_array(str4, len);

	char **str5 = to_clone(str, len);
	//radix_sort(str5, len);
	printf("%s time taken: %f \n", "radix sort", time_taken(&radix_sort, str5, len));
	//print_array(str5, len);
	
	char **str1 = to_clone(str, len);
	bubble_sort(str1, len);
	printf("%s time taken: %f \n", "bubble sort", time_taken(&bubble_sort, str1, len));
	//print_array(str1, len);
	
	char **str2 = to_clone(str, len);
	selection_sort(str2, len);
	printf("%s time taken: %f \n", "selection sort", time_taken(&selection_sort, str2, len));
	//print_array(str2, len);


	return 0;
}*/
