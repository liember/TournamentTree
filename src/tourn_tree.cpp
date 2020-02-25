#include "tourn_tree.hpp"

using namespace std;

Node *create_node(int idx)
{
    Node *t = new Node;
    t->left = t->right = NULL;
    t->idx = idx;
    return t;
}

void traverse_height(Node *root, int arr[], int &res)
{
    // нет типа, нет проблем
    if (root == NULL || (root->left == NULL &&
                         root->right == NULL))
        return;

    // находим типа который сравнивался с самым пиздатым
    if (root->left->idx != root->idx)
    {
        res = arr[root->left->idx];
    }
    else
    {
        res = arr[root->right->idx];
    }
    int drugoitipok;
    if (root->left->idx == root->idx)
    {
        if (root->left->left->idx != root->idx)
        {
            drugoitipok = arr[root->left->left->idx];
        }
        else
        {
            drugoitipok = arr[root->left->right->idx];
        }
    }
    else
    {
        if (root->right->left->idx != root->idx)
        {
            drugoitipok = arr[root->right->left->idx];
        }
        else
        {
            drugoitipok = arr[root->right->right->idx];
        }
    }

    if (drugoitipok < res)
    {
        res = drugoitipok;
    }

    // он и есть второй по пиздатости тип
}

void find_second_min(int arr[], int n)
{
    cout << "find_second_min" << endl;
    // Создаем список пиздатых типков
    list<Node *> li;

    Node *root = NULL;
    for (int i = 0; i < n; i += 2)
    {
        Node *t1 = create_node(i); // берем одного типа
        Node *t2 = NULL;           // а это пока оставим на случай если массовка не четная
                                   // и типа сверху нескем сравнивать
        if (i + 1 < n)             // если есть с кем сравнивать
        {
            // берем второго типа
            t2 = create_node(i + 1);

            // находим самого пиздатого из них
            if (arr[i] < arr[i + 1])
            {
                root = create_node(i); // реально поднялся
            }
            else
            {
                root = create_node(i + 1); // реально поднялся
            }

            // записали как оно было
            root->left = t1;
            root->right = t2;

            // добавили в список типов (это как новая массовка типов попиже)
            li.push_back(root);
        }
        else
            li.push_back(t1); // !!! заметь что в этом случае список будет не четным !!!
    }

    int lsize = li.size(); // размер массовки типов которые чего то добились в жизни

    // Создаем законченное дерево из списка подготовленного выше
    while (lsize != 1)
    {
        // узнаем индекс последней рассматриваемой пары
        int last = (lsize & 1) ? (lsize - 2) : (lsize - 1); // если lsize нечетное то

        // Попарно обрабатываем список
        for (int i = 0; i < last; i += 2)
        {
            // Берем двух типов из списка, победитель поднимается наверх
            // в новый узел
            Node *f1 = li.front(); //берем первый жлемент списка
            li.pop_front();        // удаляем перавый элемент списка

            Node *f2 = li.front(); // повторять не стану
            li.pop_front();        // ...

            // сравниваем и в итоге получаем новыого батю
            root = (arr[f1->idx] < arr[f2->idx]) ? create_node(f1->idx) : create_node(f2->idx);

            // победитель тепрь батя и надо подвязать детей к нему
            root->left = f1;
            root->right = f2;

            // добавляем в список
            li.push_back(root);
        }
        if (lsize & 1) // если lsize нечетное
        {
            li.push_back(li.front()); // закидываем оставшегося типа без пары в конец
            li.pop_front();           // ...
        }
        lsize = li.size(); // список пиздатых типов опять умегьшился :D
    }

    int res = INT_MAX;                           // по хорошему самый пиздатый типок это бесконечность, но чет таких не нашел, поэтому INT_MAX
    traverse_height(root, arr, res);             // находим не самого пиздатого, но все же пиздатого, всё же типа
    cout << "Minimum: " << arr[root->idx]        // выводим самого пиздатого
         << ", Second minimum: " << res << endl; // выводим не самого пиздатого
}
