#include<string.h>
#include<stdio.h>

int main(void)
{
   FILE *stream;
   char msg[] = "�������� ������";
   char buf[20];
   char s[1000];
   if((stream = fopen("input.txt","w+")) == NULL)
   {
      fprintf(stderr,"�� ���� ������� ����\n");
      return 1;
   }
   /* ������� � ���� ������ */
   fwrite(msg,strlen(msg)+1,1,stream);
   /* ������� �� ������ ����� */
   fseek(stream,SEEK_SET,0);
   /* ��������� ������ */
   fread(buf,strlen(msg)+1,1,stream);
   printf("%s\n",buf);
   fclose(stream);
   stream = fopen("input.txt","w+");
   fscanf(stream,&s);
   printf("%s",s);
   fclose(stream);
   return 0;
}