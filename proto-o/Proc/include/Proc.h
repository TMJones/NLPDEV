#define MAIN_PATH "/tmp/main.sock"
#define PROC_PATH "/tmp/proc.sock"

typedef struct __proc_t{
//	int  type;			//プロセス間通信種別(TBD)
	char str[256];			//文字列
//	int  terminate;			//終了フラグ
} proc_t;
