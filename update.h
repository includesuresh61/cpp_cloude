#include<iostream>
#include<string>
#include<curl/curl.h>
using namespace std;
class update{
   private:
    CURL *curl;
    string dstUrl;
    string userName;
    string passWord;
    string serverName;
    string srcpath;
    string dstpath;
   public:
    FILE *streamer;
    char errBuf[1024];
    update();
   // update(update&)=delete;
    update(string user,string passwd,string server,string srcPath,string dstPath);
    ~update();
    void init();
    void user_auth();
    string generate_url(string path); 
    CURL * get();
    void operation(unsigned int opt);
    static size_t write_callback(char *buffer, size_t size, size_t nmemb,void *stream);
    static size_t read_callback(char *buffer, size_t size, size_t nmemb,void *stream);

};
update::update(string user,string passwd,string server,string srcPath,string dstPath){
 userName=user;
 passWord=passwd;
 serverName=server;
 srcpath=srcPath;
 dstpath=dstPath;
 streamer=nullptr;
 cout<<"update()"<<endl;
}
update::~update(){
  cout<<"~update()"<<endl;
  if(streamer)
    fclose(streamer);
 curl_global_cleanup();
}
CURL *update::get(){
  return curl;
}
void update::init(){
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl=curl_easy_init();
}
string update::generate_url(string path){
   
   dstUrl="ftp://";
   dstUrl+=userName;
   dstUrl+="@";
   dstUrl+=serverName;
   dstUrl+=path;
   cout<<" URL:"<<dstUrl<<endl;   
   return dstUrl; 
}
void update::user_auth(){
 if(dstUrl.empty()){
    cout<<"user_auth failed"<<endl;
    return;
 }
 curl_easy_setopt(curl,CURLOPT_URL,dstUrl.c_str());
 curl_easy_setopt(curl,CURLOPT_USERNAME,userName.c_str());
 curl_easy_setopt(curl,CURLOPT_PASSWORD,passWord.c_str());

}
void update::operation(unsigned int opt){
   curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,errBuf);
switch(opt){
  case 1:
  {
    cout<<"POST operation!!!"<<endl;
     generate_url(srcpath);
     user_auth();
     streamer=fopen(dstpath.c_str(),"rb");
     curl_easy_setopt(curl,CURLOPT_READFUNCTION,read_callback);
     curl_easy_setopt(curl,CURLOPT_READDATA,this);
     curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);

    break;
  }
  case 2:
  {
    cout<<"GET operation !!!"<<endl;
    generate_url(srcpath);
    user_auth();
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,this);
    break;
  }
  defalut:
  {
    cout<<"UNKOWN operation"<<endl;
  }
 }
// curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 CURLcode  res = curl_easy_perform(curl);
 if(CURLE_OK != res) {
   fprintf(stderr, "curl told us %d ---->%s\n", res,errBuf);
 }
}
size_t update::read_callback(char *buffer,size_t size,size_t nmemb,void *stream){
  cout<<"read_callback !!!"<<endl;
  update *ptr=(update *)stream;
  return fread(buffer, size, nmemb, (FILE *)ptr->streamer);
}
size_t update::write_callback(char *buffer,size_t size,size_t nmemb,void *stream){
  cout<<"wirte_callback !!!"<<endl;
  update *ptr=(update *)stream;
  ptr->streamer=fopen(ptr->dstpath.c_str(),"wb");
  return fwrite(buffer,size,nmemb, (FILE *)ptr->streamer);
}



