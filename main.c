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
#define MAX_LINE 4096

void read_file_and_send(int fd, char *filename) {
	int nread = 0;
	char buff[MAX_LINE] = {0};
	snprintf(buff, sizeof(buff), "HTTP/1.1 200 OK \r\nContent-Type: text/html\r\n\r\n");
	write(fd, buff, strlen(buff));

	FILE *fp;
	fp = fopen(filename, "r");
	if (fp) {
		while ((nread = fread(buff, 1, MAX_LINE, fp)) > 0) {
			write(fd, buff, nread);
		}
		fclose(fp);
	}
	else {
		printf("failed to read file\n");
	}
}

void _index(int fd) {
	read_file_and_send(fd, "templates/index.html");
}

void page_not_found404(int fd) {
	read_file_and_send(fd, "templates/404.html");
}

void compare_sort_algorithm(int fd, int n) {
	char buff[MAX_LINE] = {0};
	snprintf(buff, sizeof(buff), "HTTP/1.1 200 OK \r\nContent-Type: application/json\r\n\r\n");
	write(fd, buff, strlen(buff));
}

void handle_http_request(int fd) {
	printf("call in handle func\n");
	char recvline[MAX_LINE] = {0};

	int n = read(fd, recvline, MAX_LINE);
	fprintf(stdout, "\n%s\n", recvline);

	char method[10];
	int i = 0;
	while(recvline[i] != ' ') {
		method[i] = recvline[i];
		i += 1;
	}
	method[i] = '\0';
	printf("\nmethod: %s\ni=%d\n", method, i);
	char addr[50];
	
	i += 1;
	int j = 0;
	while(recvline[i] != ' ' && j < 49) {
		addr[j] = recvline[i];
		i += 1;
		j += 1;
	}
	addr[j] = '\0';
	printf("addr: %s\n", addr);

	n = 0;
	if(strlen(addr) > 5)
		if(addr[0] == '/' && addr[1] == '?'
				&& addr[2] == 'n' && addr[3] == '=') {
			i = 4;
			while(i < strlen(addr)) {
				n = n*10 + (addr[i]-'0');
				i += 1;
			}
		}

	if(n > 0) {
		printf("call compare sort algorithm func: n = %d\n", n);
		compare_sort_algorithm(fd, n);
		return;
	}	

	if (strcmp(addr, "/") == 0) {
		_index(fd);
		return;
	}

	page_not_found404(fd);
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
