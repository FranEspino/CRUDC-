#include <windows.h>
#include <string.h>
#include <mysql.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <conio.h>

using namespace std;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;

void menuPrincipal(){
        cout<<"\t\t\t*********************************"<<endl;
        cout<<"\t\t\t\t   .: CRUD MENU :."<<endl<<endl;
        cout<<"\t\t\t1. CREATE NEW PRODUCT."<<endl;
        cout<<"\t\t\t2. READ ALL PRODUCTS."<<endl;
        cout<<"\t\t\t3. UPDATE A PRODUCT. "<<endl;
        cout<<"\t\t\t4. DELETE A PRODUCT. "<<endl;
        cout<<"\t\t\t5. EXIT. "<<endl<<endl;
        cout<<"\t\t\t*********************************"<<endl;
}

void createProduct(MYSQL *conn,char *productName, int productPrice, char *productDate){
    char consulta1[1024];
    sprintf(consulta1,"INSERT INTO producto VALUES('','%s','%i','%s')",productName,productPrice,productDate);
    if(mysql_query(conn,consulta1)==0){
        cout<<"\nProduct insert success"<<endl;
    }
}

void readProducts(MYSQL *conn,char * consulta,MYSQL_ROW row,MYSQL_RES *res){
    if(mysql_query(conn,consulta)==0){
        res = mysql_use_result(conn);
        cout<<"\t\t\tSHOW PRODUCTS\n";
        while((row=mysql_fetch_row(res))){
            printf("\n\t\t-----------------------------------");
            printf("\n\t\tId: %s\n",row[0]);
            printf("\t\tProduct Name: %s\n",row[1]);
            printf("\t\tProduct Price: %s\n",row[2]);
            printf("\t\tProduct Date: %s\n",row[3]);
        }
        cout<<"\n\n";
    }
}

void updateProduct(MYSQL *conn,char *updateName,int idProduct){
    char consulta2[1024];
    sprintf(consulta2,"UPDATE producto SET nombre_producto='%s' WHERE id_producto='%i'",updateName,idProduct);
    if(mysql_query(conn,consulta2)==0){
        cout<<"\nProduct update with success"<<endl;
    }
}

void deleteProduct(MYSQL *conn,int idProduct){
    char consulta3[1024];
    sprintf(consulta3,"DELETE FROM producto WHERE id_producto='%i'",idProduct);
     if(mysql_query(conn,consulta3)==0){
        cout<<"\nProduct delete with success"<<endl;
    }
}

int main()
{
   char fecha[10],hora[10],fechayhora[25];
   //sacamos la fecha
   time_t t;
   struct tm *tm;
   t=time(NULL);
   tm=localtime(&t);
   strftime(fecha, 100, "%d/%m/%y", tm);
   //sacamos la hora
   time_t current_time;
   struct tm * time_info;
   time(&current_time);
   time_info = localtime(&current_time);
   strftime(hora, sizeof(hora), "%H:%M:%S", time_info);
   //concatenamos la hora y la fecha
   strcpy(fechayhora,fecha);
   strcat(fechayhora," ");
   strcat(fechayhora,hora);

    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","tienda",0,NULL,0);
     if(conn){
        system("color a");
        cout<<"Database connected with success.\n";
    }else{
        system("color c");
        cout<<"Failed to connect database.\n";
    }
    int op;
    do{
       system("cls");
       menuPrincipal();
       cout<<"\nINGRESE UNA OPCION: ";
       cin>>op;
       switch(op){
            case 1:
                system("cls");
                char productName[1024];
                int productPrice;
                fflush(stdin);
                cout<<"\nProduct Name: ";
                cin.getline(productName,1024,'\n');
                cout<<"\n";
                fflush(stdin);
                cout<<"\nProduct Price: ";
                cin>>productPrice;
                cout<<"\n";
                createProduct(conn,productName,productPrice,fechayhora);
                system("pause");

            break;

            case 2:
                system("cls");
                char consulta[1024];
                sprintf(consulta,"SELECT *FROM producto");
                readProducts(conn,consulta,row,res);
                system("pause");
            break;

            case 3:
                system("cls");
                char updateName[1024];
                int idProduct;
                fflush(stdin);
                cout<<"\nId of the product to update: ";
                cin>>idProduct;
                cout<<"\n";
                fflush(stdin);
                cout<<"\nName of the product to update ";
                cin.getline(updateName,1024,'\n');
                cout<<"\n";
                updateProduct(conn,updateName,idProduct);
                system("pause");
            break;

            case 4:
                system("cls");
                int idProduct_drop;
                fflush(stdin);
                cout<<"\nId of the product to delete: ";
                cin>>idProduct_drop;
                deleteProduct(conn,idProduct_drop);
                system("pause");
            break;
       }

    }while(op!=5);

    return 0;
}
