//Online Food Menu Management System Using BST

#include<iostream>
#include<iomanip>
#include<limits>
#include<cctype>

using namespace std;

struct foodType{

    int foodId;
    string foodName;
    string category;
    float price;
    float rating;

    foodType *left;
    foodType *right;
};

foodType *root = NULL;

bool isValidString(string s){
    if(s.empty()) return false;

    for(char c : s){
        if(!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

bool isValidAlnum(string s){
    if(s.empty()) return false;

    for(char c : s){
        if(!isalnum(c))
            return false;
    }
    return true;
}

foodType* createNode(){

    foodType *temp = new foodType;
    string line;

    cout << "\n Enter Food ID: ";
    getline(cin, line);

    if(line.empty()){
        cout << " Invalid Food ID! Input cannot be empty.\n";
        delete temp;
        return NULL;
    }

    bool validId = true;
    for(char c : line){
        if(!isdigit(c)){
            validId = false;
            break;
        }
    }

    if(!validId){
        cout << " Invalid Food ID! Must be a number.\n";
        delete temp;
        return NULL;
    }

    temp->foodId = stoi(line);

    cout << " Enter Food Name: ";
    getline(cin, temp->foodName);

    if(temp->foodName.empty()){
        cout << " Invalid Food Name! Input cannot be empty.\n";
        delete temp;
        return NULL;
    }

    cout << " Enter Food Category: ";
    getline(cin, temp->category);

    if(temp->category.empty()){
        cout << " Invalid Category! Input cannot be empty.\n";
        delete temp;
        return NULL;
    }

    cout << " Enter Food Price: ";
    getline(cin, line);

    if(line.empty()){
        cout << " Invalid Price! Input cannot be empty.\n";
        delete temp;
        return NULL;
    }

    bool validPrice = false;
    bool dotSeen = false;
    for(int i = 0; i < (int)line.size(); i++){
        char c = line[i];
        if(i == 0 && c == '-'){
            break;
        }
        if(c == '.' && !dotSeen){
            dotSeen = true;
        } else if(!isdigit(c)){
            validPrice = false;
            goto priceInvalid;
        }
        validPrice = true;
    }

    priceInvalid:
    if(!validPrice || line == "." ){
        cout << " Invalid Price! Must be a positive number.\n";
        delete temp;
        return NULL;
    }

    temp->price = stof(line);

    if(temp->price < 0){
        cout << " Invalid Price! Cannot be negative.\n";
        delete temp;
        return NULL;
    }

    cout << " Enter Food Rating (0.0 - 5.0): ";
    getline(cin, line);

    if(line.empty()){
        cout << " Invalid Rating! Input cannot be empty.\n";
        delete temp;
        return NULL;
    }

    bool validRating = false;
    bool dotSeen2 = false;
    for(int i = 0; i < (int)line.size(); i++){
        char c = line[i];
        if(i == 0 && c == '-'){
            break;
        }
        if(c == '.' && !dotSeen2){
            dotSeen2 = true;
        } else if(!isdigit(c)){
            validRating = false;
            goto ratingInvalid;
        }
        validRating = true;
    }

    ratingInvalid:
    if(!validRating || line == "."){
        cout << " Invalid Rating! Must be a number between 0.0 and 5.0.\n";
        delete temp;
        return NULL;
    }

    temp->rating = stof(line);

    if(temp->rating < 0.0f || temp->rating > 5.0f){
        cout << " Invalid Rating! Must be between 0.0 and 5.0.\n";
        delete temp;
        return NULL;
    }

    temp->left = temp->right = NULL;

    return temp;
}

foodType* insertNode(foodType *root, foodType *temp){

    if(root == NULL){
        return temp;
    }
    else if(temp->foodId < root->foodId){
        root->left = insertNode(root->left, temp);
    }
    else if(temp->foodId > root->foodId){
        root->right = insertNode(root->right, temp);
    }
    else{
        cout << "\n Duplicate Food ID not allowed.\n";
        delete temp;
    }

    return root;
}

foodType* insertFood(foodType *root){

    foodType *temp = createNode();

    if(temp == NULL) return root;

    return insertNode(root, temp);
}

void displayFood(foodType *current){

    cout << left
         << setw(10) << current->foodId
         << setw(20) << current->foodName
         << setw(20) << current->category
         << setw(10) << current->price
         << setw(10) << current->rating
         << endl;
}

void searchFoodByCategory(foodType *root,string category,bool &found){

    if(root != NULL){

        searchFoodByCategory(root->left, category,found);

        if(root->category == category){

            found = true;

            displayFood(root);
        }

        searchFoodByCategory(root->right,category,found);
    }
}


void inorderTraversal(foodType *root){

    if(root != NULL){
        inorderTraversal(root->left);
        displayFood(root);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(foodType *root){

    if(root != NULL){
        displayFood(root);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(foodType *root){

    if(root != NULL){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        displayFood(root);
    }
}

foodType* searchFood(foodType *root, int key){

    if(root == NULL) return NULL;

    if(key == root->foodId) return root;

    else if(key < root->foodId)
        return searchFood(root->left, key);

    else
        return searchFood(root->right, key);
}

void updateFood(foodType *root, int key){

    foodType *temp = searchFood(root, key);

    if(temp == NULL){

        cout << "\n Food not found.\n";
        return;
    }

    string line;

    cout << "\n Enter New Food Name: ";
    getline(cin, temp->foodName);

    cout << " Enter New Category: ";
    getline(cin, temp->category);

    cout << " Enter New Price: ";
    getline(cin, line);

    temp->price = stof(line);

    cout << " Enter New Rating (0 - 5): ";
    getline(cin, line);

    temp->rating = stof(line);

    cout << "\n Food information updated successfully.\n";
}


foodType* findMinimum(foodType *root){

    if(root == NULL) return NULL;

    while(root->left != NULL)
        root = root->left;

    return root;
}

foodType* findMaximum(foodType *root){

    if(root == NULL) return NULL;

    while(root->right != NULL)
        root = root->right;

    return root;
}


foodType* deleteFood(foodType *root, int key){

    if(root == NULL) return root;

    if(key < root->foodId)
        root->left = deleteFood(root->left, key);

    else if(key > root->foodId)
        root->right = deleteFood(root->right, key);

    else{

        if(root->left == NULL){
            foodType *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            foodType *temp = root->left;
            delete root;
            return temp;
        }

        foodType *temp = findMinimum(root->right);

        root->foodId   = temp->foodId;
        root->foodName = temp->foodName;
        root->category = temp->category;
        root->price    = temp->price;
        root->rating   = temp->rating;

        root->right = deleteFood(root->right, temp->foodId);
    }

    return root;
}


int countFoods(foodType *root){

    if(root == NULL) return 0;

    return 1 + countFoods(root->left) + countFoods(root->right);
}

int findHeight(foodType *root){

    if(root == NULL) return -1;

    int l = findHeight(root->left);
    int r = findHeight(root->right);

    return (l > r) ? l + 1 : r + 1;
}

bool readInt(int &out){
    string line;
    getline(cin, line);

    if(line.empty()){
        cout << " Invalid input! Cannot be empty.\n";
        return false;
    }

    for(char c : line){
        if(!isdigit(c)){
            cout << " Invalid input! Must be a whole number.\n";
            return false;
        }
    }

    out = stoi(line);
    return true;
}

void displayGroupInfo(){

    cout << "\n\n      Group Members      \n";
    cout << "1. Ebisa Getahun   RU0660/17\n";
    cout << "2. Ekram Nureddis  RU0689/17\n";
    cout << "3. Hanchalu Dereje  RU1021/17\n";
}

int main(){

    char op;
    int key;
    string opLine;

Menu:

    cout << "\n\n========= Online Food Menu BST System =========";
    cout << "\n press 1 to Insert Food Item";
    cout << "\n press 2 to Search Food by ID";
    cout << "\n press 3 to Search Food by Category";
    cout << "\n press 4 to Update Food Item";
    cout << "\n press 5 to Delete Food by ID";
    cout << "\n press 6 to Display (Inorder Traversal)";
    cout << "\n press 7 to Display (Preorder Traversal)";
    cout << "\n press 8 to Display (Postorder Traversal)";
    cout << "\n press 9 to Find Minimum Food ID";
    cout << "\n press A to Find Maximum Food ID";
    cout << "\n press B to Count Total Food Items";
    cout << "\n press C to Find Height of BST";
    cout << "\n press D to Display Group Information";
    cout << "\n 0. Exit";

    cout << "\n\n Select Operation: ";
    getline(cin, opLine);

    if(opLine.empty()){
        cout << "\n Invalid input! Please select an option.\n";
        goto Menu;
    }

    op = opLine[0];

    switch(op){

        case '1':
            root = insertFood(root);
            if(root != NULL)
                cout << "\n Food inserted successfully.\n";
            break;

        case '2':
        {
            cout << "\n Enter Food ID: ";
            if(!readInt(key)) break;

            foodType *f = searchFood(root, key);

            if(f == NULL)
                cout << "\n Not found.\n";
            else{
                cout << "\n Found:\n";
                displayFood(f);
            }
            break;
        }
        
        case '3':
{
    string category;
    bool found = false;

    cout << "\n Enter Category: ";
    getline(cin, category);

    searchFoodByCategory(root,category,found);

    if(!found){

        cout << "\n No food found in that category.\n";
    }

    break;
}

case '4':
{
    cout << "\n Enter Food ID to Update: ";

    if(!readInt(key))
        break;

    updateFood(root, key);

    break;
}

        case '5':
        {
            cout << "\n Enter Food ID to delete: ";
            if(!readInt(key)) break;
            root = deleteFood(root, key);
            cout << "\n Deleted successfully (if ID existed).\n";
            break;
        }

        case '6':
            if(root == NULL) cout << "\n BST is empty.\n";
            else inorderTraversal(root);
            break;

        case '7':
            if(root == NULL) cout << "\n BST is empty.\n";
            else preorderTraversal(root);
            break;

        case '8':
            if(root == NULL) cout << "\n BST is empty.\n";
            else postorderTraversal(root);
            break;

        case '9':
        {
            foodType *m = findMinimum(root);
            if(m) cout << "\n Min ID: " << m->foodId;
            else cout << "\n Empty BST";
            break;
        }

        case 'A':
        case 'a':
        {
            foodType *m = findMaximum(root);
            if(m) cout << "\n Max ID: " << m->foodId;
            else cout << "\n Empty BST";
            break;
        }

        case 'B':
        case 'b':
            cout << "\n Total Foods: " << countFoods(root);
            break;

        case 'C':
        case 'c':
            cout << "\n Height: " << findHeight(root);
            break;

        case 'D':
        case 'd':
            displayGroupInfo();
            break;

        case '0':
            cout << "\n Exit.\n";
            return 0;

        default:
            cout << "\n Invalid option.\n";
    }

    goto Menu;
}
