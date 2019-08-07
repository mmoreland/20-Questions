/*
	animal.cpp

	author: 
	date:   

	Animal/20 questions program for CSCI 262, Fall 2018. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <deque>

using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
};

void read_preorder(node* tree, ifstream &fin){
    string current;

    getline(fin, current); //gets the current line from the txt file
    tree->data = current;

    if(current[1] == 'A'){ //stops the current run if the node is an answer
        return;
    }
    tree->left = new node;//sets the next two nodes for reading the tree
    read_preorder(tree->left, fin);

    tree->right = new node;
    read_preorder(tree->right, fin);

    return;

}


node* read_game_tree() { //sets the tree and returns the root node
    ifstream fin("animal.txt");
    node *root = new node;
    read_preorder(root, fin);
    return root;
}
void extend_game_tree(node* n, queue<string> q){ //used for extending the tree when the computer doesnt guess
        string og;
        string question;
        string Q2;
        og = n->data;

        cout << "I asked the following: " << endl; //outputs the queue of what was asked and the answers

        do{
            cout << q.front() << endl;
            q.pop();
        }while(!q.empty());

        cout << "Enter a new animal in the form of a question," << endl <<"e.g., 'Is it a whale?': (hit enter twice)" << endl;
        cin.ignore();
        getline(cin,question);
        question = "#A " + question; //Adds the answer piece to the question so it reads back into the tree
        node* a = new node;
        node* b = new node;
        n -> left = a;
        n -> right = b;

        cin.ignore();//fixed a weird problem with the function repeating
        cout << "Now enter a question for which the answer is 'yes' for your new animal" << endl << "and which does not contradict you previous answer";
        getline(cin, Q2);
        Q2 = "#Q " + Q2;
        n->data = Q2;
        a -> data = question;
        b -> data = og;

        cout << endl;
}


void play_game(node* n) {
    string ans;
    queue<string> track;
    node* m = new node; //keeps track of where the end of the tree is

    while (n != NULL) { //outputs the play function until the loop reaches NULL
        cout << n->data << "(y/n)" << endl;
        track.emplace(n->data);
        cin >> ans;
        track.emplace(ans);
        if (ans == "y") {
            m = n;
            n = n->left;
        } else if (ans == "n") {
            m = n;
            n = n->right;
        }
    }
    if ( ans == "y") {
        cout << "YAY! I guessed your animal" << endl;
        cout << endl;
        cin.ignore();//stopped the code from repeating randomly
        return;

    } else if (ans == "n") {
        char extend;
        cout << "BOO! I don't know" << endl;
        cout << "Would you like to extend the game tree? (y/n)" << endl;
        cin >> extend;
        if (extend == 'y') {
            extend_game_tree(m, track);//sets up the extend function
        }else{
            return;
        }
    }
}

void write_preorder(node* n, ofstream &out) {//writes the tree to save the file
        string current;
        if (n != NULL) { //will call recursively until the tree reaches NULL
            current = n->data;
            out << current;
            out << endl;
            write_preorder(n->left, out);
            write_preorder(n->right, out);
        }
    return;
}


void save_game_tree(node* n){ //sets up the ofstream and writes it
    ofstream out("animal.txt");
    write_preorder(n, out);
    out.close();


}
//void delete_game_tree(node* n); I left out the delete funciton since the program can just quit

int main() {//I didn't touch Main at all.
	node* root = read_game_tree();
	if (root == NULL) return -1;
	while (true) {
		string tmp;
		int choice;
		
		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		getline(cin, tmp);
		choice = atoi(tmp.c_str());

		switch (choice) {
		case 1:
			play_game(root);
			break;
		case 2:
			save_game_tree(root);
			break;
		case 3:
			break;
		default:
			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}
	
	//delete_game_tree(root);

	return 0;
}

