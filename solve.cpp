#include "bits/stdc++.h"
using namespace std;


//sql database connection using api.
map<char, int>m;

vector<char>v;


struct trie
{
public:

    int isendofword;//bool which tells us that end of word is there or not

    trie* child[62];

    string ori_link;

    string description;

    int cnt_of_clicks;

    string password;
};




trie* getNode()
{
    trie *a = new trie;
    
    a->isendofword = 0;
    
    for (int i = 0; i < 62; i++)
    {

        a->child[i] = NULL;
        
    }

    a->cnt_of_clicks = 0;

    return a;
}


void indexing()
{

    for (int i = 0; i < 10; i++)
    {

        v.push_back('0' + i);

    }
    for (int i = 0; i < 26; i++)
    {

        v.push_back('a' + i);

    }

    for (int i = 0; i < 26; i++)
    {

        v.push_back('A' + i);

    }
    for (int i = 0; i < 10; i++)
    {
        char ch = '0' + i;

        m[ch] = i;
    }
    for (int i = 0; i < 26; i++)
    {
        char ch = 'A' + i;

        m[ch] = 10 + i;
    }

    for (int i = 0; i < 26; i++)
    {
        char ch = 'a' + i;

        m[ch] = 36 + i;
    }
}



void insert(string s, trie *root, string pass, string orilink, string descript = "")
{
    trie* mover = root;
    for (int i = 0; i < s.length(); i++)
    {
        int index = m[s[i]];

        if (mover->child[index] == NULL)
        {
            mover->child[index] = getNode(); //(as its null a new node has to be formed)

        }

        mover = mover->child[index];
    }

    mover->ori_link = orilink;

    mover->password = pass;

    mover->isendofword++;

    mover->description = descript;

    cout << "Congratulations your link has been successfully generated\n\n";

    cout << "Your link is:\n\n";

    cout << "https://www.aap.com/";

    cout << s << endl;

    cout << "\n";
}



bool search(string s, trie* root)
{
    trie *mover = root;
    for (int i = 0; i < s.length(); i++)
    {
        int index = m[s[i]];

        if (mover->child[index] == NULL)
        {
            return false;

        }
        else
        {
            mover = mover->child[index];

        }
    }
    return ((mover->isendofword) && (mover != NULL));
    //return kare
}



void retrieve(string s, trie* root)
{
    trie *mover = root;

    for (int i = 0; i < s.length(); i++)
    {
        int index = m[s[i]];

        if (mover->child[index] == NULL)
        {
            cout << "No such link exists or create a new link\n" << endl;
            return;
        }
        else
        {
            mover = mover->child[index];

        }
    }

    bool a = ((mover->isendofword) && (mover != NULL));


    if (a)
    {
        cout << "The original link is:\n\n";

        cout << mover->ori_link << endl;

        cout << "The number of clicks till now on this link is:\n\n";

        cout << ++mover->cnt_of_clicks << endl;
    }
    else
    {
        cout << "No such link exists or create a new link\n" << endl;
    }
}


void erase(string s, trie* root)
{
    trie *mover = root;
    for (int i = 0; i < s.length(); i++)
    {
        int index = m[s[i]];

        if (mover->child[index] == NULL)
        {
            cout << "No such link exists or create a new link\n" << endl;

        }
        else
        {
            mover = mover->child[index];

        }
    }
    bool a = ((mover->isendofword) && (mover != NULL));


    if (a)
    {
        cout << "Please enter your password\n\n";


        string password;

        cin >> password;

        cout << endl;
        if (password == mover->password)
        {
            mover->isendofword--;


            mover->description = "";

            mover->cnt_of_clicks = 0;

            mover->password = "";

            mover->ori_link = "";

            cout << "OK your link has been deleted\n\n";
        }
        else
        {
            cout << "Wrong password\n\n";
        }
    }
    else
    {
        cout << "No such link exists or create a new link\n" << endl;
    }
}

string generator(trie* root)
{

    while (1) {

        string s1;

        for (int i = 0; i < 6; i++)
        {

            s1 += v[rand() % 62];
        }

        if (!search(s1, root))
        {
            return s1;
        }
    }
}


int main()
{

    indexing();

    cout << "WELCOME TO OUR AAP URL Shortner\n\n";


    trie *root = getNode();

    while (1)
    {
        cout << "Press 1 for shortening\n\n";

        cout << "Press 2 for retrieval\n\n";

        cout << "Press 3 for deleting\n\n";

        cout << "Press 4 for exit\n\n";
        
        char n;

        cin >> n;

        cout << endl;
        
        if (n == '1')
        {
            cout << "Please enter the original_link\n\n";

            string original_link;

            cin >> original_link;

            cout << endl;

            string short_link = generator(root);

            string password, descript;

            cout << "Please enter the password\n\n";

            cin >> password;

            cout << endl;

            cout << "Please enter the description\n\n";

            cin >> descript;

            cout << endl;

            insert(short_link, root, password, original_link, descript);
        
        }
        else if (n == '2')
        {
            cout << "Enter shortened link:\n\n";

            string user_input;

            cin >> user_input;

            cout << endl;

            user_input = user_input.substr(user_input.length() - 6);

            retrieve(user_input, root);

        }

        else if (n == '3')
        {
            cout << "Enter shortened link that is to be deleted:\n\n";

            string user_input;

            cin >> user_input;

            cout << endl;

            user_input = user_input.substr(user_input.length() - 6);

            erase(user_input, root);
        }

        else
        {
            cout << "Thanks for using our software\n";

            break;

        }
    }
}
