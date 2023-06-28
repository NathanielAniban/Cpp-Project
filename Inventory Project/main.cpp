#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
string DatabasePath = "Inventory.csv";
class InventoryManagement{
    public:
    //Menu
    void InventoryManager(){
        Again:
        system("cls");
        char choice;
        cout << "==========================================" << endl;
        cout << "|  Welcome This is Inventory Management! |" << endl;
        cout << "==========================================" << endl;
        cout << "|           S E L E C T I O N            |" << endl;
        cout << "==========================================" << endl;
        cout << "|           [A] Add Product              |" << endl;
        cout << "|           [V] Show Product             |" << endl;
        cout << "|           [S] Search Product           |" << endl;
        cout << "|           [R] Restock Product          |" << endl;
        cout << "|           [G] Restock Goods            |" << endl;
        cout << "|           [D] Delete Product           |" << endl;
        cout << "|           [Q] Log - Out                |" << endl;
        cout << "==========================================" << endl;
        cout << " SELECT: "; cin >> choice;
        switch(choice){
            case 'A': case 'a': AddProduct(); system("pause"); goto Again; break;
            case 'V': case 'v': SeeProduct(); system("pause"); goto Again;break;
            case 'S': case 's': SearchProductHandler(); system("pause"); goto Again;break;
            case 'R': case 'r': AddStockHandler(); system("pause"); goto Again;break;
            case 'D': case 'd': DeleteItemHandler(); system("pause"); goto Again;break;
            case 'G': case 'g': AutoRestock(); system("pause"); goto Again;break;
            case 'Q': case 'q': cout << "Have A Nice Day!\n"; break;
            default:
            cout << "Invalid. Please Try Again!\n"; goto Again; break;
        }
    }
    // Adding Product To CSV
    void AddProduct(){
        fstream file;
        file.open(DatabasePath);
        if(file){
            file.close();
            AppendingProduct();
        }else{
            file.close();
            FileCreation();
        }
    }
    void FileCreation(){
        fstream file;
        char choice;
        double Pieces,Bundle;
        string Product,Type,Quantity,Stocks,QuantityInBox,goodsLeft;
        file.open(DatabasePath, ios::out);
        if(file.is_open()){
            cin.get();
            file << "ID,Product,Type,Quantity,Bundle Cost,Pieces Cost,Bundle Count,Goods Left,Stocks";
            cout << "Enter Product Name: "; getline(cin,Product);
            cout << "Enter Product Type: "; getline(cin,Type);
            cout << "Enter Product Quantity (Per Bundle): "; cin >> Quantity;
            main:
            cout << "Selection for Price Item:\n";
            cout << "[P] Price for Pieces\n";
            cout << "[B] Price for Bundle\n";
            cout << "Select: "; cin >> choice;
            switch(choice){
                case 'P': case 'p':
            cout << "Enter Product Cost (Per Pieces): "; cin >> Pieces;
                if(Pieces <= 0){
                    cout << "Invalid. Please Try Again!\n";
                    goto main;
                }
                else{
                    Bundle = Pieces * stoi(Quantity);
                }
                break;
                case 'B': case 'b':
            cout << "Enter Product Cost (Per Bundle): "; cin >> Bundle;
                if(Bundle <= 0){
                    cout << "Invalid. Please Try Again!\n";
                    goto main;
                }
                else{
                    Pieces = Bundle / stoi(Quantity);
                }
                break;
                default:
                cout << "Invalid. Please Try Again!\n";
                goto main;
                break;
            }
            cout << "Enter how Many Bundles in Box(Stocks): "; cin >> QuantityInBox;
            cout << "Enter How Many Stocks of Product: "; cin >> Stocks;
            goodsLeft = Quantity;
            int thisStock = stoi(Stocks) - 1;
            file << "\n" << 1 << "," << Product << "," << Type << "," << Quantity << "," << Bundle << "," << Pieces << "," << QuantityInBox << "," << goodsLeft << "," << thisStock;
        }
        else{
            cout << "File Creation Failed!\n";
        }
    }
    void AppendingProduct(){
         fstream file;
        char choice;
        double Pieces,Bundle;
        string Product,Type,Quantity,Stocks,QuantityInBox, line;
        int length = 0;
        file.open(DatabasePath, ios::in);
        while(!file.eof()){
            getline(file, line);
            length = length + 1;
        }
        file.close();
        file.open(DatabasePath, ios::app);
        if(file.is_open()){
            cin.get();
            cout << "Enter Product Name: "; getline(cin,Product);
            cout << "Enter Product Type: "; getline(cin,Type);
            cout << "Enter Product Quantity (Per Bundle): "; cin >> Quantity;
            main:
            cout << "Selection for Price Item:\n";
            cout << "[P] Price for Pieces\n";
            cout << "[B] Price for Bundle\n";
            cout << "Select: "; cin >> choice;
            switch(choice){
                case 'P': case 'p':
            cout << "Enter Product Cost (Per Pieces): "; cin >> Pieces;
                if(Pieces <= 0){
                    cout << "Invalid. Please Try Again!\n";
                    goto main;
                }
                else{
                    Bundle = Pieces * stoi(Quantity);
                }
                break;
                case 'B': case 'b':
            cout << "Enter Product Cost (Per Bundle): "; cin >> Bundle;
                if(Bundle <= 0){
                    cout << "Invalid. Please Try Again!\n";
                    goto main;
                }
                else{
                    Pieces = Bundle / stoi(Quantity);
                }
                break;
                default:
                cout << "Invalid. Please Try Again!\n";
                goto main;
                break;
            }
            cout << "Enter how Many Bundles in Box(Stocks): "; cin >> QuantityInBox;
            cout << "Enter How Many Stocks of Product: "; cin >> Stocks;
            string GoodsLeft = Quantity;
            int MyStocks = stoi(Stocks) - 1;
            file << length-1 << "," << Product << "," << Type << "," << Quantity << "," << Bundle << "," << Pieces << "," << QuantityInBox << "," << GoodsLeft << "," << MyStocks << endl;
        }
        else{
            cout << "File Creation Failed!\n";
        }
    }
    //Showing Product to Screen
    void SeeProduct(){
        string line;
        int counter;
        int sizeCounter;
        int gaplength = 18;
        vector <string> ID,Product,Type,Quantity,CostBundle,CostPieces,GetBundle,goodsleft,Stocks;
        string ToProduct,ToType,ToQuantity,ToBundle,ToPieces,ToGetBundle,MyGoodsLeft,ToStocks;
        fstream file;
        file.open(DatabasePath, ios::in);
        if(file.is_open()){
            while(!file.eof()){
                getline(file, line, ',');
                ID.push_back(line);
                getline(file, line, ',');
                Product.push_back(line);
                getline(file, line, ',');
                Type.push_back(line);
                getline(file, line, ',');
                Quantity.push_back(line);
                getline(file, line, ',');
                CostBundle.push_back(line);
                getline(file, line, ',');
                CostPieces.push_back(line);
                getline(file, line, ',');
                GetBundle.push_back(line);
                getline(file, line, ',');
                goodsleft.push_back(line);
                getline(file, line);
                Stocks.push_back(line);
            }
            file.close();
            counter = Product.size();

            for(int x = 0; x < counter; x++){
                
                cout << ID[x] << "\t";
                ToProduct = Product[x];
                sizeCounter = ToProduct.size();
                for(int y = 0; y < 25; y++){
                    if(y < sizeCounter){
                        cout << ToProduct[y];
                    }else{
                        cout << " ";
                    }
                }

                ToType = Type[x];
                sizeCounter = ToType.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToType[y];
                    }else{
                        cout << " ";
                    }
                }


                ToBundle = CostBundle[x];
                sizeCounter = ToBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToBundle[y];
                    }else{
                        cout << " ";
                    }
                }

                ToPieces = CostPieces[x];
                sizeCounter = ToPieces.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToPieces[y];
                    }else{
                        cout << " ";
                    }
                }


                ToQuantity = Quantity[x];
                sizeCounter = ToQuantity.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToQuantity[y];
                    }else{
                        cout << " ";
                    }
                }
                
                ToGetBundle = GetBundle[x];
                sizeCounter = ToGetBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToGetBundle[y];
                    }else{
                        cout << " ";
                    }
                }
                MyGoodsLeft = goodsleft[x];
                sizeCounter = MyGoodsLeft.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << MyGoodsLeft[y];
                    }else{
                        cout << " ";
                    }
                }
                
                ToStocks = Stocks[x];
                sizeCounter = ToStocks.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToStocks[y];
                    }else{
                        cout << " ";
                    }
                }
                cout << "\n";
            }
        }
        else{
            cout << "You Shoud Create Database to See list!\n";
        }
    }
    //Search Type of The Product to Sort Out
    void SearchProductHandler(){
        fstream file;
        file.open(DatabasePath);
        if(file){
            file.close();
            SearchProduct();
        }
        else{
            file.close();
            cout << "Database Doesn't Exist!\n";
        }
    }
    void SearchProduct(){
        int counter, gaplength = 20, sizeCounter = 0;
        string SearchType, line;
        vector <string> ID,Product,Type,Quantity,CostBundle,CostPieces,GetBundle,goodsleft,Stocks;
        string ToProduct,ToType,ToQuantity,ToBundle,ToPieces,ToGetBundle,MyGoodsLeft,ToStocks;
        fstream file;
        file.open(DatabasePath, ios::in);
        if(file.is_open()){
            while(!file.eof()){
                getline(file, line, ',');
                ID.push_back(line);
                getline(file, line, ',');
                Product.push_back(line);
                getline(file, line, ',');
                Type.push_back(line);
                getline(file, line, ',');
                Quantity.push_back(line);
                getline(file, line, ',');
                CostBundle.push_back(line);
                getline(file, line, ',');
                CostPieces.push_back(line);
                getline(file, line, ',');
                GetBundle.push_back(line);
                getline(file, line, ',');
                goodsleft.push_back(line);
                getline(file, line);
                Stocks.push_back(line);
            }
            file.close();
            counter = Product.size();
        cout << "Search for Product Type: "; cin >> SearchType;

                //Intro List
                cout << ID[0] << "\t";
                ToProduct = Product[0];
                sizeCounter = ToProduct.size();
                for(int y = 0; y < 25; y++){
                    if(y < sizeCounter){
                        cout << ToProduct[y];
                    }else{
                        cout << " ";
                    }
                }

                ToType = Type[0];
                sizeCounter = ToType.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToType[y];
                    }else{
                        cout << " ";
                    }
                }

                ToBundle = ToBundle[0];
                sizeCounter = ToBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToBundle[y];
                    }else{
                        cout << " ";
                    }
                }

                ToPieces = ToPieces[0];
                sizeCounter = ToPieces.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToPieces[y];
                    }else{
                        cout << " ";
                    }
                }

                ToQuantity = Quantity[0];
                sizeCounter = ToQuantity.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToQuantity[y];
                    }else{
                        cout << " ";
                    }
                }

                ToGetBundle = GetBundle[0];
                sizeCounter = ToGetBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToGetBundle[y];
                    }else{
                        cout << " ";
                    }
                }
                
                MyGoodsLeft = goodsleft[0];
                sizeCounter = MyGoodsLeft.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << MyGoodsLeft[y];
                    }else{
                        cout << " ";
                    }
                }


                ToStocks = Stocks[0];
                sizeCounter = ToStocks.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToStocks[y];
                    }else{
                        cout << " ";
                    }
                }
                cout << "\n";
                }
        //Searches Found
        for(int x = 0; x < counter; x++){
                if(SearchType == Type[x]){
                cout << ID[x] << "\t";
                ToProduct = Product[x];
                sizeCounter = ToProduct.size();
                for(int y = 0; y < 25; y++){
                    if(y < sizeCounter){
                        cout << ToProduct[y];
                    }else{
                        cout << " ";
                    }
                }
                ToType = Type[x];
                sizeCounter = ToType.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToType[y];
                    }else{
                        cout << " ";
                    }
                }


                ToBundle = ToBundle[x];
                sizeCounter = ToBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToBundle[y];
                    }else{
                        cout << " ";
                    }
                }

                ToPieces = ToPieces[x];
                sizeCounter = ToPieces.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToPieces[y];
                    }else{
                        cout << " ";
                    }
                }

                ToQuantity = Quantity[x];
                sizeCounter = ToQuantity.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToQuantity[y];
                    }else{
                        cout << " ";
                    }
                }

                ToGetBundle = GetBundle[x];
                sizeCounter = ToGetBundle.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToGetBundle[y];
                    }else{
                        cout << " ";
                    }
                }
                
                MyGoodsLeft = goodsleft[x];
                sizeCounter = MyGoodsLeft.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << MyGoodsLeft[y];
                    }else{
                        cout << " ";
                    }
                }

                ToStocks = Stocks[x];
                sizeCounter = ToStocks.size();
                for(int y = 0; y < gaplength; y++){
                    if(y < sizeCounter){
                        cout << ToStocks[y];
                    }else{
                        cout << " ";
                    }
                }
                cout << "\n";
                }   
            }
    }
    //Search Item to Delete
    void DeleteItemHandler(){
        fstream file;
        file.open(DatabasePath);
        if(file){
            file.close();
            DeleteItem();
        }
        else{
            file.close();
            cout << "Database Doesn't Exist!\n";
        }
    }
    void DeleteItem(){
        int counter, Position, Count;
        vector <string> ID,Product,Type,Quantity,CostBundle,CostPieces,GetBundle,goodsleft,Stocks;
        string line, thisType, thisID;
        char choice;
        cout << "Enter ID of Product: "; cin >> thisID;
        cin.get();
        cout << "Enter Type of Product: "; getline(cin, thisType);
        fstream file;
        file.open(DatabasePath, ios::in);
        while(!file.eof()){
                getline(file, line, ',');
                ID.push_back(line);
                getline(file, line, ',');
                Product.push_back(line);
                getline(file, line, ',');
                Type.push_back(line);
                getline(file, line, ',');
                Quantity.push_back(line);
                getline(file, line, ',');
                CostBundle.push_back(line);
                getline(file, line, ',');
                CostPieces.push_back(line);
                getline(file, line, ',');
                GetBundle.push_back(line);
                getline(file, line, ',');
                goodsleft.push_back(line);
                getline(file, line);
                Stocks.push_back(line);
            }
            file.close();
            bool finder = false;
            counter = Product.size();
            for(int x = 0; x < counter; x++){
                if(thisType == Type[x] && thisID == ID[x]){
                    finder = true;
                    Position = Count-1;
                }
                Count++;
            }
            if(finder == true){
                cout << "ID and Type of Product Found!\n";
                cout << "Your Product:\n";
                cout << "ID: "<< ID[Position] << endl;
                cout << "Product: " << Product[Position] << endl;
                cout << "Type: "<< Type[Position] << endl;
                cout << "Quantity: " << Quantity[Position] << endl;
                cout << "Bundle Cost: " << CostBundle[Position] << endl;
                cout << "Pieces Cost: " << CostPieces[Position] << endl;
                cout << "Bundle Pieces: " << GetBundle[Position] << endl;
                cout << "Goods Left: " << goodsleft[Position] << endl;
                cout << "Stocks: " << Stocks[Position] << endl;
                again:
                cout << "Do you want To Delete this Item to List?: "; cin >> choice;
                switch(choice){
                    case 'Y': case 'y':
                    DeletionProcess(thisID,thisType);
                    break;
                    case 'N': case 'n':
                    cout << "Okay :)\n";
                    break;
                    default:
                    cout << "invalid. Please Try Again!\n";
                    goto again;
                    break;
                }
            }
            else{
                cout << "ID and Type of Product not Found!\n";
            }
    }
    void DeletionProcess(string myID, string myType){
    vector <string> ID,Product,Type,Quantity,CostBundle,CostPieces,GetBundle,Goodsleft,Stocks;
    string line;
    fstream file;
    int counter;
    file.open(DatabasePath, ios::in);
        while(!file.eof()){
                getline(file, line, ',');
                ID.push_back(line);
                getline(file, line, ',');
                Product.push_back(line);
                getline(file, line, ',');
                Type.push_back(line);
                getline(file, line, ',');
                Quantity.push_back(line);
                getline(file, line, ',');
                CostBundle.push_back(line);
                getline(file, line, ',');
                CostPieces.push_back(line);
                getline(file, line, ',');
                GetBundle.push_back(line);
                getline(file, line, ',');
                Goodsleft.push_back(line);
                getline(file, line);
                Stocks.push_back(line);
            }
            file.close();
            counter = Product.size();
            int setter = 0;
        file.open(DatabasePath, ios::out);
        for(int x = 0; x < counter-1; x++){
            if(x == 0){
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << Goodsleft[x] << "," << Stocks[x] << endl; 
            }
            else if(myID == ID[x] && myType == Type[x]){
                cout << "Item Deletion Successfully!\n";
                setter++;
            }
            else{
                file << x-setter << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] <<  "," << GetBundle[x] << "," << Goodsleft[x] << "," << Stocks[x] << endl; 
            }
        }
    
    }
    //Add Stocks To Inventory
    void AddStockHandler(){
        fstream file;
        file.open(DatabasePath);
        if(file){
            file.close();
            AddStock();
        }
        else{
            file.close();
            cout << "Database Doesn't Exist!\n";
        }
    }
    void AddStock(){
        string findID, findType, line;
        int MyStock;
        vector <string> GetID, GetProduct, GetType,GetQuantity,GetBundleCost,GetPiecesCost;
        vector <string> GetBundle, MyGoodsleft,GetStock;
        int counter;
        cout << "Add Stock:\n";
        cout << "Enter the Product ID: "; cin >> findID;
        cin.get();
        cout << "Enter Product Type: "; getline(cin, findType);
        fstream file;
        file.open(DatabasePath, ios::in);
        while(!file.eof()){
            getline(file, line, ',');
            GetID.push_back(line);
            getline(file, line, ',');
            GetProduct.push_back(line);
            getline(file, line, ',');
            GetType.push_back(line);
            getline(file, line, ',');
            GetQuantity.push_back(line);
            getline(file, line, ',');
            GetBundleCost.push_back(line);
            getline(file, line, ',');
            GetPiecesCost.push_back(line);
            getline(file, line, ',');
            GetBundle.push_back(line);
            getline(file, line, ',');
            MyGoodsleft.push_back(line);
            getline(file, line);
            GetStock.push_back(line);
        }
        file.close();
        counter = GetID.size();
        bool condition = false;
        int StockGetter;
        for(int x = 0; x < counter; x++){
            if(findID == GetID[x] && findType == GetType[x]){
                cout << "Item Found!\n";
                StockGetter = stoi(GetStock[x]);
                condition = true;
            }
        }
        
        file.open(DatabasePath, ios::out);
        if(condition == true){
            cout << "Enter How Many Stocks You'll Add in the System: "; cin >> MyStock;
            for(int x = 0; x < counter-1; x++){
                if(findID == GetID[x] && findType == GetType[x]){
                file << GetID[x] << "," << GetProduct[x] << "," << GetType[x] << "," << GetQuantity[x] << "," << GetBundleCost[x] << "," << GetPiecesCost[x] <<  "," << GetBundle[x] << "," << MyGoodsleft[x] << "," << MyStock + StockGetter << endl; 
                cout << "Restocking Item Successfully!\n";
                }
                else{
                file << GetID[x] << "," << GetProduct[x] << "," << GetType[x] << "," << GetQuantity[x] << "," << GetBundleCost[x] << "," << GetPiecesCost[x] <<  "," << GetBundle[x] << "," << MyGoodsleft[x] << "," << GetStock[x] << endl;  
                }
            }
        }
        else{
            cout << "Product ID and Type not Found!\n";
        }


    }
    void AutoRestock(){
        vector <string> ID,Product,Type,Quantity,CostBundle,CostPieces,GetBundle,goodsleft,Stocks;
        string line;
        bool condition = false;
        fstream file;
        file.open(DatabasePath,ios::in);
        while(!file.eof()){
                getline(file, line, ',');
                ID.push_back(line);
                getline(file, line, ',');
                Product.push_back(line);
                getline(file, line, ',');
                Type.push_back(line);
                getline(file, line, ',');
                Quantity.push_back(line);
                getline(file, line, ',');
                CostBundle.push_back(line);
                getline(file, line, ',');
                CostPieces.push_back(line);
                getline(file, line, ',');
                GetBundle.push_back(line);
                getline(file, line, ',');
                goodsleft.push_back(line);
                getline(file, line);
                Stocks.push_back(line);
        }
        file.close();

        file.open(DatabasePath, ios::out);
        int count = ID.size()-1;
        for(int x = 0; x < count; x++){
            if(x == 0){
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << goodsleft[x] << "," << Stocks[x] << endl; 
            }
            else if(stoi(goodsleft[x]) == 0 && stoi(Stocks[x]) == 0){
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << goodsleft[x] << "," << Stocks[x] << endl;
            cout<< "This ID: " << ID[x] << ". OUT OF STOCK! RESTOCK IMMEDIATELY\n";
            }
            else if(stoi(goodsleft[x]) == 0){
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << Quantity[x] << "," << stoi(Stocks[x]) - 1 << endl; 
            condition = true;
            }
            else if(stoi(Stocks[x]) == 0){
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << Quantity[x] << "," << Stocks[x] << endl; 
            cout << "This ID: " << ID[x] << ". Need To Restock it's Inventory!\n";
            }
            else{
            file << ID[x] << "," << Product[x] << "," << Type[x] << "," << Quantity[x] << "," << CostBundle[x] << "," << CostPieces[x] << "," << GetBundle[x] << "," << goodsleft[x] << "," << Stocks[x] << endl;     
            }
        }
        if(condition == true){
        cout << "Restocking Goods Successfully!\n";
        }
        else{
        cout << "There's no Need To Restock!\n";
        }
        file.close();
    }    
};

int main(){
    InventoryManagement Product;
    Product.InventoryManager();
    

    return 0;
}