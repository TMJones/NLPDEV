#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto-o.h"
#include "Proc.h"

int main(){
	char in_str[256]="init";
	char out_str[256]="init";
	int  ret = 0;
	system("clear");
//	while(strcmp("bye", in_str)){
	while(ret == 0){
		ret = Proc_response(in_str, out_str);
		if( ret == 1 ) break ;
		ret = IF_output(out_str);
		ret = IF_input(in_str);
//		ret = Learn_learning(in_str);
	}
	ret = Proc_response(in_str, out_str);
	ret = IF_output(out_str);
}

