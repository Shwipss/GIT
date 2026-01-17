#include<stdio.h>
#define file "FileName.txt" // ism ta3 file lifih ma3lomat 
#include<stdlib.h>
#include<windows.h>//ns7a9oha fal interface 
typedef struct Car{
int  matricule; 
char Marc[30];
float distance ; //masafa lma9to3a ta3 kol Car

}Car;
typedef struct BST{//baynary serch tree
Car node;// and matricule is id for this tre (node.matricle)
struct BST*left;// ibn aysar 
struct BST*right;//ibn ayman 
}BST;

void BstStructInReadFile(BST**root,Car car){
BST*tmp=*root;//n7tajoh bahnamchiw falchajra 
BST*newNode;
newNode=malloc(sizeof(BST));
newNode->node=car;
newNode->left=NULL;// lzam n7tohom NUll l5atar hadom awra9
newNode->right=NULL;
if(*root==NULL){
    
    *root=newNode;//lhna ida kan root null  fma3natha hdi awal 3o9da
}else{

    while(1){// kayan ch7al mantari9a ma7bitch n3a9daha mam ida 3acht hdi mahich best fihom bsa7 ahal
//ma7abitch ndir recercivet la5atar  ma3andha 7ta fayda hna w9adr ysra overflow stach fal big dat 
        if(car.matricule<tmp->node.matricule){//y9arn  matricul lyal3ab dawr ta3 id  mba3da ya5dam 3adi kchgle tmp raho ytza7la9 fachjra  
    if(tmp->left==NULL) {tmp->left=newNode;break;} else{ tmp=tmp->left;}

}else{
    if(tmp->right==NULL) {tmp->right=newNode;break;}else {tmp=tmp->right;}
}} 
}

}
void readData(BST**root){
FILE*f;
f=fopen(file,"r");
if(!f){//ida kanat NUll bal bar twli 1 sma yd5l inverse logical
printf("erure file does not existe or it's impty ");
exit(0);
}
Car car;
while (fscanf(f,"%d %s %f",&car.matricule,car.Marc,&car.distance)==3)
{
   //dork nkono 3amarna  node lowla nba3toha lchjra

    BstStructInReadFile(root,car);}
   fclose(f); 
}


void addCar(BST **root){
    Car car;

    printf("da5l matricule ");
    scanf("%d",&car.matricule);

    printf("da5l lmarc ");
    scanf("%s",car.Marc);

    printf("da5l distance ");
    scanf("%f",&car.distance);

    // nst3mlo nfs dala li nd5lo biha viotur ll bst
    BstStructInReadFile(root,car);


}
 
void searchCar(BST* root) {
    int matricule;
    printf("aktb matricule lithws elih : ");
    scanf("%d",&matricule);//madam lkey howa matricule sma nhawso ela matricule brk
    while (root != NULL) {
        if (root->node.matricule == matricule) {//hna kinlgaw nafs lmatricule
            printf("lcar ta3k :\nmatricule :%d\nmarc :%s\ndistance :%f",root->node.matricule,
       root->node.Marc,
       root->node.distance);
            exit(0);
        } 
        else if (matricule < root->node.matricule) {
            root = root->left;//ida kan 9al nroho lchilde sghir 
        } 
        else {
            root = root->right;//ida kan ktar nroho lchilde lkbir
        }
    }

    printf("makansh wli ghodwa\n"); //malginash :(
}

