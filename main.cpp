#include <iostream>
#include<string>
#include<ctime>
#include"Product.h"
#include"Stock.h"
#include"Order.h"
#include"Customers.h"
#include"Transaction.h"
#include"Credit.h"
using namespace std;

Stock stck;
Product prdct;
Customers cstmsr;
Order ffff;
Transaction trnsction;
unsigned int m_PrdctList_indx=0;
unsigned int m_PrdctListID=1;
unsigned int m_OrderList_indx=0;
unsigned int m_OrderListCounter=1;
unsigned int m_TransactionList_indx=0;
unsigned int m_TransactionCounter=1;

Product*productList= new Product[50];
Order*orderList= new Order[50];
Transaction*TransactionList= new Transaction[50];

void readFromTheFileProduct();
void writeOnTheFileProduct();
void readFromTheFileOrder();
void writeOnTheFileOrder();
void readFromTheFileTransaction();
void writeOnTheFileTransaction();
void mainMenu();
void dataEntrymenu();
void salesProcess();
void print();
void productMenu();
void stockMenu();
void customerMenu();

int main()
{
    mainMenu();
    return 0;
}
void mainMenu()
{
    readFromTheFileProduct();
    readFromTheFileOrder();
    readFromTheFileTransaction();
    int c=-1;
    while (c!=0)
    {
        cout<<"-------------------------------------------------------\n"
            <<"1.Data Entry\n"
            <<"2.Sales process\n"
            <<"3.Print\n"
            <<"0.Quit\n"
            <<"Enter Your Choice: ";
        cin>> c;
        cin.ignore();
        cout<<"-------------------------------------------------------\n";
        switch (c)
        {
        case 1:
            dataEntrymenu();
            break;
        case 2:
            salesProcess();
            break;
        case 3:
            print();
            break;
        }
    }
    writeOnTheFileProduct();
    writeOnTheFileOrder();
    writeOnTheFileTransaction();
    delete [] productList;
    delete [] orderList;
    delete [] TransactionList;
}

void dataEntrymenu()
{
    int b;
    cout <<"1.Add  ||  Update  product list \n"
         <<"2.Add  ||  Edit  ||  Search  ||  Delete  ||  Update product in stock\n"
         <<"3.Add  ||  Edit  ||  Search  ||  Delete customer\n"
         <<"Enter Your Choice: ";
    cin>> b;
    cin.ignore();
    cout<<"-------------------------------------------------------\n";
    switch(b)
    {
    case 1:
        productMenu();
        break;
    case 2:
        stockMenu();
        break;
    case 3:
        customerMenu();
        break;
    }
}

