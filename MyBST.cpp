#include<iostream>
#include <bits/stdc++.h>
using namespace std;
template<class T>
class bstSTL{
 public:
    T data;
    static unsigned int size;
    bstSTL *right;
    bstSTL *left;
    bstSTL();
    bstSTL(bstSTL &)=delete;
    void operator=(const bstSTL &)=delete;
    ~bstSTL();
    static bstSTL *insert(bstSTL *root,T data);
    static bstSTL *clear(bstSTL *root,T data);
    static bool find(bstSTL *root,T data);
    static void show(bstSTL *root);
    //void search(T port);
};
template<class T>
bstSTL<T>::bstSTL(){
  data=(T ){0};
  right=nullptr;
  left=nullptr;
}
template<class T>
unsigned int bstSTL<T>::size=0;;
template<class T>
bstSTL<T>::~bstSTL(){
 if(right)
    delete right;
 if(left)
    delete left;
}
template<class T>
bstSTL<T> *bstSTL<T>::insert(bstSTL *root,T data){
 if(!root){
    bstSTL *tmp=new bstSTL();
    tmp->right=nullptr;
    tmp->left=nullptr;
    tmp->data=data;
    size++;
    return tmp; 
 }
 if(root->data == 0){
   root->data=data;
   size++;
   return root;
 }
 if(root->data > data)
 root->left=insert(root->left,data);
 else
 root->right=insert(root->right,data);
 return root;
}
template<class T>
bool bstSTL<T>::find(bstSTL *root,T data){
  if(root == nullptr) 
     return false;
  if(root->data == data)
     return true;
  find(root->left,data);
  find(root->right,data);
}
template<class T>
bstSTL<T> *bstSTL<T>::clear(bstSTL *root,T data){
  if(root == nullptr)
      return root;
   if(root->data > data)
       root->left = clear(root->left,data);
   else if(data > root->data)
       root->right = clear(root->right,data);
   else {
       if(root->left== nullptr && root->right== nullptr){
           if(size !=0)size--;
           return nullptr;
       }
       else if (root->left == nullptr) {
            bstSTL* temp = root->right;
            free(root);
            if(size !=0)size--;
            return temp;
       }
       else if (root->right == nullptr) {
            bstSTL* temp = root->left;
            free(root);
            if(size !=0)size--;
            return temp;
      }
      bstSTL *current =root->right;
      while (current && current->left != nullptr)
              current = current->left;
      bstSTL *temp =current;
      root->data = data;
      root->right =clear(root->right, temp->data);
   }
   return root;
}

template<class T>
void bstSTL<T>::show(bstSTL *root){
 if(root == nullptr) return;
    printf("%d ",root->data);
    show(root->left);
    show(root->right);
}

int main()
{
bstSTL <int> *obj=new bstSTL<int>();
cout<<"----------------------INSERT-START------------------"<<endl;
for( int i=0;i<29000;i++)
bstSTL <int> ::insert(obj,i);
cout<<"----------------------INSERT-END------------------"<<endl;
bstSTL <int> ::show(obj);
cout<<"size ="<<bstSTL <int> ::size<<endl;
if(bstSTL <int> ::find(obj,25666)){
cout<<"found---25666"<<endl;
 bstSTL <int> ::clear(obj,25666);
}
else
cout<<"Not found---25666"<<endl;
if(bstSTL <int> ::find(obj,25666)){
cout<<"found---25666"<<endl;
 bstSTL <int> ::clear(obj,25666);
}
else
cout<<"Not found---25666"<<endl;
cout<<"size ="<<bstSTL <int> ::size<<endl;

}
