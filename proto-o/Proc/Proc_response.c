#include <stdio.h>
#include <string.h>
#include <time.h>

int Proc_response(char *in_str, char *out_str){
        int t=time(NULL)%10;
        if ( strcmp("init", in_str) ==  0){
                strcpy(out_str, "こんにちは！ボクおっくんだよ！\n");
                return 0;
        }
        if ( strstr(in_str, "調子" ) != NULL ) {
                strcpy(out_str, "最高にHighってやつだ！\n");
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