void salesProcess()
{
    bool orderExist = false;
    bool cstExist = false;
    bool cstExist22 = false;
    bool orderPay = false;
    int choi;
    cout <<  " 1.Add Order \n"
         <<" 2.Update Order \n"
         <<" 3.Add Transaction \n"
         <<" 4.Pay order \n"
         <<" Enter Your Choice : ";
    cin >> choi;
    cin.ignore();
    switch(choi)
    {
    case 1:
        int cstmrID;
        cout << " Enter customer ID : ";
        cin >> cstmrID;
        cin.ignore();
        for(int i = 0 ; i < cstmsr.getCustmrArrSize(); i++ )
        {
            if(cstmrID==cstmsr.returnCustomerArr()[i]->getCustomerID())
            {
                orderList[m_OrderList_indx].setCustomerToOrder(cstmsr.returnCustomerArr()[i]);
                cstExist = true;
                break;
            }
        }
        {
            if(cstExist)
            {
                orderList[m_OrderList_indx].setOrderID(m_OrderListCounter);
                int randomNumber=0;
                srand(time(0));
                randomNumber=rand();
                cout<< " The order number : " << randomNumber<<endl;
                orderList[m_OrderList_indx].setOrderNumber(randomNumber);
                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];
                time (&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
                string str(buffer);
                cout << " Order time : " << str <<endl;
                orderList[m_OrderList_indx].setOrderDate(str);
                orderList[m_OrderList_indx].setOrderStatus(1);
                orderList[m_OrderList_indx].createListOfOrdItems(&stck);
                m_OrderList_indx++;
                m_OrderListCounter++;
                break;
            }
            else cout << " this customer was not found \n";
        }
        break;
    case 2:
        int ordrIDD;
        int ordrStts;
        cout << " Enter Order ID : ";
        cin>> ordrIDD;
        cin.ignore();
        for(unsigned int i = 0 ; i < m_OrderList_indx; i++)
        {
            if(ordrIDD == orderList[i].getOrderID())
            {
                orderExist = true;
                cout << " Update Order Status \n"
                     << " 1. New order \n"
                     << " 2. Hold order \n"
                     << " 3. Paid order \n"
                     << " 4. Canceled order \n"
                     << " Enter you choice : ";
                while(true)
                {
                    cin >> ordrStts;
                    if (ordrStts >= 1 && ordrStts <= 4)
                        break;
                    else
                        cout << "\aPlease Enter a valid Choice : " ;
                }
                switch(ordrStts)
                {
                case 1:
                    orderList[i].setOrderStatus(1);
                    break;
                case 2:
                    orderList[i].setOrderStatus(2);
                    break;
                case 3:
                    orderList[i].setOrderStatus(3);
                    break;
                case 4:
                    orderList[i].setOrderStatus(4);
                    break;
                default:
                    ;
                }
                break;
            }
        }
        if(!orderExist)
        {
            cout<<"-------------------------------------------------------\n";
            cout << " this Order ID was not found \n";
        }
        break;
    case 3:
        int cstmrrID;
        cout << " Enter customer ID : ";
        cin >> cstmrrID;
        for(int i = 0 ; i < cstmsr.getCustmrArrSize(); i++ )
        {
            if(cstmrrID==cstmsr.returnCustomerArr()[i]->getCustomerID())
            {
                TransactionList[m_TransactionList_indx].setCustomerTTransaction(cstmsr.returnCustomerArr(), cstmsr.getCustmrArrSize(), cstmrrID);
                TransactionList[m_TransactionList_indx].SetOrdrToTransaction(&orderList);
                TransactionList[m_TransactionList_indx].setOrdersCount(&m_OrderList_indx);
                TransactionList[m_TransactionList_indx].setTrnsactionID(m_TransactionCounter);
                time_t rawtimee;
                struct tm * timeinfoo;
                char buffer[80];
                time (&rawtimee);
                timeinfoo = localtime(&rawtimee);
                strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfoo);
                string str(buffer);
                cout << " Transaction time : " << str <<endl;
                TransactionList[m_TransactionList_indx].setTransactionDate(str);
                m_TransactionList_indx++;
                m_TransactionCounter++;
                cstExist22 = true;
                break;
            }
        }
        if(!cstExist22)
        {
            cout << " ------------------------------------------------\n";
            cout << " This customer was not found \n";
        }
        break;
    case 4:
        bool orderPay = false;
        int ordrIDDD;
        int pymntmthd;
        cout << " Enter Order ID : ";
        cin >> ordrIDDD;
        cin.ignore();
        for (unsigned int i = 0 ; i < m_OrderList_indx; i++ )
        {
            if(ordrIDDD==orderList[i].getOrderID())
            {
                if (orderList[i].getOrderStatus()== 3 )
                {
                    cout << " ------------------------------------------------\n";
                    cout << " This order was already paid \n";
                }
                else if (orderList[i].getOrderStatus()== 4)
                {
                    cout << " ------------------------------------------------\n";
                    cout << " This order was already canceled \n";
                }
                else if (orderList[i].getOrderStatus()== 2 || orderList[i].getOrderStatus()==1)
                {
                    orderList[i].checkOrder();
                    cout << "\n------------------------------------------------\n";
                    cout << " ------------------------------------------------\n";
                    cout << " The payment Amount is : " << orderList[i].CalcTotalPrice();
                    cout << "\n------------------------------------------------\n";
                    cout << "------------------------------------------------\n";
                    cout << " 1. Credit \n "
                         << " 2. Cash \n "
                         << " 3. Check \n "
                         << " Enter the payment method : ";
                    while(true)
                    {
                        cin >> pymntmthd;
                        if (pymntmthd >= 1 && pymntmthd <= 3)
                            break;
                        else
                            cout << "\aPlease Enter a valid Choice : " ;
                    }
                    Payment*m_PayOrder;
                    switch(pymntmthd)
                    {
                    case 1:
                        m_PayOrder = new Credit;
                        m_PayOrder->fillData();
                        break;
                    case 2:
                        m_PayOrder = new Cash;
                        m_PayOrder->fillData();
                        break;
                    case 3:
                        m_PayOrder = new Check;
                        m_PayOrder->fillData();
                        break;
                    default:
                        cout << "\a Process was Terminated due to invalid Choice \n";
                        break;
                    }
                    {
                        if( m_PayOrder->getPaymentAmount() >= orderList[i].CalcTotalPrice())
                        {
                            orderList[i].setOrderStatus(3);
                        }
                        else if( m_PayOrder->getPaymentAmount() < orderList[i].CalcTotalPrice())
                        {
                            orderList[i].setOrderStatus(2);
                            cout << " This money is not sufficient and this order will be hold\n " ;
                        }
                    }
                }
                orderPay = true;
                break;
            }
        }
        if(!orderPay)
        {
            cout << " ------------------------------------------------\n";
            cout << " This order was not found \n";
        }
        break;
    }
}

