#include <stdio.h>
#include <string.h>
#include <time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <sys/un.h>
#include <poll.h>
#include <errno.h>

#include "Proc.h"

int Proc_response(char *in_str, char *out_str){
        int t=time(NULL)%10;
        if ( strcmp("init", in_str) ==  0){
                strcpy(out_str, "こんにちは！ボクおっくんだよ！\n");
                return 0;
        }
        if ( strstr(in_str, "調子" ) != NULL ) {
                strcpy(out_str, "最高にHighってやつだ！\0\n");
                return 0;
        }
        if ( strstr(in_str, "天気" ) != NULL ) {
                strcpy(out_str, "うむ！　絶好の筋肉トレ日和だ！\n");
                return 0;
        }
        if ( strstr(in_str, "バカ" ) != NULL ) {
                strcpy(out_str, "バカって言うほうがバカなんだよ！　バーカ！\n");
                return 1;
        }
        if ( (strcmp("bye", in_str) ==  0) ||
             (strstr(in_str, "バイバイ" ) != NULL )) {
                strcpy(out_str, "バイバイ\n");
                return 1;
        }
        switch (t){
                case 0:
                        strcpy(out_str, "牛が食いたくば倒すのみ！\n");
                        break;
                case 1:
                        strcpy(out_str, "戦え！　何を！？　人生をだ！\n");
                        break;
                case 2:
                        strcpy(out_str, "うぬは己に負けたのだ…\n");
                        break;
                case 3:
                        strcpy(out_str, "俺より強いやつに会いに行く\n");
                        break;
                case 4:
                        strcpy(out_str, "まずはやってみよ！　考えるのはそれからだ\n");
                        break;
                case 5:
                        strcpy(out_str, "筋肉ってのは素晴らしい…そう思わないか？\n");
                        break;
                case 6:
                        strcpy(out_str, "明日は明日の風が吹く！\n");
                        break;
                case 7:
                        strcpy(out_str, "てめえの血は何色だ！？\n");
                        break;
                case 8:
                        sprintf(out_str, "「%s」？ あー…あれ美味しいよね\n", in_str);
                        break;
                case 9:
                        sprintf(out_str, "昔は良く遊んだな…「%s」\n", in_str);
                        break;
        }
        return 0;
}

int main(){
	int sock, cfd;
	struct sockaddr_un saddr, cliaddr;
	struct pollfd fds[1] = {0,};
	char buf[1024];
	char buf2[1024];

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock < 0){
		fprintf(stderr, "socket error[%d]\n", errno);
		return(-1);
	}

	saddr.sun_family = AF_UNIX;
	strcpy(saddr.sun_path, PROC_PATH);
	if(bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_un)) < 0){
		fprintf(stderr, "bind error[%d]\n", errno);
		return(-1);
    	}

	if(listen(sock, 5) < 0){
		fprintf(stderr, "listen error[%d]\n", errno);
		return(-1);
	}

	fds[0].fd = sock;
	fds[0].events = POLLIN;

	while(strcmp("bye", buf) !=  0){
		poll(fds, 1, -1);
		if(fds[0].revents & POLLIN){
			memset(&cliaddr, 0, sizeof(struct sockaddr_un));
			socklen_t addrlen = sizeof(struct sockaddr_un);
			if((cfd = accept(sock, (struct sockaddr *)&cliaddr, &addrlen)) < 0){
				fprintf(stderr, "accept error[%d]\n", errno);
				return (-1);
			}
			int len = read(cfd, buf, sizeof(buf));
			buf[len] = 0;
			Proc_response(buf, buf2);
			system(buf);
			send_message(buf2);
		}else{
			fprintf(stderr, "error[%d]\n", errno);
			return (-1);
		}
	}
	close(cfd);
	close(sock);
	remove(PROC_PATH);
	return 0;
}

int send_message( char *buf){
        int sock;
        struct sockaddr_un dest;

        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        dest.sun_family = AF_UNIX;
        strcpy(dest.sun_path, MAIN_PATH);

        if(connect(sock, (struct sockaddr *)&dest, sizeof(struct sockaddr_un)) < 0){
                fprintf(stderr, "connect error[%d]\n", errno);
                return -1;
        }

        if(write(sock, buf, strlen(buf)) < 0){
                fprintf(stderr, "write error[%d]\n", errno);
                return -1;
        }

        close(sock);

}
