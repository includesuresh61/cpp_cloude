#include<iostream>
#include<string>
#include<cstdarg>
using namespace std;
string strPrintf(string &result,const char *format...){

   va_list args;
   va_start(args,format);
   while(*format != '\0'){
         string tmp;
         if(*format == '%'){
             format++;
             switch(*format){
               case 'd':
                {
                  int i = va_arg(args, int);
                  tmp=to_string(i);
                  result+=tmp;
                  goto Fmtspec;
                }
               case 'f':
                {
                  double f = va_arg(args,double);
                  tmp=to_string(f);
                  result+=tmp;
                  goto Fmtspec;
                }
               case 's':
                {
                  char *p = va_arg(args,char *);
                  while(*p){
                    tmp+=*p;
                    p++;
                  }
                  tmp+='\0';
                  result+=tmp;
                  goto Fmtspec;
                               
                } 
               case 'c':
                {
                  int c = va_arg(args,int);
                  tmp=static_cast<char>(c);
                  result+=tmp;
                  goto Fmtspec;
                }
               case 'u':
                {
                  unsigned int u = va_arg(args,unsigned int);
                  tmp=to_string(u);
                  result+=tmp;
                  goto Fmtspec;

                }
               case 'l':
                {
                   format++;
                   if(*format == 'l'){
                     format++;
                     if(*format == 'd'){
                       long long int lld = va_arg(args,long long int);
                       tmp=to_string(lld);
                       result+=tmp;
                       goto Fmtspec;
                     }else if(*format == 'u'){
                       unsigned long long int llu=va_arg(args, unsigned long long int);
                       tmp=to_string(llu);
                       result+=tmp;
                       goto Fmtspec;
                     }

                   }else if(*format == 'u'){
                      unsigned long int lu=va_arg(args, unsigned long int);
                      tmp=to_string(lu);
                      result+=tmp;
                      goto Fmtspec;
                   }
                }
               case 'L':
                {
                  format++;
                  if(*format == 'f'){
                      long double f = va_arg(args,long double);
                      tmp=to_string(f);
                      result+=tmp;
                      goto Fmtspec;
                   }
              
                }
               default:
               {
                 cout<<"Unkown format specifier!!!"<<endl;
               }
 
             }


         }
         result+=(*format);
         Fmtspec:
         format++;
  }
  va_end(args);
  return result;
}
int main(){

 
   string dst;
   string tmp="I_am";
   strPrintf(dst,"hello_%s_in_%lld_%f_%c",tmp.c_str(),52000000000000001,102.1234,'X');
   //strPrintf(dst,"empty_text");
   cout<<"o/p:"<<dst<<endl;


}