void DisplayCars(BST* root,int mode ,FILE* f)   // bon rayh nkhdm b type ta3 order "Preorder" bch ndiro prinl ll cars kima rahom fl tree tkon hak --> (root -> left -> right)
{
    // khdmna bl mode bch ndkhloha f switch w nkhliw meme function tkhdm 2 khdmat nt3lmo mn3wdoch nfs khdma fi kol mara 
    if (root == NULL) return ;
    
    if (mode == 3)  // print terminal
    {
    
         printf("Matricule : %d | Brand : %s | KM : %f \n", root->node.matricule , 
                                                             root->node.Marc , 
                                                             root->node.distance );
    }
    
    if (mode == 0)  // print file  
    {
    
        fprintf(f,"%d %s %f \n", root->node.matricule ,
                                 root->node.Marc ,
                                  root->node.distance );
        
    }
    

     DisplayCars(root->left,mode,f);  // fi kol mra nroho ll jiha ntb9o eliha meme fonction  ( mtnsawch f bch n3gbo pointer ela ll file )
          DisplayCars(root->right,mode,f);
   
}
BST*changRoot(int key,BST*root,BST*tmp){
//dala lira7jiblna nwe node ta3na l5atr ktfasi rak dir tbadol mfati7 bin nodes taw3ak lazam t5ayar the best postion whadi hya 5admat adala
if(key<root->node.matricule&&root->left!=NULL){
    return changRoot(key,root->left,root);
}//tmp hwa sa7 ymadalna 3o9da li9bal ln7awso 3liha
if(key>root->node.matricule&&root->right!=NULL){
    return changRoot(key,root->right,root);
}
return tmp;
}
BST* Delet(int key,BST*root){
if(root!=NULL){//ybda ya7awas 7tan yal9a l3oda 
if(key<root->node.matricule){
if(Delet(key,root->left)==NULL) root->left=NULL;

}if(key>root->node.matricule){
if( Delet(key, root->right)==NULL)root->right=NULL;
}
if(key==root->node.matricule){
    if(root->left==NULL&&root->right==NULL){//lokan jat l3o9da wara9a 
        free(root);
        return NULL;
    }else{
        BST*tmp;
   if(root->left!=NULL){//lahna l7ala ta3 lokan jat l3o9a mhich war9a sma 3ndan zoj 7alat lzoj y5admo bdala ta3 changRoot
    BST*newRoot=changRoot(key,root->left,root);
if(newRoot==root){
    root->node=newRoot->left->node;
    free(newRoot->left);
    root->left=NULL;}else{
 root->node=newRoot->right->node;
 tmp=newRoot->right->left; 
 free(newRoot->right);
 newRoot->right=tmp;
   }
   }else{
    BST*newRoot=changRoot(key,root->right,root);
    if(newRoot==root){
        root->node=newRoot->right->node;
        free(newRoot->right);
        root->right=NULL;}else{
            root->node=newRoot->left->node;
            tmp=newRoot->left->right;
            free(newRoot->left);
            newRoot->left=tmp;
        }
//rakaz mli7 l5atar mhich kima dala alm3rofa hadi 5damtha w7di 
   }   
        

    }
}
}else{printf("the informatoin is not exit");}  //lahna lokan mayl9ach lma3loma lokan tla7ad dala ta3i fiha 3yb kbir wli how return ta3h mahoch mli7 wymadlak 9yam 3achwaiya 3la hdi ma9dartch nchco l7ala ta3ha ta7t
}

void updateDistance(BST* root){//hna ra7 n9adro nbadlo distance ta3 tonobil kima t7ab
    int matricule;
    float newDistance;

    printf("enter matricule : ");
    scanf("%d",&matricule);

   while (root != NULL) {
        if (root->node.matricule == matricule) {//hna kinlgaw nafs lmatricule
            printf("enter new distance : ");
            scanf("%f",&newDistance);
            root->node.distance=newDistance;
            printf("distance updated successfully\n");
            return;
        } 
        else if (matricule < root->node.matricule) {
            root = root->left;//ida kan 9al nroho lchilde sghir 
        } 
        else {
            root = root->right;//ida kan ktar nroho lchilde lkbir
        }
    }

    printf("car not found\n");
}

void main (){
    int choice=1; //bah nkhayro wesh ndiro
    BST *root=NULL;//head wla root ta3 chajra ns7a9oh fay 3amalya 
    int key;
readData(&root);//5damt bdouble pointer bah ji sahla ta9dar ta5dam bah t7ab
while(choice!=0){
printf("1-larak hab dir add type \n2-larak hab dir search type \n3-display \n4-delet \n5-update distance \n Exit 0 ");
printf("ur choice : ");
scanf("%d", &choice);
system("cls");//tfasi wch kyan fal tarminam
switch (choice)//bash nkhayro wesh habin ndiro
{
    
case 1:
    addCar(&root); //lahna tbda l5adma ta3 add ra7 ta5dam fanction ta3ak wt3aytlha hna t7ab ta5dam fanction swa kima ta3i bal loop wla bl recercevete 
    break;
case 2:
    searchCar(root);//hna ysra search
    break;
case 3 :
    DisplayCars(root,3,NULL);  
    break;

case 4:

printf("enter the key for car");
scanf("%d",&key);
Delet(key,root);//dala ta3 delet syit nbastha 9ad mana9dar mam mhich top ldic daraja

break;

case 5 :
    updateDistance(root);//hada bah tbdel distance ta3 tonobil bistkhdam matricule mta3ou
    break;
case 0 :
{
    FILE*f;
    f=fopen("FileName.txt","w");  // hda choice y3wd yktb file ta3na b order ta3 tree
    if (f == NULL)
    {
        printf("error opening file");
        break;
    }

    DisplayCars(root,0,f);
}                            
default:
system("cls");
    break;
}

}}