void print()
{
    int chh;
    cout <<  " 1.Print customer List \n"
         <<" 2.Print product data \n"
         <<" 3.Print Stock data \n"
         <<" 4.Print Transaction \n"
         <<" 5.Print Order list \n"
         <<"Enter Your Choice: ";
    cin >> chh;
    cin.ignore();
    switch(chh)
    {
    case 1:
        cstmsr.printCustomers();
        break;
    case 2:
        for (unsigned int i = 0 ; i < m_PrdctList_indx ; i++)
        {
            cout << productList[i];
            cout<< "\n";
        }
        break;
    case 3:
        stck.showPrdctStckList();
        break;
    case 4:
        for (unsigned int i = 0 ; i < m_TransactionList_indx ; i++)
        {
            TransactionList[i].printTransaction();
            cout<< "\n";
        }
        break;
    case 5:
        for (unsigned int i = 0 ; i < m_OrderList_indx ; i++)
        {
            orderList[i].printAllOrders();
            cout<< "\n";
        }
        break;
    }
}

void productMenu()
{

    cout << "1. Add a product\n" << "2. Update product price\n";
    bool prdctFound = false;
    cout << " Enter your choice : ";
    int M;
    cin >> M;
    cin.ignore();
    switch(M)
    {
    case 1:     // add product to product list
        cin >> productList[m_PrdctList_indx];
        productList[m_PrdctList_indx].setProductID(m_PrdctListID);
        m_PrdctList_indx++;
        m_PrdctListID++;
        break;
    case 2:
        int m_prdctIDD;
        double prdctPrice;
        cout << " Enter product ID you want to update : ";
        cin >> m_prdctIDD;
        cin.ignore();
        {
            for(unsigned int i=0; i<m_PrdctList_indx; i++)
            {
                if(productList[i].getProductID()==m_prdctIDD)
                {
                    cout << " Enter the new price : ";
                    cin>>prdctPrice;
                    cin.ignore();
                    productList[i].setProductPrice(prdctPrice);
                    prdctFound = true;
                    break;
                }
            }
            if(!prdctFound)
            {
                cout<<"-------------------------------------------------------\n";
                cout << " This product was not found \n";
            }
        }
        break;
    }
}

void stockMenu()
{
    int D;
    int Prdct1,Prdct2,Prdct3,Prdct4;
    cout << "1. Add a stock\n" << "2. Edit a stock\n"<< "3. Search for a stock\n" << "4. Delete a stock\n" << "5. Update a product in the stock\n" << "Enter you choice : ";
    cin >> D;
    cin.ignore();
    switch(D)
    {
    case 1:
        stck.createProdctStockList(productList,m_PrdctList_indx);
        break;
    case 2:
        cout << "Enter the product ID : ";
        cin >> Prdct1;
        cin.ignore();
        stck.editProductInfo(productList,m_PrdctList_indx,Prdct1);
        break;
    case 3:
        cout << " Enter the product ID : ";
        cin >> Prdct2;
        cin.ignore();
        stck.searchForProduct(Prdct2);
        break;
    case 4:
        cout << " Enter the product ID : ";
        cin >> Prdct3;
        cin.ignore();
        stck.deleteProductfromStock(Prdct3);
        break;
    case 5:
        cout << " Enter the product ID : ";
        cin >> Prdct4;
        cin.ignore();
        stck.UpdateStock(Prdct4);
        break;
    }
}

