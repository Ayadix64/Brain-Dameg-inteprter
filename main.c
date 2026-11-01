#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned long GetFileSize(FILE* fl){
	if(fl==NULL){
		printf("err in file\n");
		return -1;
	}
	long prev=ftell(fl);
	if(fseek(fl, 0L, SEEK_END)==-1){
		printf("files to fseek");
		return -1;
	}
	unsigned long fileSize = ftell(fl);
	fseek(fl, prev, SEEK_SET);
	return fileSize;

}

int main(int argc , char** arg)
{
	assert(argc>1);
	FILE* f = fopen(arg[1], "r");
	if(!f){
		printf("can not open file %s .\n",arg[1]);
		return -1;
	}
	unsigned int prog_len = GetFileSize(f);
	char* prog = (char*)malloc(prog_len);
	fread((void*)prog, prog_len, 1, f);

	unsigned char buff[0xffff];
	memset(buff, 0, 0xffff);
	int ptr = 0; 
	int ip = 0;
	for( ;ip < prog_len;){
		switch (prog[ip]) {
			case '>':
				ptr++;
				ip++;
				break;
			case '<':
				ptr--;
				ip++;
				break;
			case '+':
				buff[ptr]++;
				ip++;
				break;
			case '-':
				buff[ptr]--;
				ip++;
				break;
			case '.':
				putchar(buff[ptr]);
				fflush(stdout);
				ip++;
				break;
			case ',':
				buff[ptr] = getchar();
				ip++;
				break;
			case '[':
				if(!buff[ptr])
				{
					int bracts = 0;
					for( ; ip  < prog_len ; ip++)
					{
						if(prog[ip] == '[')bracts++;
						if(prog[ip] == ']')bracts--;
						
						if(!bracts && prog[ip] == ']')
						{
							break;
						}
						
					}
				}
				ip++;
				break;
			case ']':
				if(buff[ptr])
				{
					int bracts = 0;
					for( ; ip  >= 0 ; ip--)
					{
						if(prog[ip] == '[')bracts--;
						if(prog[ip] == ']')bracts++;
						
						if(!bracts && prog[ip] == '[')
						{
							break;
						}
						
					}
				}
				ip++;
				break;
			default:
				ip++;
				break;
		}
	}
}
