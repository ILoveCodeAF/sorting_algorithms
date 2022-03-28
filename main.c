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
	
	char **str = (char**)malloc(n*sizeof(char*));
	random_value_array(str, n);
	print_array(str, n);

	char **str1 = to_clone(str, n);
	char **str2 = to_clone(str, n);
	char **str3 = to_clone(str, n);
	char **str4 = to_clone(str, n);
	char **str5 = to_clone(str, n);

	double radix_sort_runtime = time_taken(&radix_sort, str1, n);
	double merge_sort_runtime = time_taken(&merge_sort, str2, n);
	double quick_sort_runtime = time_taken(&quick_sort, str3, n);
	double bubble_sort_runtime = time_taken(&bubble_sort, str4, n);
	double selection_sort_runtime = time_taken(&selection_sort, str5, n);

	printf("radix sort: %f  %s\n", radix_sort_runtime, double_to_string(radix_sort_runtime));
	printf("merge sort: %f  %s\n", merge_sort_runtime, double_to_string(merge_sort_runtime));
	printf("quick sort: %f  %s\n", quick_sort_runtime, double_to_string(quick_sort_runtime));
	printf("bubble sort: %f  %s\n", bubble_sort_runtime, double_to_string(bubble_sort_runtime));
	printf("selection sort: %f  %s\n", selection_sort_runtime, double_to_string(selection_sort_runtime));
	printf("sorted str: \n");
	print_array(str1, n);


	snprintf(buff, sizeof(buff), "HTTP/1.1 200 OK \r\nContent-Type: application/json\r\n\r\n");
	write(fd, buff, strlen(buff));

	char* json_str = array_to_json_string(str, n);
	char* json_str_key_value = pair_to_json_string("str", json_str);
	char* radix_sort_key_value = pair_to_json_string("radix_sort", double_to_string(radix_sort_runtime));
	char* merge_sort_key_value = pair_to_json_string("merge_sort", double_to_string(merge_sort_runtime));
	char* quick_sort_key_value = pair_to_json_string("quick_sort", double_to_string(quick_sort_runtime));
	char* bubble_sort_key_value = pair_to_json_string("bubble_sort", double_to_string(bubble_sort_runtime));
	char* selection_sort_key_value = pair_to_json_string("selection_sort", double_to_string(selection_sort_runtime));
	char* json_sorted_str = array_to_json_string(str1, n);
	char* json_sorted_str_key_value = pair_to_json_string("sorted_str", json_sorted_str);

	int json_response_len = strlen(json_str_key_value)
							+ strlen(radix_sort_key_value)
							+ strlen(merge_sort_key_value)
							+ strlen(quick_sort_key_value)
							+ strlen(bubble_sort_key_value)
							+ strlen(selection_sort_key_value)
							+ strlen(json_sorted_str_key_value) + 10;
	char* json_response = (char*) malloc(json_response_len*sizeof(char));
	int k = 0;
	json_response[k] = '"';
	k += 1;
	json_response[k] = '{';
	k += 1;
	k = add_two_strs(json_response, k, json_str_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, radix_sort_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, merge_sort_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, quick_sort_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, bubble_sort_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, selection_sort_key_value);
	k = add_two_strs(json_response, k, ",");
	k = add_two_strs(json_response, k, json_sorted_str_key_value);
	json_response[k] = '}';
	k += 1;
	json_response[k] = '"';
	k += 1;
	json_response[k] = '\0';

	write(fd, json_response, strlen(json_response));
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


