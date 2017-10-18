#include<string.h>
#include<stdio.h>

int main(void)
{
   FILE *stream;
   char msg[] = "Тестовый пример";
   char buf[20];
   char s[1000];
   if((stream = fopen("input.txt","w+")) == NULL)
   {
      fprintf(stderr,"Не могу открыть файл\n");
      return 1;
   }
   /* вывести в файл данные */
   fwrite(msg,strlen(msg)+1,1,stream);
   /* перейти на начало файла */
   fseek(stream,SEEK_SET,0);
   /* прочитать данные */
   fread(buf,strlen(msg)+1,1,stream);
   printf("%s\n",buf);
   fclose(stream);
   stream = fopen("input.txt","w+");
   fscanf(stream,&s);
   printf("%s",s);
   fclose(stream);
   return 0;
}