#include "inventoryManager.hpp"

class InventoryManagementLayout : protected ProductManager {
    public:
        void printHeader() {
            // Define column widths: Name=15, Stock=10, Price=10
            std::cout << std::left << std::setw(15) << "PRODUCT" 
                    << std::setw(10) << "STOCK" 
                    << std::setw(10) << "PRICE" << std::endl;
                    
            // Print a separator line
            std::cout << std::string(35, '-') << std::endl;

            //Read Files
            std::ifstream readFile(DATABASE_FILE);
            std::vector<std::string> productInfo;
            std::vector<std::string> productName;
            std::vector<int> productStock;
            std::vector<double> productPrice;
            
            if(readFile.is_open()){
                std::string tempFile;    
                while(std::getline(readFile, tempFile)){
                    productInfo.push_back(tempFile);
                }
                readFile.close();
            }
            else{
                std::cerr << "Unable to open file." << std::endl;
            }
            
            while(!productInfo.empty()){
                std::string currentProduct = productInfo.back();
                productInfo.pop_back();

                size_t pos1 = currentProduct.find(",");
                size_t pos2 = currentProduct.find(",", pos1 + 1);

                std::string name = currentProduct.substr(0, pos1);
                int stock = std::stoi(currentProduct.substr(pos1 + 1, pos2 - pos1 - 1));
                double price = std::stod(currentProduct.substr(pos2 + 1));

                productName.push_back(name);
                productStock.push_back(stock);
                productPrice.push_back(price);
            }

            for(size_t i = 0; i < productName.size(); i++){
                std::cout << std::left << std::setw(15) << productName[i] 
                        << std::setw(10) << productStock[i] 
                        << std::setw(10) << productPrice[i] << std::endl;
            }
        };

        void displayMenu(){
            size_t input;
            std::cout << "\nWelcome to the Inventory Management System!" << std::endl;
            std::cout << "Menu Options:" << std::endl;
            std::cout << "1. Add Product" << std::endl;
            std::cout << "2. Delete Product" << std::endl;
            std::cout << "3. Update Product" << std::endl;
            std::cout << "4. Check Product Existence" << std::endl;
            std::cout << "5. Check Stock Level" << std::endl;
            std::cout << "6. Display Inventory" << std::endl;
            std::cout << "7. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            if (!(std::cin >> input)) {
                std::cerr << "Invalid input! Please enter a number." << std::endl;
                return; // Exit or handle error
            }
            std::cin.ignore(); // Ignore the newline character left in the buffer
            handleUserChoice(input);

        };

        bool handleUserChoice(int choice){
            switch(choice) {
                case 1:
                    // Add Product
                    insertManuallyNewProduct();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break;
                case 2:
                    // Delete Product
                    deleteManuallyProduct();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break;
                case 3:
                    // Update Product
                    updateManuallyProduct();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break;  
                case 4:
                    // Check Product Existence
                    manuallyCheckProductExistence();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break;
                case 5:
                    // Check Stock Level
                    manuallyCheckStockLevel();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break;
                case 6:
                    printHeader();
                    system("pause"); // Pause the console to view the message (Windows-specific)
                    system("cls"); // Clear the console screen (Windows-specific)
                    displayMenu();
                    break; // Exit the program
                case 7:
                    std::cout << "Exiting program." << std::endl;
                    break; // Exit the program
                default:
                    std::cerr << "Invalid choice. Please try again." << std::endl;
            }
            return true; // Continue the program
        }

        void insertManuallyNewProduct(){
        std::string ProductName;
        int ProductStock;
        double ProductPrice;

        std::cout << "Enter the name of the product: ";
        std::getline(std::cin, ProductName);
        std::cout << "Enter the stock of the product: ";
        if (!(std::cin >> ProductStock)) {
            std::cerr << "Invalid input! Please enter a number." << std::endl;
            return; // Exit or handle error
        }
    
        std::cout << "Enter the price of the product: ";
        std::cin >> ProductPrice;
        std::cin.ignore(); // Ignore the newline character left in the buffer

        if(insertNewProduct(ProductName, ProductStock, ProductPrice)){
            std::cout << "Product added successfully." << std::endl;
        } else {
            std::cerr << "Failed to add product." << std::endl;
        }
}

        void deleteManuallyProduct(){
            std::string ProductName;

            std::cout << "Enter the name of the product to delete: ";
            std::getline(std::cin, ProductName);

            if(findAndDeleteProduct(ProductName)){
                std::cout << "Product deleted successfully." << std::endl;
            } else {
                std::cerr << "Failed to delete product." << std::endl;
            }
        };  

        void updateManuallyProduct(){
            std::string ProductName;
            int newStock;
            double newPrice;

            std::cout << "Enter the name of the product to update: ";
            std::getline(std::cin, ProductName);
            std::cout << "Enter the new stock of the product: ";
            if (!(std::cin >> newStock)) {
                std::cerr << "Invalid input! Please enter a number." << std::endl;
                return; // Exit or handle error
            }
        
            std::cout << "Enter the new price of the product: ";
            std::cin >> newPrice;
            std::cin.ignore(); // Ignore the newline character left in the buffer

            if(findAndUpdateProduct(ProductName, newStock, newPrice)){
                std::cout << "Product updated successfully." << std::endl;
            } else {
                std::cerr << "Failed to update product." << std::endl;
            }
        };

        void manuallyCheckProductExistence(){
            std::string ProductName;

            std::cout << "Enter the name of the product to check: ";
            std::getline(std::cin, ProductName);

            if(checkIfProductExists(ProductName)){
                std::cout << "Product exists in the database." << std::endl;
            } else {
                std::cout << "Product does not exist in the database." << std::endl;
            }
        };

        void manuallyCheckStockLevel(){
            std::string ProductName;
            int threshold;

            std::cout << "Enter the name of the product to check stock level: ";
            std::getline(std::cin, ProductName);
            std::cout << "Enter the stock threshold: ";
            if (!(std::cin >> threshold)) {
                std::cerr << "Invalid input! Please enter a number." << std::endl;
                return; // Exit or handle error
            }
            std::cin.ignore(); // Ignore the newline character left in the buffer

            if(checkIfStockIsLow(ProductName, threshold)){
                std::cout << "Stock level is low for this product." << std::endl;
            } else {
                std::cout << "Stock level is sufficient for this product." << std::endl;
            }
        };
};

