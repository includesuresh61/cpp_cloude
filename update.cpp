#include"update.h"
int main(){

 /*update obj("user","pass","FTPserver","/vms/my_1.txt","my_2.txt");
 obj.init();
 obj.operation(2);*/
//    userName,password,FTPserver,srcPath,dstPath 
 update obj("user","pass","FTPserver","/vms/my_1.txt","my_2.txt");
 obj.init();
 obj.operation(1);


}