void customerMenu()
{
    int n;
    int Prdct1,Prdct2,Prdct3;
    cout << "1. Add customer \n" << "2. Edit customer info\n"<< "3. Search for a customer\n" << "4. Delete a customer \n"  <<"Enter you choice : ";
    cin >> n;
    cin.ignore();
    switch(n)
    {
    case 1:
        cstmsr.addCustomer();
        break;
    case 2:
        cout << "Enter customer ID : ";
        cin >> Prdct1;
        cin.ignore();
        cstmsr.editCustomerInfo(Prdct1);
        break;
    case 3:
        cout << " Enter customer ID : ";
        cin >> Prdct2;
        cin.ignore();
        cstmsr.searchForCustomer(Prdct2);
        break;
    case 4:
        cout << " Enter the customer ID : ";
        cin >> Prdct3;
        cin.ignore();
        cstmsr.deleteCustomer(Prdct3);
        break;
    }
}

void readFromTheFileProduct()
{
    unsigned int prdctId;
    string prdctName;
    string prdctSN;
    double prdctPrice;
    fstream infile("productList.txt", ios::in);
    if(infile.is_open())
    {
        while (infile >> prdctId && getline(infile,prdctName, '|')&&
                getline(infile,prdctSN, '|')&& infile>>prdctPrice)
        {
            productList[m_PrdctList_indx].setProductID(prdctId);
            if(prdctName[0]==' ')
            {
                prdctName.erase(0,1);
            }
            productList[m_PrdctList_indx].setProductName(prdctName);
            productList[m_PrdctList_indx].setproductserialNumber(prdctSN);
            productList[m_PrdctList_indx].setProductPrice(prdctPrice);
            m_PrdctList_indx++;
            m_PrdctListID++;
        }
    }
    infile.close();
}


void writeOnTheFileProduct()
{
    fstream writeOnProduct("productList.txt", ios::out);
    for(int i = 0 ; i < m_PrdctList_indx; i++)
    {
        writeOnProduct<< productList[i].printProduct() << endl;
    }
    writeOnProduct.close();
}

void readFromTheFileOrder()
{
    string rdrDate;
    int rdrItemStatus;
    long long orderNumber;
    ifstream infile("orderList.txt");
    while(infile >> rdrItemStatus)
    {
        getline(infile,rdrDate,'|' );
        infile >> orderNumber;
        orderList[m_OrderList_indx].readFromORDer(infile, cstmsr.returnCustomerArr(), cstmsr.getCustmrArrSize(), &stck );
        orderList[m_OrderList_indx].setOrderID(m_OrderListCounter);
        if(rdrDate[0]==' ')
        {
            rdrDate.erase(0,1);
        }
        orderList[m_OrderList_indx].setOrderDate(rdrDate);
        orderList[m_OrderList_indx].setOrderNumber(orderNumber);
        orderList[m_OrderList_indx].setOrderStatus(rdrItemStatus);
        m_OrderList_indx++;
        m_OrderListCounter++;
    }
    infile.close();

}

void readFromTheFileTransaction()
{
    string transactionDate;
    ifstream infile("TransactionList.txt");
    while(getline(infile,transactionDate,'|' ))
    {
        TransactionList[m_TransactionList_indx].setTrnsactionID(m_TransactionCounter);
        if(transactionDate[0]==' ')
        {
            transactionDate.erase(0,1);
        }
        TransactionList[m_TransactionList_indx].setTransactionDate(transactionDate);
        TransactionList[m_TransactionList_indx].readFromTransaction(infile, cstmsr.returnCustomerArr(), cstmsr.getCustmrArrSize());
        TransactionList[m_TransactionList_indx].SetOrdrToTransaction(&orderList);
        TransactionList[m_TransactionList_indx].setOrdersCount(&m_OrderList_indx);

        m_TransactionList_indx++;
        m_TransactionCounter++;
    }
    infile.close();
}

void writeOnTheFileOrder()
{
    fstream writeOnOrderList("OrderList.txt",ios::out);
    for(int i = 0 ; i < m_OrderList_indx; i++)
    {
        writeOnOrderList<< orderList[i].writeOnOrder()<< endl;
    }

    writeOnOrderList.close();
}


void writeOnTheFileTransaction()
{
    fstream writeOnTransaction("TransactionList.txt",ios::out);
    for(int i = 0 ; i < m_TransactionList_indx; i++)
    {
        writeOnTransaction << TransactionList[i].WriteToTrnasctionFile();
        if(i != m_TransactionList_indx - 1)
        {
            cout << endl;
        }
    }
    writeOnTransaction.close();
}
