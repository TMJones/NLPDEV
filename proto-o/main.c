#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <poll.h>

#include "proto-o.h"
#include "Proc.h"

int main(){
	char in_str[1024]="init";
	char out_str[1024]="こんにちは！ボクおっくんだよ！\n";
	int  ret = 0;
	pid_t  pid = 0;
        int sock, cfd;
        struct sockaddr_un saddr, cliaddr;
        struct pollfd fds[1] = {0,};

        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if(sock < 0){
                fprintf(stderr, "socket error errno[%d]\n", errno);
                return(-1);
        }

        saddr.sun_family = AF_UNIX;
        strcpy(saddr.sun_path, MAIN_PATH);
        if(bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_un)) < 0){
                fprintf(stderr, "bind error errno[%d]\n", errno);
                return(-1);
        }

        if(listen(sock, 5) < 0){
                fprintf(stderr, "listen error errno[%d]\n", errno);
                return(-1);
        }

        fds[0].fd = sock;
        fds[0].events = POLLIN;

	pid = init_proc();

	system("clear");
	ret = IF_output(out_str);

        while(strcmp("bye", in_str) !=  0){
		ret = IF_input(in_str);
		send_message(in_str);

                poll(fds, 1, -1);
                if(fds[0].revents & POLLIN){
                        memset(&cliaddr, 0, sizeof(struct sockaddr_un));
                        socklen_t addrlen = sizeof(struct sockaddr_un);
                        if((cfd = accept(sock, (struct sockaddr *)&cliaddr, &addrlen)) < 0){
                                fprintf(stderr, "accept error errno[%d]\n", errno);
                                return (-1);
                        }
                        int len = read(cfd, out_str, sizeof(out_str));
                        out_str[len] = 0;
			ret = IF_output(out_str);
                }else{
                        fprintf(stderr, "error errno[%d]\n", errno);
                        return (-1);
                }
        }

        close(cfd);
        close(sock);

	remove(MAIN_PATH);

        return 0;
}

pid_t init_proc(){
	// プロセスを分岐させ、子プロセスでメインプロセス実行 
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		execlp("./Proc/Proc_res", NULL);
		exit(0);
	}

	sleep(1);
	return pid;
}

int send_message(char *buf){
	int sock;
	struct sockaddr_un dest;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
 	dest.sun_family = AF_UNIX;
	strcpy(dest.sun_path, PROC_PATH);

	if(connect(sock, (struct sockaddr *)&dest, sizeof(struct sockaddr_un)) < 0){
		fprintf(stderr, "connect error errno[%d]\n", errno);
		return -1;
	}

	if(write(sock, buf, strlen(buf)) < 0){
		fprintf(stderr, "write error errno[%d]\n", errno);
		return -1;
	}

	close(sock);
}
