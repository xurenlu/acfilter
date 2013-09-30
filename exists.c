/*
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "mem_collector.h"
#include "acseg_tree.h"


int main(int argc, char **argv)
{
    char * dict_path;//  = "/home/renlu/dict.txt";
    if(argc<2){
        printf("usage:%s dict.file",argv[0]);exit(2);
    }
    dict_path = malloc(sizeof(char)*1024);
    if(!dict_path) {exit(1);}
    strcpy(dict_path,argv[1]);
	//char dict_path[]  = "dict3.txt";
	char text_path[]  = "mogu.txt";
	//char text_path[]  = "info.txt";

	char new_word[] =  "new_word";

	int hash_size = 50;
	unsigned char buf[8192];

	int text_fd;
	ssize_t read_size;
	int j;

	acseg_index_t *acseg_index;
	acseg_index = acseg_index_init();

	//print_time("load dict start");
	if ( !acseg_index_load(acseg_index, dict_path) ) {
		printf("load dict failed\n");
		return 0;
	}
	//print_time("load dict end");
	acseg_index_fix(acseg_index);
	//print_time("fix index end \n");
	
	acseg_result_t * seg_result;

	acseg_str_t text;

	text_fd = open(text_path, O_RDONLY);
	read_size = read(text_fd, buf, sizeof(buf));
	//printf("%s", buf);

	text.len  = read_size;
	text.data = buf;

	//print_time("start seg\n");
	seg_result = acseg_full_seg(acseg_index, &text,2);
	//print_time("end seg\n");

	acseg_str_t *phrase;
	acseg_list_item_t *result_item;
	result_item = seg_result->list->first;
	while (result_item) {
		phrase = (acseg_str_t *) result_item->data;	
		printf("%s ", phrase->data); 
		result_item = result_item->next;
	}

	// free res
	close(text_fd);
	acseg_destory_result(&seg_result);
	acseg_destory_index(&acseg_index);


}
